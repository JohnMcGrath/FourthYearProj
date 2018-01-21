#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Projectile
{
public:
	Projectile();
	~Projectile();



	//void HandleInput(sf::Vector2f t, int typeOfMovement);
	void Initialise();
	void Update(sf::Vector2f position, float orientation);

	void setVelocity(sf::Vector2f newVelocity) { m_velocity = newVelocity; }
	void setPosition(sf::Vector2f newPosition) { m_position = newPosition; }
	void setOrientation(float newOrientation) { m_orientation = newOrientation; }

	float orientate();
	void WrapAround(sf::Vector2f screenSize);

	float Magnitude(sf::Vector2f v);
	float Distance(sf::Vector2f t);
	sf::Vector2f Normalise(sf::Vector2f v);

	sf::Vector2f getVelocity() { return m_velocity; }
	sf::Vector2f getPosition() { return m_position; }
	float getOrientation() { return m_orientation; }

	void setTexture(sf::Texture newTexture) { m_texture = newTexture; }
	void setSprite(sf::Sprite newSprite) { m_sprite = newSprite; }

	sf::Texture getTexture() { return m_texture; }
	sf::Sprite getSprite() { return m_sprite; }

private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	float m_orientation;
	float m_maxSpeed = 2.5f;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool isFlying = false;
};
