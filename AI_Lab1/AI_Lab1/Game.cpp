#include "Game.h"
#include <iostream>

/// <summary>
///	Constructor
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1000, 800, 32 }, "Shooter" },
	m_exitGame{false} //when true game will exit
{
	centrePoint = sf::Vector2f(m_window.getSize().x, m_window.getSize().y);
	setupSprite(); // load textures
}

/// <summary>
///	Destructor
/// </summary>
Game::~Game()
{
}

/// <summary>
///	Initial things that are done when the app starts
/// </summary>
void Game::run()
{
	m_mapLoader = new MapLoader();
	m_soundManager = new SoundManager();
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps

	//Truly randomise
	srand(time(NULL));

	m_player->Initialise();
	
	//Sets the values for the view to follow the player
	playerView.setSize(sf::Vector2f(VIEW_HEIGHT,VIEW_HEIGHT));

	//Initialise the original object of each type of enemies

	//Spawn From Nests
	e1.Initialise(1, m_soundManager);
	////Workers
	//e2.Initialise(2);
	////Boids
	//e3.Initialise(3);
	////Swarm
	//e4.Initialise(4);

	////Nest gets a random spawn location
	//m_nestSprite.setPosition(sf::Vector2f(rand() % m_window.getSize().x, rand() % m_window.getSize().y));

	m_player->setWallSprites(&m_mapLoader->getWallSprites());

	spawnEnemies(m_mapLoader->getSpawnPoints());

	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
///	Resizes the view and screen if the app window is adjusted
/// </summary>
void Game::ResizeView(const sf::RenderWindow& window, sf::View view)
{
	float ratio = float(window.getSize().x) / float(window.getSize().y);
	playerView.setSize(sf::Vector2f(VIEW_HEIGHT * ratio, VIEW_HEIGHT*ratio));
}

void Game::RestartGame()
{
	enemies.clear();
	m_player->setHeatlth(100);
	m_player->setPosition(m_player->getStartingPosition());
	spawnEnemies(m_mapLoader->getSpawnPoints());
	score = enemies.size();
}

/// <summary>
/// Handles if the app is closed or resized.
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}

		if (sf::Event::Resized == event.type)
		{
			ResizeView(m_window, playerView);
		}
	}
}

void Game::spawnEnemies(std::vector<sf::Vector2f> spawns)
{
	std::vector<sf::Vector2f> tempSpawns = spawns;
	
	for (int i = 0; i < tempSpawns.size(); i++)
	{
			e1.setPosition(tempSpawns.at(i));
			enemies.push_back(e1);
	}
}

/// <summary>
/// Handles all events and collisions relating to the enemies and the nests
/// </summary>
void Game::EnemyHandler()
{
	if (spawnCounter < 40)
	{
		spawnCounter++;
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].Update(m_player->getPosition(), centrePoint, 1);

		//Get player collision box
		playerBound = m_player->getSprite().getGlobalBounds();
		playerBoundShap.setSize(sf::Vector2f(playerBound.width, playerBound.height));
		playerBoundShap.setPosition(sf::Vector2f(playerBound.left, playerBound.top));

		for (size_t j = 0; j < enemies[i].getBullets().size(); j++)
		{
			//Get bullet of the enemy's collision box
			bulletBound = enemies[i].getBullets()[j].m_shape.getGlobalBounds();
			bulletBoundShape.setSize(sf::Vector2f(bulletBound.width, bulletBound.height));
			bulletBoundShape.setPosition(sf::Vector2f(bulletBound.left, bulletBound.top));

			if (playerBoundShap.getGlobalBounds().intersects(bulletBoundShape.getGlobalBounds()))
			{
				//The player's invincibilty turns on
				if (!m_player->getInvincible())
				{
					m_soundManager->playSound("playerGrunt");
					//Reduce Health by 10
					m_player->setInvincible(true);
					m_player->invinTimer = 0;
					m_player->reduceHealth(25);
					if (m_player->getHealth() <= 0)
					{
						m_gameState = GameState::DeathScreen;
					}
				}
			}
		}
	}
	//Turns off after time
	if (m_player->getInvincible())
	{
		m_player->getSprite().setColor(sf::Color::Black);
		m_player->invinTimer++;
	}
	if (m_player->invinTimer >= 100)
	{
		m_player->setInvincible(false);
	}
}

