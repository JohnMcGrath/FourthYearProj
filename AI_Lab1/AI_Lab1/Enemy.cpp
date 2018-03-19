#pragma once
#include "Enemy.h"

Enemy::Enemy() {}

/// <summary>
/// Handles Movement
/// </summary>
void Enemy::HandleInput(sf::Vector2f t, int typeOfMovement) {
	
	if (Magnitude(t - m_position) < 350)
	{
		m_state = EnemyState::Hostile;
	}
	/*else
	{
		m_state = EnemyState::Passive;
	}*/

	if (m_state == EnemyState::Hostile)
	{
		if (typeOfMovement == 0)
		{
			m_velocity = t - m_position;
			m_velocity = Normalise(m_velocity);
			m_velocity * m_maxSpeed;
		}

		//Algorithm for seeking a target
		if (typeOfMovement == 1)
		{
			float timeToTarget = 0.5f;
			m_velocity = t - m_position;

			m_velocity *= timeToTarget;
			float l = Magnitude(m_velocity);
			if (l > m_maxSpeed)
			{
				m_velocity = Normalise(m_velocity);
				m_velocity *= m_maxSpeed;
			}

			//If the enemies seeks, it will also fire at the enemy
			FireBullets(t);
		}

		//Algorithm for wandering
		//Used by workers
		if (typeOfMovement == 2)
		{
			float dist = 1000;
			float rad = 700;
			sf::Vector2f travelPoint = Normalise(m_velocity) * dist;
			travelPoint += m_position;

			if (timer >= 50)
			{
				timer = 0;
				randAngle = (rand() % 75 + 15);
			}

			else
			{
				timer++;
			}

			newTravelPoint = sf::Vector2f((rad * sin(randAngle) + newTravelPoint.x), (rad * cos(randAngle) + newTravelPoint.y));
			m_velocity = newTravelPoint - m_position;
			m_velocity = Normalise(m_velocity);
			m_velocity * m_maxSpeed;
		}

		//Algorithm For the Swarming behaviour
		//Used by Predators
		if (typeOfMovement == 3)
		{
			float timeToTarget = 0.25f;

			m_velocity = t - m_position;

			m_velocity *= timeToTarget;
			float l = Magnitude(m_velocity);
			if (l > m_maxSpeed)
			{
				m_velocity = Normalise(m_velocity);
				if (posInSwarm == 0)
				{
					m_velocity *= m_maxSpeed;
				}
				else
				{
					m_velocity *= (m_maxSpeed* (1 / (posInSwarm + .1f)));
				}
			}
			//If the enemies seeks, it will also fire at the enemy
			FireBullets(t);
		}
	}

}

/// <summary>
/// Fire Bullets at target position
/// </summary>
void Enemy::FireBullets(sf::Vector2f target) 
{
	
	if (bulletCounter < 60 * 1.2f)
	{
		bulletCounter++;
	}

	else
	{
		bulletCounter = 0;
		b.m_shape.setPosition(m_sprite.getPosition());

		//Bullets coloured green so they're easy to identify
		b.m_shape.setFillColor(sf::Color::Green);

		b.m_velocity = aimDirNormal * b.m_maxSpeed;
		m_soundManager->playSound("enemyGun1");
		bullets.push_back(b);
	}

	enemyCentre = sf::Vector2f(m_sprite.getPosition());
	aimDir = target - enemyCentre;
	aimDirNormal = Normalise(aimDir);

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].m_shape.move(bullets[i].m_velocity);

		//If the distance is great than 600, delete the bullet
		if (Magnitude(bullets[i].m_shape.getPosition() - m_sprite.getPosition()) > 300)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
	}
}

/// <summary>
/// Adjust velocity according to orientation
/// </summary>
float Enemy::orientate()
{
	float l = Magnitude(m_velocity);
	if (l > 0)
	{
		return ((atan2(m_velocity.x, -m_velocity.y)) * 180 / 3.142);
	}
	else
	{
		return m_orientation;
	}
}


float Enemy::Magnitude(sf::Vector2f v)
{
	return sqrt((v.x*v.x) + (v.y*v.y));
}

sf::Vector2f Enemy::Normalise(sf::Vector2f v)
{
	float temp = Magnitude(v);
	if (temp > 0)
	{
		return sf::Vector2f((v.x / temp), (v.y / temp));
	}
	else
		return v;

}

/// <summary>
/// Initialisation
/// </summary>
void Enemy::Initialise(int color, SoundManager * soundMang) {
	m_soundManager = soundMang;
	if (color == 2)
	{
		if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Worker.png"))
		{
			// simple error message if previous call fails
			std::cout << "problem loading logo" << std::endl;
		}
		m_orientation = rand() % 360;
		m_velocity = sf::Vector2f(rand() % -100 + 200, rand() % 50);
		m_maxSpeed = 0.1f;
		m_sprite.setScale(sf::Vector2f(0.075, 0.075));
	}

	else
	{
		if (!m_texture.loadFromFile("ASSETS\\IMAGES\\soldier.png"))
		{
			// simple error message if previous call fails
			std::cout << "problem loading logo" << std::endl;
		}
		m_sprite.setScale(sf::Vector2f(0.2, 0.2));
	}

	if (color == 1) m_sprite.setColor(sf::Color::Green);
	if (color == 2) m_sprite.setColor(sf::Color::Blue);
	if (color == 3) m_sprite.setColor(sf::Color::Cyan);
	if (color == 4) m_sprite.setColor(sf::Color::Red);
	m_sprite.setOrigin(75, 225);
	m_sprite.setTexture(m_texture);
}

/// <summary>
/// Gets an SF RectShape to represent an objects collision
/// </summary>
sf::RectangleShape Enemy::getCollisionBox() 
{
	enemyCol = m_sprite.getGlobalBounds();
	enemyColBox.setSize(sf::Vector2f(enemyCol.width, enemyCol.height));
	enemyColBox.setPosition(sf::Vector2f(enemyCol.left, enemyCol.height));

	return enemyColBox;
}

/// <summary>
/// Update Loop
/// </summary>
void Enemy::Update(sf::Vector2f t, sf::Vector2f screenSize, int typeOfMovement) {
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(m_position);
	m_orientation = orientate();
	m_sprite.setRotation(m_orientation);
	HandleInput(t, typeOfMovement);
	m_position = m_position += m_velocity;
}