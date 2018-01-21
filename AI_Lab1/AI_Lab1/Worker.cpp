#include "Worker.h"

Worker::Worker() {}

void Worker::Initialise() 
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\worker.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.1, 0.1));
	m_sprite.setPosition(m_position);
}
void Worker::Update()
{
	workerCol = m_sprite.getGlobalBounds();
	workerColBox.setSize(sf::Vector2f(workerCol.width, workerCol.height));
	workerColBox.setPosition(sf::Vector2f(workerCol.top, workerCol.height));
	m_sprite.setPosition(m_position);
}