/// <summary>
/// Handles all events and collisions relating to the workers
/// </summary>
void Game::WorkerHandler()
{
	//Get player collsion box
	playerBound = m_player->getSprite().getGlobalBounds();
	playerBoundShap.setSize(sf::Vector2f(playerBound.width, playerBound.height));
	playerBoundShap.setPosition(sf::Vector2f(playerBound.left, playerBound.top));

	for (size_t h = 0; h < m_mapLoader->getWallSprites().size(); h++)
	{
		//Only check walls within a distance of 200 pixels
		if (m_player->Magnitude(playerBoundShap.getPosition() - m_mapLoader->getWallSprites().at(h).getPosition()) < 200)
		{
			//If bullet hits wall

			//WANT TO SMOOTHEN OUT COLLISION
			if (playerBoundShap.getGlobalBounds().intersects(m_mapLoader->getWallSprites().at(h).getGlobalBounds()))
			{
				sf::Vector2f tempPlayerPos = m_player->getPosition();
				sf::Vector2f tempSpritePos = m_mapLoader->getWallSprites().at(h).getPosition();

				if (tempPlayerPos.y < tempSpritePos.y)
				{
					m_player->setPosition(sf::Vector2f(tempPlayerPos.x, tempPlayerPos.y -= 5));
				}

				else if (tempPlayerPos.y > tempSpritePos.y)
				{
					m_player->setPosition(sf::Vector2f(tempPlayerPos.x, tempPlayerPos.y += 5));
				}

				if (tempPlayerPos.x < tempSpritePos.x)
				{
					m_player->setPosition(sf::Vector2f(tempPlayerPos.x -= 5, tempPlayerPos.y));
				}

				else if (tempPlayerPos.y > tempSpritePos.y)
				{
					m_player->setPosition(sf::Vector2f(tempPlayerPos.x += 5, tempPlayerPos.y));
				}

				std::cout << "Wall Hit" << std::endl;
			}
		}
	}

	//Update loop
	//for (size_t j = 0; j < workersEns.size(); j++)
	//{
	//	workersEns[j].Update(m_player->getPosition(), centrePoint, 2);

	//	//Get worker collision box
	//	workerBound = workersEns[j].getSprite().getGlobalBounds();
	//	workerBoundShape.setSize(sf::Vector2f(workerBound.width, workerBound.height));
	//	workerBoundShape.setPosition(sf::Vector2f(workerBound.left, workerBound.top));

	//	if (workerBoundShape.getGlobalBounds().intersects(playerBoundShap.getGlobalBounds()))
	//	{
	//		//delete the worker and gain a point
	//		workersEns.erase(workersEns.begin() + j);
	//		score++;
	//		break;
	//	}
	//}

	//Damage Player if enemy touches you
	for (size_t k = 0; k < enemies.size(); k++)
	{
		//Same variables are reused
		workerBound = enemies[k].getSprite().getGlobalBounds();
		workerBoundShape.setSize(sf::Vector2f(workerBound.width, workerBound.height));
		workerBoundShape.setPosition(sf::Vector2f(workerBound.left, workerBound.top));
		if (workerBoundShape.getGlobalBounds().intersects(playerBoundShap.getGlobalBounds()))
		{
			/*enemies.erase(enemies.begin() + k);*/

			//If the player is not invincible
			if (!m_player->getInvincible())
			{
				//Reduce Health by 10
				m_soundManager->playSound("playerGrunt");
				m_player->setInvincible(true);
				m_player->invinTimer = 0;
				m_player->reduceHealth(10);

				if (m_player->getHealth() <= 0)
				{
					m_gameState = GameState::DeathScreen;
				}
			}
		}
	}
}

void Game::ChangeController()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_controllerMode = Controller::KeyboardContr;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_controllerMode = Controller::JoystickContr;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_player->setOrientation(0);
		m_controllerMode = Controller::TouchScreenContr;
	}
}

void Game::CheckIfFiring()
{
	if (m_controllerMode == Controller::KeyboardContr)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_isFiring = true;
		}
		else
		{
			m_isFiring = false;
		}
	}
	else if (m_controllerMode == Controller::JoystickContr)
	{
		if (sf::Joystick::isButtonPressed(0, 5))
		{
			m_isFiring = true;
		}
		else
		{
			m_isFiring = false;
		}
	}
	else //Controller::TouchScreenContr
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_spacePressedOnce)
		{
			m_spacePressedOnce = true;
			m_isFiring = !m_isFiring;
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_spacePressedOnce)
		{
			m_spacePressedOnce = false;
		}
	}

}

