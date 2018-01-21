#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

class Bullet;

class Enemy
{
public:
	/// <summary>
	/// Base bullets that all bullets are copied from
	/// <summary>
	Bullet b;

	/// <summary>
	///Vector used to store bullets
	/// <summary>
	std::vector<Bullet> bullets;

	/// <summary>
	///Constructor
	/// <summary>
	Enemy();


	/// <summary>
	///Fires bullets in the direction of the target
	/// <summary>
	///<param name= target>Where the bullet is to be aimed at</param>
	void FireBullets(sf::Vector2f target);

	/// <summary>
	/// Handles enemy movement
	/// <summary>
	void HandleInput(sf::Vector2f t, int typeOfMovement);

	/// <summary>
	///Initialisation
	/// <summary>
	void Initialise(int color);

	/// <summary>
	///Update Loop
	/// <summary>
	void Update(sf::Vector2f t, sf::Vector2f screenSize, int typeOfMovement);

	/// <summary>
	/// Getters
	/// <summary>
	std::vector<Bullet> getBullets() { return bullets; }
	sf::Vector2f getVelocity() { return m_velocity; }
	sf::Vector2f getPosition() { return m_position; }
	float getOrientation() { return m_orientation; }
	sf::Texture getTexture() { return m_texture; }
	sf::Sprite getSprite() { return m_sprite; }
	sf::RectangleShape getCollisionBox();
	int getHitsTaken() { return m_hitsTaken; }
	int getPosInSwarm() { return posInSwarm; }

	/// <summary>
	///Setters
	/// <summary>
	void setVelocity(sf::Vector2f newVelocity) { m_velocity = newVelocity; }
	void setPosition(sf::Vector2f newPosition) { m_position = newPosition; }
	void setOrientation(float newOrientation) { m_orientation = newOrientation; }
	void setTexture(sf::Texture newTexture) { m_texture = newTexture; }
	void setSprite(sf::Sprite newSprite) { m_sprite = newSprite; }
	void addHitsTaken(int hit) { m_hitsTaken += hit; }
	void setPosInSwarm(int newPos) { posInSwarm = newPos; }

	/// <summary>
	/// CHnage's velocity according to orientation
	/// <summary>
	float orientate();

	/// <summary>
	/// Math Tools
	/// <summary>
	float Magnitude(sf::Vector2f v);
	sf::Vector2f Normalise(sf::Vector2f v);

private:
	/// <summary>
	/// Velocity, Position, Orientation and MaxSpeed
	/// <summary>
	sf::Vector2f m_velocity;
	sf::Vector2f m_position = sf::Vector2f(500, 500);
	float m_orientation;
	float m_maxSpeed = 2.5f;

	/// <summary>
	/// Textures and Sprites
	/// <summary>
	sf::Texture m_texture;
	sf::Texture m_nestTexture;
	sf::Sprite m_sprite; 

	/// <summary>
	/// Timer
	/// <summary>
	int timer = 40;

	/// <summary>
	/// New Target Destination
	/// <summary>
	sf::Vector2f newTravelPoint;

	/// <summary>
	/// Random Angle (for wander movement)
	/// <summary>
	float randAngle;

	/// <summary>
	///Rects used for bounding box
	/// <summary>
	sf::FloatRect enemyCol;
	sf::RectangleShape enemyColBox;
	
	/// <summary>
	/// Time Between shots
	/// <summary>
	int bulletCounter;

	/// <summary>
	/// Used for aiming at a target 
	/// <summary>
	sf::Vector2f enemyCentre;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNormal;

	/// <summary>
	/// Amount of shots an enemies taken
	/// <summary>
	int m_hitsTaken = 0;

	/// <summary>
	/// Vector used to represent sopt on the radar
	/// <summary>
	sf::Vector2f hudPos;
	sf::CircleShape hudShape;

	int posInSwarm;
};