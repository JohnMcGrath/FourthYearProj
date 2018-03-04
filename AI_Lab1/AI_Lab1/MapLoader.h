#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class MapLoader
{
public:
	MapLoader();
	void Init();
	void Render();
	void Draw(sf::RenderWindow* window);
	std::vector<sf::Sprite> getSprites() { return m_sprites; }

private:
	std::vector<int> m_row0 = { 1,1,1,1,1,1,1,1,1,1 };
	std::vector<int> m_row1 = { 1,1,0,0,0,0,0,0,0,1 };
	std::vector<int> m_row2 = { 1,0,1,0,0,0,0,0,0,1 };
	std::vector<int> m_row3 = { 1,0,0,1,0,0,0,0,0,1 };
	std::vector<int> m_row4 = { 1,0,0,0,1,0,0,0,0,1 };
	std::vector<int> m_row5 = { 1,0,0,0,0,1,0,0,0,1 };
	std::vector<int> m_row6 = { 1,0,0,0,0,0,1,0,0,1 };
	std::vector<int> m_row7 = { 1,0,0,0,0,0,0,1,0,1 };
	std::vector<int> m_row8 = { 1,0,0,0,0,0,0,0,1,1 };
	std::vector<int> m_row9 = { 1,1,1,1,1,1,1,1,1,1 };

	std::vector<std::vector<int>> m_rows;
	sf::Sprite m_wallSprite;
	sf::Sprite m_tempSprite;
	sf::Texture m_wallTexture;
	sf::Sprite m_floorSprite;
	sf::Texture m_floorTexture;
	std::vector<sf::FloatRect> m_wallPos;
	std::vector<sf::FloatRect> m_floorPos;
	std::vector<sf::Sprite> m_sprites;
	
};
