#include "Bullet.h"

Bullet::Bullet(float radius)
{
	m_velocity = sf::Vector2f(0, 0);
	m_maxSpeed = 15.0f;

	this->m_shape.setRadius(radius);
	this->m_shape.setFillColor(sf::Color::Red);
}