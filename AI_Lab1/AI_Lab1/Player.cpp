#pragma once
#include "Player.h"

Player::Player() {}

/// <summary>
/// Guides the player's character
/// </summary>
/// <param name="t">Where the player is to go next</param>
void Player::steerPlayer(sf::Vector2f t)
{
	m_velocity = (m_position + t) - m_position;
	m_velocity = Normalise(m_velocity);
	m_velocity * m_maxSpeed;
}

/// <summary>
/// Adjusts the player's velocity accord to their orientation
/// </summary>
float Player::orientate()
{
	std::cout << "Win";
	float l = Magnitude(m_velocity);
	if (l > 0)
	{
		std::cout << "Win";
		return ((atan2(m_velocity.x, -m_velocity.y)) * 180 / 3.142);
	}
	else
	{
		std::cout << "Lose";
		return m_orientation;
	}
}

/// <summary>
/// Handles all keyboard keys and what they do
/// </summary>
void Player::HandleInput()
{
	//Boost forward
	float x = sin(getOrientation());
	float y = -cos(getOrientation());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		steerPlayer(sf::Vector2f(x, y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		steerPlayer(sf::Vector2f(-x, -y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//Rotate
		setOrientation(getOrientation() - (4 / (180 / 3.142)));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//Rotate
		setOrientation(getOrientation() + (4 / (180 / 3.142)));
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		setVelocity(sf::Vector2f(0, 0));
	}
}

/// <summary>
///Math formula for distance
/// <summary>
float Player::Magnitude(sf::Vector2f v)
{
	return sqrt((v.x*v.x) + (v.y*v.y));
}

/// <summary>
///Math formula for normalising a vector
/// <summary>
sf::Vector2f Player::Normalise(sf::Vector2f v)
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
///Initialisation function
/// <summary>
void Player::Initialise() {
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\soldier.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.25, 0.25));
	m_sprite.setPosition(sf::Vector2f(300, 300)); 
	m_sprite.setOrigin(75,225);
}

/// <summary>
/// Function used if player wants to teleport after reachign
/// end of screen, currently not used
/// <summary>
void Player::WrapAround(sf::Vector2f screenSize) 
{
	if (m_position.x + m_sprite.getLocalBounds().width <= 0)
	{
		m_position.x = screenSize.x - 1;
	}
	if (m_position.x  > screenSize.x)
	{
		m_position.x = -1 - m_sprite.getLocalBounds().width;
	}
	if (m_position.y + m_sprite.getLocalBounds().height <= 0)
	{
		m_position.y = screenSize.y - 1;
	}
	if (m_position.y  > screenSize.y)
	{
		m_position.y = -1 - m_sprite.getLocalBounds().height;
	} 
}

/// <summary>
///Update loop for the player
/// <summary>
void Player::Update(sf::Vector2f centrePoint) {
	
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation * (180 / 3.14));
	HandleInput();
	m_velocity = Normalise(m_velocity);
	setPosition(m_position + (sf::Vector2f(getVelocity().x*m_maxSpeed,getVelocity().y*m_maxSpeed)));
}