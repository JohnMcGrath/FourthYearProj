#pragma once
#include <fstream>
#include <chrono>
#include "Player.h"

class FileWriter
{
public:
	void writeResults();
	void incrimentShotsTaken() { m_shotsTaken++; };
	void incrimentShotsHit() { m_shotsHit++; };
	void incrimentdistanceTravelled() { m_distanceTravelled++; }
	void incrimentTimesOfDeath() { m_timesDied++; }
	void startRecording();
	void setcontrolModeCombo(std::string cmc) { m_controlModeCombo = cmc; }
	void setMode(std::string m) { m_mode = m; }
	void beginTimer() { m_timeStart = m_clock.getElapsedTime().asSeconds(); };
	void endTimer() { m_timeEnd = m_clock.getElapsedTime().asSeconds(); }
	void setEndHealth(int i) { m_endHealth = i; }
	void update(float playVel);
private:
	const char * m_path = "ASSETS\\TEXTFILES";
	std::ofstream m_file;
	int m_shotsTaken = 0;
	int m_shotsHit = 0;
	int m_distanceTravelled = 0;
	int m_timeTaken = 0;
	int m_timeStart = m_clock.getElapsedTime().asSeconds();
	int m_timeEnd = m_clock.getElapsedTime().asSeconds();
	int m_timesDied = 0;
	int m_endHealth = 0;
	sf::Clock m_clock;
	std::string m_controlModeCombo = "Keyboard; ";
	std::string m_mode = "Arcade";
};
