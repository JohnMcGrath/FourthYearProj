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
	m_velocity * acceleration();
}

/// <summary>
/// Adjusts the player's velocity accord to their orientation
/// </summary>
void Player::orientate(sf::Vector2f target, int controlMode)
{
	if (controlMode == 0 || controlMode == 1)
	{
		m_orientation = (atan2(target.x, -target.y)); //As radians
	}
}

float Player::acceleration()
{
	if (m_gameMode == GameMode::Arcade)
	{
		if (m_currentSpeed < m_maxSpeed)
		{
			m_acceleration = 1.2;

			if (m_currentSpeed == 0)
			{
				m_currentSpeed = 0.4f;
			}
			m_currentSpeed *= m_acceleration;

			if (m_currentSpeed > m_maxSpeed)
			{
				m_currentSpeed = m_maxSpeed;
			}
			std::cout << "Speed: " << m_currentSpeed << std::endl;
		}
	}
		
	else if (m_gameMode == GameMode::Simulation)
	{
		if (m_currentSpeed < m_maxSpeed)
		{
			m_acceleration = 0.1f;
			if (m_currentSpeed == 0)
			{
				m_currentSpeed = 0.2f;
			}
			m_currentSpeed += m_acceleration;

			if (m_currentSpeed > m_maxSpeed)
			{
				m_currentSpeed = m_maxSpeed;
			}
			std::cout << "Speed: " << m_currentSpeed << std::endl;
		}
	}

	else
	{
		m_currentSpeed = m_maxSpeed;
		std::cout << "Speed: " << m_currentSpeed << std::endl;
		return m_maxSpeed;
	}

	
	return m_currentSpeed;
}

/// <summary>
/// Handles all keyboard keys and what they do
/// </summary>
void Player::HandleInput(int controlMode)
{
	//Boost forward
	float x = sin(getOrientation());
	float y = -cos(getOrientation());

	//Mouse&Keyboard
	if (controlMode == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (!m_KeyboardPressOnceW)
			{
				std::cout << "W" << std::endl;
				m_currentSpeed = 0;
			}

			m_KeyboardPressOnceW = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_position = m_position + sf::Vector2f(0, -acceleration() / 1.5);
			}
			else
			{
				m_position = m_position + sf::Vector2f(0, -acceleration());
			}
		}

		else
		{
			m_KeyboardPressOnceW = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (!m_KeyboardPressOnceS)
			{
				std::cout << "S" << std::endl;
				m_currentSpeed = 0;
			}

			m_KeyboardPressOnceS = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_position = m_position + sf::Vector2f(0, acceleration() / 1.5);
			}
			else
			{
				m_position = m_position + sf::Vector2f(0, acceleration());
			}
		}

		else
		{
			m_KeyboardPressOnceS;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (!m_KeyboardPressOnceA)
			{
				std::cout << "A" << std::endl;
				m_currentSpeed = 0;
			}
			m_KeyboardPressOnceA = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				m_position = m_position + sf::Vector2f(-acceleration() / 1.5, 0);
			}
			else
			{
				m_position = m_position + sf::Vector2f(-acceleration(), 0);
			}
		}

		else
		{
			m_KeyboardPressOnceA = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (!m_KeyboardPressOnceD)
			{
				std::cout << "D" << std::endl;
				m_currentSpeed = 0;
			}

			m_KeyboardPressOnceD = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				m_position = m_position + sf::Vector2f(acceleration() / 1.5, 0);
			}
			else
			{
				m_position = m_position + sf::Vector2f(acceleration(), 0);
			}
		}
		else
		{
			m_KeyboardPressOnceD = false;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			setVelocity(sf::Vector2f(0, 0));
			m_currentSpeed = 0;
		}
	}

	//Controller
	if (controlMode == 1)
	{
		tempVec.x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
		tempVec.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);

		if ((tempVec.x > 5) || (tempVec.x < -5))
		{
			if (!m_JoystickLeftMovedOnce)
			{
				m_currentSpeed = 0;
			}
			m_JoystickLeftMovedOnce = true;
			m_position = m_position += (sf::Vector2f(acceleration() * (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100), 0));
		}
		else
		{
			m_JoystickLeftMovedOnce = false;
		}

		if ((tempVec.y > 5) || (tempVec.y < -5))
		{
			if (!m_JoystickRightMovedOnce)
			{
				m_currentSpeed = 0;
			}
			m_JoystickRightMovedOnce = true;
			m_position = m_position += sf::Vector2f(0, acceleration() * (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 100));
		}
		else
		{
			m_JoystickRightMovedOnce = false;
		}

		if ((tempVec.x < 5) && (tempVec.x > -5) &&
			(tempVec.y < 5) && (tempVec.y > -5))
		{
			std::cout << "Decel" << std::endl;
			m_currentSpeed = 0;
		}
	}

	//TouchScreen
	if (controlMode == 2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			steerPlayer(sf::Vector2f(x, y));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			steerPlayer(sf::Vector2f(-x, -y));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !m_touchControlPressOnceA)
		{
			m_touchControlPressOnceA = true;
			setOrientation(getOrientation() - (45 / (180 / 3.142)));
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_touchControlPressOnceA == true)
		{
			m_touchControlPressOnceA = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true && m_touchControlPressOnceD == false)
		{
			std::cout << getOrientation() << std::endl;
			m_touchControlPressOnceD = true;
			setOrientation(getOrientation() + (45 / (180 / 3.142)));
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == false && m_touchControlPressOnceD == true)
		{
			m_touchControlPressOnceD = false;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			setVelocity(sf::Vector2f(0, 0));
			m_currentSpeed = 0;
		}
	}
	
}

float Player::DotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}

float Player::AngleBetweenVectors(sf::Vector2f v1, sf::Vector2f v2)
{
	return ((DotProduct(v1, v2)) / (Magnitude(v1)*Magnitude(v2)));
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
	m_sprite.setPosition(m_startingPosition);
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

void Player::checkWallCollision()
{
	for (int i = 0; i < m_copyOfWalls->size(); i++)
	{
		if (m_sprite.getGlobalBounds().intersects(m_copyOfWalls->at(i).getGlobalBounds()))
		{
			std::cout << "Touching Wall" << std::endl;
		}
	}
}

/// <summary>
///Update loop for the player
/// <summary>
void Player::Update(sf::Vector2f centrePoint, int controlMode) {
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation * (180 / 3.14));
	HandleInput(controlMode);
	m_velocity = Normalise(m_velocity);
	setPosition(m_position + (sf::Vector2f(getVelocity().x*m_maxSpeed,getVelocity().y*m_maxSpeed)));
}