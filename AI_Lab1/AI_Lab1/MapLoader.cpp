#include "MapLoader.h"
#include <iostream>

MapLoader::MapLoader()
{
	m_rows.push_back(m_row0);
	m_rows.push_back(m_row1);
	m_rows.push_back(m_row2);
	m_rows.push_back(m_row3);
	m_rows.push_back(m_row4);
	m_rows.push_back(m_row5);
	m_rows.push_back(m_row6);
	m_rows.push_back(m_row7);
	m_rows.push_back(m_row8);
	m_rows.push_back(m_row9);

	Init();
}

void MapLoader::Init()
{
	if (!m_wallTexture.loadFromFile("ASSETS\\IMAGES\\wallSprite.png"))
	{
		std::cout << "Error loading wallTexture" << std::endl;
	}

	m_wallSprite.setTexture(m_wallTexture);
	if (!m_floorTexture.loadFromFile("ASSETS\\IMAGES\\floorBoard.png"))
	{
		std::cout << "Error loading floorTexture" << std::endl;
	}
	m_floorSprite.setTexture(m_floorTexture);

	for (int i = 0; i < m_row0.size(); i++)
	{
		std::cout << "" << std::endl;
		for (int j = 0; j < m_rows.size(); j++)
		{
			if (m_rows.at(i).at(j) == 1)
			{
				std::cout << "||";
				m_tempSprite.setPosition(sf::Vector2f(128 * i, 128 * j));
				m_tempSprite.setTexture(m_wallTexture);
				m_tempSprite.setScale(sf::Vector2f(0.5f,0.5f));
				m_sprites.push_back(m_tempSprite);
				//m_wallPos.push_back(sf::FloatRect(256 * i, 256 * j, 256, 256));
			}
			else
			{
				std::cout << "  ";
				m_tempSprite.setPosition(sf::Vector2f(128 * i, 128 * j));
				m_tempSprite.setTexture(m_floorTexture);
				m_tempSprite.setScale(sf::Vector2f(0.5f, 0.5f));
				m_sprites.push_back(m_tempSprite);
				//m_floorPos.push_back(sf::FloatRect(256 * i, 256 * j, 256, 256));
			}
			
		}
	}
	
}

void MapLoader::Draw(sf::RenderWindow* window)
{
	//std::cout << "Drawing Walls" << std::endl;
	//for (int i = 0; i << m_wallPos.size(); i++)
	//{
	//	//std::cout << "Wall" << std::endl;
	//	m_wallSprite.setPosition(sf::Vector2f(m_wallPos.at(i).left, m_wallPos.at(i).top));
	//	window->draw(m_wallSprite);
	//}
	//for (int j = 0; j << m_floorPos.size(); j++)
	//{
	//	m_floorSprite.setPosition(sf::Vector2f(m_floorPos.at(j).left, m_floorPos.at(j).top));
	//	window->draw(m_floorSprite);
	//}
	for (int i = 0; i < m_sprites.size(); i++)
	{
		window->draw(m_sprites[i]);
	}
}