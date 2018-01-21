#ifndef GAME
#define GAME

#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "math.h"
#include "Worker.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>

class Player;
class Enemy;
class Projectile;
class Bullet;
class Worker;
class sf::CircleShape;

static const float VIEW_HEIGHT = 1080.0f;

class Game
{
public:
	/// <summary>
	/// Pointer to the player object
	/// <summary>
	Player * m_player = new Player();

	/// <summary>
	///Blueprint for the Enemies that Spawn from Nests
	/// <summary>
	Enemy e1;
	std::vector<Enemy> enemies;

	/// <summary>
	/// Blueprint for the Workers
	/// <summary>
	Enemy e2;
	std::vector<Enemy> workersEns;

	/// <summary>
	///Blueprint for the boids
	/// <summary>
	Enemy e3;
	std::vector<Enemy> boids;

	/// <summary>
	///Blueprint for the boids
	/// <summary>
	Enemy e4;
	std::vector<Enemy> predators;

	/// <summary>
	///Bullets used by entities
	/// <summary>
	Bullet  b1;
	std::vector<Bullet> bullets;

	std::vector<sf::CircleShape> hudEnemiesEls;

	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void ResizeView(const sf::RenderWindow& window, sf::View view);
	void setupSprite();

	/// <summary>
	///Handle Classes for game entities
	/// <summary>
	void EnemyHandler();
	void WorkerHandler();
	void BulletHandler();
	void HUDHandler();

	/// <summary>
	///Checks for the nearest worker object, causes frame stutter upon starting app if used
	/// <summary>
	sf::Vector2f CheckForNearestWorker(sf::Vector2f currentPos);

	/// <summary>
	/// main SFML window
	/// <summary>

	sf::RenderWindow m_window; 
	/// <summary>
	///View that Follows the player
	/// <summary>
	sf::View playerView;

	/// <summary>
	/// texture and sprite used for background
	/// <summary>
	sf::Texture m_logoTexture; 
	sf::Sprite m_logoSprite; 

	/// <summary>
	/// control exiting game
	/// <summary>
	bool m_exitGame;

	/// <summary>
	///centre of screen
	/// <summary>
	sf::Vector2f centrePoint;

	sf::Texture m_nestTexture;
	sf::Sprite m_nestSprite;
	std::vector<sf::Sprite> nests;

	/// <summary>
	/// Vectors used in calculationg where the player is aiming
	/// <summary>
	sf::Vector2f playerCentre;
	sf::Vector2f cursorPos;
	sf::Vector2f aimDir;
	sf::Vector2f normalisedAimDir;

	/// <summary>
	///Counters used on things that continuosly spawn
	/// <summary>
	int spawnCounter = 40;
	int workerCounter = 20;
	int bulletCounter = 10;

	/// <summary>
	///player's score
	/// <summary>
	int score = 0;

	/// <summary>
	/// Floats and rectShapes used to represent bounding boxes
	/// Using .getLocalBounds on objects in vector caused some issues
	/// but this resolves them
	/// <summary>
	sf::FloatRect bulletBound;
	sf::RectangleShape bulletBoundShape;
	sf::FloatRect enemyBound;
	sf::RectangleShape enemyBoundShap;
	sf::FloatRect workerBound;
	sf::RectangleShape workerBoundShape;
	sf::FloatRect playerBound;
	sf::RectangleShape playerBoundShap;

	/// <summary>
	///Font used by all text
	/// <summary>
	sf::Font m_scoreFont;

	/// <summary>
	/// Score UI Hud
	/// <summary>
	sf::Text m_scoreText;
	sf::Text m_scorePreText;

	/// <summary>
	///Health UI Hud
	/// <summary>
	sf::Text m_healthText;
	sf::Text m_healthPreText;

	int nestCounter = 0;

	/// <summary>
	///Radar Hud
	/// <summary>
	sf::RectangleShape hudMapBack;
	sf::CircleShape hudPlayerMap;
	sf::CircleShape hudEnemyMap;
	sf::CircleShape hudWorkerMap;
	sf::CircleShape hudBoidMap;
};

#endif