#include "FileWriter.h"

void FileWriter::writeResults()
{
	m_timeEnd = m_clock.getElapsedTime().asSeconds();
	m_file.open("results.txt");

	int tempTime = m_timeEnd - m_timeStart;
	m_file << "Time Taken: ";
	m_file << tempTime;
	m_file << " seconds.\n";

	m_file << "Total Shots Hit: ";
	m_file << m_shotsHit;
	m_file << "\n";

	m_file << "Total Shots Fired: ";
	m_file << m_shotsTaken;
	m_file << "\n";
}

void FileWriter::startRecording()
{

}