#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class MapLoader
{
public:
	MapLoader();
	void Init();
	void Draw(sf::RenderWindow* window);
	std::vector<sf::Sprite> getSprites() { return m_sprites; }
	std::vector<sf::Sprite> getWallSprites() { return m_wallSprites; }
	std::vector<sf::Vector2f> getSpawnPoints() { return m_spawnPoints; }
	std::vector<sf::Vector2f>* getNodes() { return &m_nodes; }

private:
	 std::vector<int> m_row0 = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	 std::vector<int> m_row1 = { 1,0,0,0,0,0,0,0,0,2,2,1,0,0,1 };
	 std::vector<int> m_row2 = { 1,0,0,0,0,0,0,0,0,0,0,1,0,0,1 };
	 std::vector<int> m_row3 = { 1,0,0,1,1,1,1,1,1,1,1,1,0,0,1 };
	 std::vector<int> m_row4 = { 1,0,0,1,0,0,0,0,0,0,0,0,0,2,1 };
	 std::vector<int> m_row5 = { 1,0,0,1,0,0,0,0,0,0,0,0,0,2,1 };
	 std::vector<int> m_row6 = { 1,0,0,1,0,0,0,0,1,0,0,1,0,0,1 };
	 std::vector<int> m_row7 = { 1,0,0,1,0,0,2,0,1,0,0,1,0,0,1 };
	 std::vector<int> m_row8 = { 1,0,0,1,0,0,0,0,1,0,1,1,0,0,1 };
	 std::vector<int> m_row9 = { 1,0,0,0,0,0,0,0,1,0,0,0,0,0,1 };
	std::vector<int> m_row10 = { 1,0,0,0,0,0,0,0,1,0,0,0,0,0,1 };
	std::vector<int> m_row11 = { 1,0,0,1,1,1,1,1,1,0,0,0,1,1,1 };
	std::vector<int> m_row12 = { 1,2,0,0,0,0,0,0,0,0,0,0,0,0,1 };
	std::vector<int> m_row13 = { 1,0,0,0,0,0,0,0,0,2,0,0,0,0,1 };
	std::vector<int> m_row14 = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

	std::vector<std::vector<int>> m_rows;
	sf::Sprite m_wallSprite;
	sf::Sprite m_tempSprite;
	sf::Texture m_wallTexture;

	sf::Sprite m_roofSprite;
	sf::Texture m_roofTexture;

	sf::Sprite m_floorSprite;
	sf::Texture m_floorTexture;
	sf::Vector2f tempVec;
	std::vector<sf::FloatRect> m_wallPos;
	std::vector<sf::FloatRect> m_floorPos;
	std::vector<sf::Sprite> m_sprites;
	std::vector<sf::Sprite> m_wallSprites;
	std::vector<sf::Sprite> m_floorSprites;
	std::vector<sf::Vector2f> m_nodes;
	std::vector<sf::Vector2f> m_spawnPoints;
};
