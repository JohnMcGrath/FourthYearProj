#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
	init();
}

void SoundManager::init()
{
	if (!m_buffer.loadFromFile("ASSETS\\SOUNDS\\backgroundMusic.mp3"))
	{
		std::cout << "Error Loading Background Music" << std::endl;
	}

	if (!m_backgroundSong.openFromFile("ASSETS\\SOUNDS\\backgroundMusic.wav"))
	{
		std::cout << "Error Streaming Background Music" << std::endl;
	}
	m_backgroundSong.setLoop(true);
	m_backgroundSong.play();
}

void SoundManager::playSound(std::string sound)
{

}