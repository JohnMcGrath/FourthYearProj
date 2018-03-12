#pragma once
#include <SFML/Audio.hpp>
#include <map>

class SoundManager
{
public:
	SoundManager();
	void init();
	void playSound(std::string soundName);
	void update();
	
private:
	sf::Sound m_soundPlayer;
	sf::Music m_backgroundSong;

	sf::Sound m_playerGunShotSound;
	sf::Sound m_enemyGunShotSound;
	sf::Sound m_playerGruntSound;
	sf::Sound m_enemyGruntSound;
	sf::Sound m_enemyDeathSound;

	sf::SoundBuffer m_playerGunShot;
	sf::SoundBuffer m_enemyGunShot;
	sf::SoundBuffer m_playerGrunt;
	sf::SoundBuffer m_enemyGrunt;
	sf::SoundBuffer m_enemyDeath;

	std::map<std::string, sf::SoundBuffer*> m_sounds;
	std::map<std::string, sf::Sound*> m_soundPlayers;
	std::vector<sf::Sound> m_queue;
};
