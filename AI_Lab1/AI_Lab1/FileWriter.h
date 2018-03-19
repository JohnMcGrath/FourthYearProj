#pragma once
#include <fstream>
#include <chrono>
#include "Player.h"

class FileWriter
{
public:
	/*FileWriter()
	{ 

		m_file.open("tempTestFile.txt");
		m_file << "This is a test";
	}*/
	void writeResults();
	void incrimentShotsTaken() { m_shotsTaken++; };
	void incrimentShotsHit() { m_shotsHit++; };
	void incrimentdistanceTravelled();
	void startRecording();
	void setcontrolModeCombo(std::string cmc) { m_controlModeCombo = cmc; }
	void beginTimer() { m_timeStart = m_clock.getElapsedTime().asSeconds(); };
	void endTimer() { m_timeEnd = m_clock.getElapsedTime().asSeconds(); }
private:
	const char * m_path = "ASSETS\\TEXTFILES";
	std::ofstream m_file;
	int m_shotsTaken = 0;
	int m_shotsHit = 0;
	int m_distanceTravelled = 0;
	int m_timeTaken = 0;
	int m_timeStart = m_clock.getElapsedTime().asSeconds();
	int m_timeEnd = m_clock.getElapsedTime().asSeconds();
	sf::Clock m_clock;
	std::string m_controlModeCombo;
};
