#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

enum Controller
{
	KeyboardContr = 0,
	JoystickContr = 1,
	TouchScreenContr = 2
};

enum GameState
{
	Gameplaying = 0,
	DeathScreen = 1,
	WinScreen = 2
};

enum GameMode
{
	Arcade = 0,
	Simulation = 1,
	StrawMan = 2
};

class Player
{
public:
	/// <summary>
	///Player contructor
	/// <summary>
	Player();

	/// <summary>
	///Handle all input
	/// <summary>
	void HandleInput(int controlMode);

	/// <summary>
	///Initialiseation Function
	/// <summary>
	void Initialise();

	/// <summary>
	///Update loop
	/// <summary>
	void Update(sf::Vector2f centrePoint, int controlMode);

	/// <summary>
	///Getters
	/// <summary>
	sf::Vector2f getVelocity() { return m_velocity; }
	sf::Vector2f getPosition() { return m_position; }
	float getOrientation() { return m_orientation; }
	sf::Texture getTexture() { return m_texture; }
	sf::Sprite getSprite() { return m_sprite; }
	int getHealth() { return m_health; }
	bool getInvincible() { return invincile; }

	/// <summary>
	///Setters
	/// <summary>
	void setVelocity(sf::Vector2f newVelocity) { m_velocity = newVelocity; }
	void setPosition(sf::Vector2f newPosition) { m_position = newPosition; }
	void setOrientation(float newOrientation) { m_orientation = newOrientation; }
	void setTexture(sf::Texture newTexture) { m_texture = newTexture; }
	void setSprite(sf::Sprite newSprite) { m_sprite = newSprite; }
	void reduceHealth(int h) { m_health -= h; }
	void setHeatlth(int h) { m_health = h; }
	void setInvincible(bool tf) { invincile = tf; }

	/// <summary>
	///Used for guiding the player's velocity
	/// <summary>
	void steerPlayer(sf::Vector2f);

	/// <summary>
	///Used if player wants to teleport once leaving the screen
	///Currently not used
	/// <summary>
	void WrapAround(sf::Vector2f screenSize);

	/// <summary>
	///Math Tools
	/// <summary>
	float Magnitude(sf::Vector2f v);
	sf::Vector2f Normalise(sf::Vector2f v);
	float DotProduct(sf::Vector2f v1, sf::Vector2f v2);
	float AngleBetweenVectors(sf::Vector2f v1, sf::Vector2f v2);
	void setWallSprites(std::vector<sf::Sprite> *sprites)
	{
		m_copyOfWalls = sprites;
	}
	
	void checkWallCollision();

	/// <summary>
	///Adjust's player's velocity by orientation
	/// <summary>
	void orientate(sf::Vector2f target, int controlMode);

	/// <summary>
	///Timer used to represent how long a player is invincible after taking damage
	/// <summary>
	int invinTimer = 0;

	sf::Vector2f getStartingPosition() { return m_startingPosition; }

private:
	/// <summary>
	///Vector used when a small temporary value is needed
	/// <summary>
	sf::Vector2f tempVec;

	/// <summary>
	///Velocity
	/// <summary>
	sf::Vector2f m_velocity;

	/// <summary>
	///Position
	/// <summary>
	sf::Vector2f m_position = sf::Vector2f(300, 300);

	/// <summary>
	///Orientation
	/// <summary>
	float m_orientation = 0;

	/// <summary>
	///How were they previously orientation
	/// <summary>
	float m_lastOrient = 0;

	/// <summary>
	///Max speed
	/// <summary>
	float m_maxSpeed = 2.5f;

	/// <summary>
	///Sprite and Texture
	/// <summary>
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	/// <summary>
	///Health 
	/// <summary>
	int m_health = 100;

	/// <summary>
	///Whether is currently invinsible
	/// <summary>
	bool invincile = false;

	bool m_touchControlPressOnceA = false;
	bool m_touchControlPressOnceD = false;

	bool m_touchControlIsFiring = false;

	std::vector<sf::Sprite>* m_copyOfWalls;

	sf::Vector2f m_previousPos;

	sf::Vector2f m_startingPosition{ 300, 300 };
};
