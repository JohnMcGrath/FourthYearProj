#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
	init();
}

void SoundManager::init()
{
	//Loads the player gunshot sound
	if (!m_playerGunShot.loadFromFile("ASSETS\\SOUNDS\\ar1.wav"))
	{
		std::cout << "Error Loading Player Gunshot Sound AR1" << std::endl;
	}
	//m_playerGunShot.setBuffer(m_buffer);
	m_sounds.insert(std::make_pair("playerGun", &m_playerGunShot));
	m_soundPlayers.insert(std::make_pair("playerGun", &m_playerGruntSound));

	//Loads the enemy gunshot
	if (!m_enemyGunShot.loadFromFile("ASSETS\\SOUNDS\\pistol1.wav"))
	{
		std::cout << "Error Loading Enemy Gunshot Pistol1" << std::endl;
	}
	//m_enemyGunShot.setBuffer(m_buffer);
	m_sounds.insert(std::make_pair("enemyGun1", &m_enemyGunShot));
	m_soundPlayers.insert(std::make_pair("enemyGun1", &m_enemyGunShotSound));

	////Loads the player grunt sound
	if (!m_playerGrunt.loadFromFile("ASSETS\\SOUNDS\\playerGrunt.wav"))
	{
		std::cout << "Error Loading Enemy Gunshot Pistol1" << std::endl;
	}
	m_sounds.insert(std::make_pair("playerGrunt", &m_playerGrunt));
	m_soundPlayers.insert(std::make_pair("playerGrunt", &m_playerGruntSound));

	////Loads the player grunt sound
	if (!m_enemyGrunt.loadFromFile("ASSETS\\SOUNDS\\enemyGrunt.wav"))
	{
		std::cout << "Error Loading Enemy Gunshot Pistol1" << std::endl;
	}
	m_sounds.insert(std::make_pair("enemyGrunt", &m_enemyGrunt));
	m_soundPlayers.insert(std::make_pair("enemyGrunt", &m_enemyGruntSound));

	////Loads the enemy death sound
	if (!m_enemyDeath.loadFromFile("ASSETS\\SOUNDS\\enemyDeath.wav"))
	{
		std::cout << "Error Loading Enemy Death sound" << std::endl;
	}
	m_sounds.insert(std::make_pair("enemyDeath", &m_enemyDeath));
	m_soundPlayers.insert(std::make_pair("enemyDeath", &m_enemyDeathSound));

	if (!m_backgroundSong.openFromFile("ASSETS\\SOUNDS\\backgroundMusic.wav"))
	{
		std::cout << "Error Streaming Background Music" << std::endl;
	}
	m_backgroundSong.setLoop(true);
	m_backgroundSong.play();
}

void SoundManager::playSound(std::string sound)
{
	m_soundPlayers[sound]->setBuffer(*m_sounds[sound]);
	m_soundPlayers[sound]->play();
}

void SoundManager::update()
{
	for (int i = 0; i < m_queue.size(); i++)
	{
		m_queue.at(i).play();
		m_queue.erase(m_queue.begin() + i);
	}
}