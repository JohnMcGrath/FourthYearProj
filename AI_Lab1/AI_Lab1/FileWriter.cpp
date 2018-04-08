#include "FileWriter.h"

void FileWriter::writeResults()
{
	m_timeEnd = m_clock.getElapsedTime().asSeconds();
	m_file.open("results.txt", std::ofstream::out | std::ofstream::app);

	std::cout << "Time Start: " << m_timeStart << std::endl;
	std::cout << "Time End: " << m_timeEnd << std::endl;

	m_file << m_controlModeCombo;
	m_file << m_mode;
	m_file << "\n";

	int tempTime = m_timeEnd - m_timeStart;
	m_file << "Time Taken: ";
	m_file << tempTime;
	m_file << " seconds.\n";

	m_file << "Total Shots Hit: ";
	m_file << m_shotsHit;
	m_file << ".\n";

	m_file << "Total Shots Fired: ";
	m_file << m_shotsTaken;
	m_file << ".\n";

	m_file << "Times Died: ";
	m_file << m_timesDied;
	m_file << ".\n";

	m_file << "Remaining Health: ";
	m_file << m_endHealth;
	m_file << ".\n";

	m_file << "Total Distance Traveled: ";
	m_file << m_distanceTravelled;
	m_file << ".\n\n";

	m_file.close();
}

void FileWriter::startRecording()
{
	m_shotsTaken = 0;
	m_shotsHit = 0;
	m_distanceTravelled = 0;
	m_timeTaken = 0;
	m_timesDied = 0;
	m_timeStart = m_clock.getElapsedTime().asSeconds();
	m_timeEnd = m_clock.getElapsedTime().asSeconds();
}

void FileWriter::update(float playVel)
{
	if (playVel != 0)
	{
		incrimentdistanceTravelled();
	}
}