/// <summary>
/// Handles all events and collisions relating to the player's bullets
/// </summary>
void Game::BulletHandler()
{
	CheckIfFiring();

	if (m_isFiring)
	{
		//timer
		if (bulletCounter < 10)
		{
			bulletCounter++;
		}
		else
		{
			bulletCounter = 0;
			b1.m_shape.setPosition(m_player->getPosition());
			b1.m_velocity = normalisedAimDir * b1.m_maxSpeed;
			m_soundManager->playSound("playerGun");
			bullets.push_back(Bullet(b1));
		}

	}
	//Gets the aiming vector between the player and a point slighty, directly ahead of the player
	playerCentre = sf::Vector2f(m_player->getPosition());

	if (m_controllerMode == Controller::KeyboardContr)
	{
		cursorPos = (sf::Vector2f)sf::Mouse::getPosition(m_window);

		aimDir = cursorPos - sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2);
	}

	else if (m_controllerMode == Controller::JoystickContr)
	{
		cursorPos = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z), sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R));
		aimDir = cursorPos;
	}

	else if (m_controllerMode == Controller::TouchScreenContr)
	{
		cursorPos = sf::Vector2f(10 * sin(m_player->getOrientation()) + m_player->getPosition().x, 10 * -cos(m_player->getOrientation()) + m_player->getPosition().y);
		aimDir = cursorPos - playerCentre;
	}

	normalisedAimDir = m_player->Normalise(aimDir);

	//Update each individual bullet
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].m_shape.move(bullets[i].m_velocity);

		//If the bullet is a distance of 2000 or more pixels from the player, the shot is deleted
		if (m_player->Magnitude(bullets[i].m_shape.getPosition() - m_player->getPosition()) > 600)
		{
			bullets.erase(bullets.begin() + i);
			//break;
		}

		//if the bullet wasnt deleted
		else
		{
			//Gets the bullets bounding box
			bulletBound = bullets[i].m_shape.getGlobalBounds();
			bulletBoundShape.setSize(sf::Vector2f(bulletBound.width, bulletBound.height));
			bulletBoundShape.setPosition(sf::Vector2f(bulletBound.left, bulletBound.top));

			//////CAUSES LAG IF BULLET GOES OFF SCREEN
			//for (size_t h = 0; h < m_mapLoader->getWallSprites().size(); h++)
			//{
			//	if (m_player->Magnitude(bullets[i].m_shape.getPosition() - m_mapLoader->getWallSprites().at(h).getPosition()) < 20)
			//	{
			//		////If bullet hits wall
			//		if (bulletBoundShape.getGlobalBounds().intersects(m_mapLoader->getWallSprites().at(h).getGlobalBounds()))
			//		{
			//			bullets.erase(bullets.begin() + i);
			//			//break;
			//		}
			//	}
			//}

			for (size_t k = 0; k < enemies.size(); k++)
			{
				//Gets the enemy's bounding box
				enemyBound = enemies[k].getSprite().getGlobalBounds();
				enemyBoundShap.setSize(sf::Vector2f(enemyBound.width, enemyBound.height));
				enemyBoundShap.setPosition(sf::Vector2f(enemyBound.left, enemyBound.top));

				if (bulletBoundShape.getGlobalBounds().intersects(enemyBoundShap.getGlobalBounds()))
				{
					bullets.erase(bullets.begin() + i);
					//If the enemy has taken 4 hits
					enemies[k].addHitsTaken(1);
					if (enemies[k].getHitsTaken() >= 4)
					{
						m_soundManager->playSound("enemyDeath");
						score--;
						enemies.erase(enemies.begin() + k);
						if (score <= 0)
						{
							m_gameState = GameState::WinScreen;
						}
					}
					else
					{
						m_soundManager->playSound("enemyGrunt");
					}
				}
			}

			//for (size_t j = 0; j < boids.size(); j++)
			//{
			//	//Gets the enemy boid's bounding box
			//	enemyBound = boids[j].getSprite().getGlobalBounds();
			//	enemyBoundShap.setSize(sf::Vector2f(enemyBound.width, enemyBound.height));
			//	enemyBoundShap.setPosition(sf::Vector2f(enemyBound.left, enemyBound.top));
			//	
			//	if (bulletBoundShape.getGlobalBounds().intersects(enemyBoundShap.getGlobalBounds()))
			//	{
			//		bullets.erase(bullets.begin() + i);
			//		boids.erase(boids.begin() + j);
			//		break;
			//	}
			//}
		}
	}
}

