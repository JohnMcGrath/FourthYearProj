#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
public:
	/// <summary>
	/// Bullet's shape
	/// <summary>
	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
	float m_maxSpeed;

	Bullet(float radius = 5.f);
};