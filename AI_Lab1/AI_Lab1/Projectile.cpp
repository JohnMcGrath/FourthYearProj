#pragma once
#include "Projectile.h"

Projectile::Projectile() 
{
	Initialise();
}

float Projectile::orientate()
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

float Projectile::Distance(sf::Vector2f t)
{
	return sqrt(((t.x - m_position.x)*(t.x - m_position.x)) + ((t.y - m_position.y)*(t.y - m_position.y)));
}

float Projectile::Magnitude(sf::Vector2f v)
{
	return sqrt((v.x*v.x) + (v.y*v.y));
}

sf::Vector2f Projectile::Normalise(sf::Vector2f v)
{
	float temp = Magnitude(v);
	if (temp > 0)
	{
		return sf::Vector2f((v.x / temp), (v.y / temp));
	}
	else
		return v;

}

void Projectile::Initialise() {
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\projectile.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_orientation = 0;
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.5, 0.5));
}

void Projectile::Update(sf::Vector2f position, float orientation) {
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	if (!isFlying) {
		m_position = sf::Vector2f((50 * cos(orientation)) + position.x, (50 * sin(orientation)) + position.y);
		m_sprite.setPosition(m_position);
		m_orientation = orientation;
	}

	m_sprite.setRotation(m_orientation * (180 / 3.14));
	m_position = m_position += m_velocity;
}