/// <summary>
/// Checks to find which worker is the closest
/// Using this will cause frame stutter, commenting out increases framerate
/// </summary>
/// <param name="currentPos">current position of the object checking</param>
sf::Vector2f Game::CheckForNearestWorker(sf::Vector2f currentPos)
{
	float currentAns = -1;
	float finalAns = 5000;
	sf::Vector2f finalPos;
	sf::Vector2f temp;
	for (size_t i = 0; i < workersEns.size(); i++)
	{
			temp = workersEns[i].getSprite().getPosition();
			currentAns = m_player->Magnitude(temp - currentPos);
			if (currentAns < finalAns)
			{
				finalAns = currentAns;
				finalPos = temp;
			}
		}
		return finalPos;
}

void Game::HUDHandler()
{
	m_scorePreText.setPosition(sf::Vector2f(m_player->getPosition().x - 500, m_player->getPosition().y - 450));
	m_scoreText.setPosition(sf::Vector2f(m_scorePreText.getPosition().x + (m_scorePreText.getCharacterSize() * (m_scorePreText.getString().getSize() / 1.5)), m_scorePreText.getPosition().y));
	std::stringstream sc;
	sc << score;
	m_scoreText.setString(sc.str().c_str());
	m_scorePreText.setString("Enemies Remaining: ");

	m_healthPreText.setPosition(m_scorePreText.getPosition().x, m_scorePreText.getPosition().y + 50);
	m_healthText.setPosition(m_healthPreText.getPosition().x + (m_healthPreText.getCharacterSize() * (m_healthPreText.getString().getSize() / 1.5)), m_healthPreText.getPosition().y);
	std::stringstream hl;
	hl << m_player->getHealth();
	m_healthText.setString(hl.str().c_str());
	m_healthPreText.setString("Health: ");

	m_controlModePreText.setPosition(m_healthPreText.getPosition().x, m_healthPreText.getPosition().y + 50);
	m_controlModeText.setPosition(m_controlModePreText.getPosition().x + (m_controlModeText.getCharacterSize() * (m_controlModePreText.getString().getSize() / 1.5)), m_controlModePreText.getPosition().y);
	std::string cm;
	if (m_controllerMode == 0)
	{
		cm = "Keyboard";
	}
	else if (m_controllerMode == 1)
	{
		cm = "Joystick";
	}
	else
	{
		cm = "TouchScreen";
	}
	m_controlModeText.setString(cm);
	m_controlModePreText.setString("Control Mode: ");

	

	/*hudMapBack.setPosition(m_player->getPosition().x - 500, m_player->getPosition().y - 350);
	hudPlayerMap.setPosition(sf::Vector2f(hudMapBack.getPosition().x + (hudMapBack.getSize().x / 2), hudMapBack.getPosition().y + (hudMapBack.getSize().y / 2)));
*/
	for (size_t i = 0; i < enemies.size(); i++)
	{
		hudEnemyMap.setPosition(sf::Vector2f(hudMapBack.getPosition().x + (enemies[i].getPosition().x / 8), hudMapBack.getPosition().y + (enemies[i].getPosition().y / 8)));
		hudEnemiesEls.push_back(hudEnemyMap);
	}
	
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_gameState == GameState::Gameplaying)
	{
		if (boids.size() < 2)
		{
			e3.setPosition(sf::Vector2f(playerView.getSize().x - (rand() % 500), playerView.getSize().y - (rand() % 500)));
			boids.push_back(e3);
		}

		//Player
		m_player->Update(centrePoint, m_controllerMode);
		m_player->orientate(aimDir, m_controllerMode);

		//View
		playerView.setCenter(m_player->getPosition());

		//m_soundManager->update();

		HUDHandler();
		BulletHandler();
		EnemyHandler();
		WorkerHandler();
		ChangeController();
	}
	
	else if ((m_gameState == GameState::DeathScreen) || (m_gameState == GameState::WinScreen))
	{
		std::cout << "You Died/Won" << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			m_gameState = GameState::Gameplaying;
			RestartGame();
		}
	}
	
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	m_window.setView(playerView);

	m_mapLoader->Draw(&m_window);
	
	for (size_t i = 0; i < enemies.size(); i++)
	{
		for (size_t j = 0; j < enemies[i].getBullets().size(); j++)
		{
			m_window.draw(enemies[i].getBullets()[j].m_shape);
		}
		m_window.draw(enemies[i].getSprite());
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		m_window.draw(bullets[i].m_shape);
	}

	m_window.draw(m_player->getSprite());

	//Draw HUD Stuff
	m_window.draw(m_scoreText);
	m_window.draw(m_scorePreText);
	m_window.draw(m_healthText);
	m_window.draw(m_healthPreText);
	m_window.draw(m_controlModeText);
	m_window.draw(m_controlModePreText);

	/*m_window.draw(hudMapBack);
	m_window.draw(hudPlayerMap);*/
	
	if (m_gameState == GameState::DeathScreen)
	{
		//Draw GameplayStuff


		//Draw HUD Stuff
		m_window.setView(m_window.getDefaultView());
		m_window.draw(m_deathScreenSprite);
	}

	else if (m_gameState == GameState::WinScreen)
	{
		//Draw GameplayStuff


		//Draw HUD Stuff
		m_window.setView(m_window.getDefaultView());
		m_window.draw(m_winScreenSprite);
	}

	m_window.display();
}



