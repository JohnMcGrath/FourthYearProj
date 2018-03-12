#pragma once
#include <SFML/Audio.hpp>
#include <map>

class SoundManager
{
public:
	SoundManager();
	void init();
	void playSound(std::string soundName);
	
private:
	sf::SoundBuffer m_buffer;
	sf::Music m_backgroundSong;
	sf::Sound m_playerGunShot;
	sf::Sound m_enemyGunShot;
	sf::Sound m_playerGrunt;
	sf::Sound m_enemyGrunt;

	std::map<std::string, sf::Sound> m_sounds;
};
