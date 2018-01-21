#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

/*
NOTE: Currently not used in project, see Enemy.h and Enemy.cpp for the worker objects
*/

class Worker
{
public:
	Worker();
	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
	float m_maxSpeed;



	void Initialise();
	void Update();

	sf::Texture getTexture() { return m_texture; }
	sf::Sprite getSprite() { return m_sprite; }
	sf::Vector2f getVelocity() { return m_velocity; }
	sf::Vector2f getPosition() { return m_position; }

	void setPosition(sf::Vector2f pos) { m_position = pos; }

	void setTexture(sf::Texture newTexture) { m_texture = newTexture; }
	void setSprite(sf::Sprite newSprite) { m_sprite = newSprite; }

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::FloatRect workerCol;
	sf::RectangleShape workerColBox;
};