/// <summary>
/// load the textures and fonts,setup of sprites
/// </summary>
void Game::setupSprite()
{
	if (!m_deathScreenTexture.loadFromFile("ASSETS\\IMAGES\\deathScreen.png"))
	{
		std::cout << "problem loading death screen" << std::endl;
	}
	m_deathScreenSprite.setTexture(m_deathScreenTexture);
	m_deathScreenSprite.setPosition(0, 0);

	if (!m_winScreenTexture.loadFromFile("ASSETS\\IMAGES\\winScreen.png"))
	{
		std::cout << "problem loading win screen" << std::endl;
	}
	m_winScreenSprite.setTexture(m_winScreenTexture);
	m_winScreenSprite.setPosition(0, 0);

	//if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\floorBoard.png"))
	//{
	//	// simple error message if previous call fails
	//	std::cout << "problem loading logo" << std::endl;
	//}
	//m_logoSprite.setPosition(-200, - 200);
	//m_logoSprite.setScale(sf::Vector2f(0.75, 0.75));
	//m_logoTexture.setRepeated(true);
	//m_logoSprite.setTexture(m_logoTexture);
	//m_logoSprite.setTextureRect(sf::IntRect(0, 0, 3000, 3000));
	//m_logoSprite.setPosition(-300, -300);

	if (!m_scoreFont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_scorePreText.setFillColor(sf::Color::White);
	m_scorePreText.setFont(m_scoreFont);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setFont(m_scoreFont);

	m_healthPreText.setFillColor(sf::Color::White);
	m_healthPreText.setFont(m_scoreFont);
	m_healthText.setFillColor(sf::Color::White);
	m_healthText.setFont(m_scoreFont);

	m_controlModePreText.setFillColor(sf::Color::White);
	m_controlModePreText.setFont(m_scoreFont);

	m_controlModeText.setFillColor(sf::Color::White);
	m_controlModeText.setFont(m_scoreFont);

	//if (!m_nestTexture.loadFromFile("ASSETS\\IMAGES\\nest.png"))
	//{
	//	std::cout << "problem loading nest" << std::endl;
	//}
	//m_nestSprite.setTexture(m_nestTexture);
	//m_nestSprite.setScale(sf::Vector2f(0.2, 0.2));

	hudMapBack.setSize(sf::Vector2f(m_window.getView().getSize().x / 10, m_window.getView().getSize().y / 10));
	hudMapBack.setFillColor(sf::Color::White);
	hudMapBack.setPosition(m_player->getPosition().x - 500, m_player->getPosition().y - 350);

	hudPlayerMap.setFillColor(sf::Color::Red);
	hudPlayerMap.setRadius(4);

	hudWorkerMap.setFillColor(sf::Color::Blue);
	hudWorkerMap.setRadius(2);

	hudEnemyMap.setFillColor(sf::Color::Green);
	hudEnemyMap.setRadius(3);
}
