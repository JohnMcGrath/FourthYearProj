#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

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
	void HandleInput();

	/// <summary>
	///Initialiseation Function
	/// <summary>
	void Initialise();

	/// <summary>
	///Update loop
	/// <summary>
	void Update(sf::Vector2f centrePoint);

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
	void setHealth(int h) { m_health -= h; }
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

	/// <summary>
	///Adjust's player's velocity by orientation
	/// <summary>
	float orientate();

	/// <summary>
	///Timer used to represent how long a player is invincible after taking damage
	/// <summary>
	int invinTimer = 0;

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
};
