#pragma once
#include <vector>

class MapLoader
{
public:
	MapLoader();

private:
	std::vector<int> m_row0 = { 1,1,1,1,1,1,1,1,1,1 };
	std::vector<int> m_row1 = { 1,0,0,0,0,0,0,0,0,1 };
	std::vector<int> m_row2 = { 1,0,0,0,0,0,0,0,0,1 };
	std::vector<int> m_row3 = { 1,0,0,0,0,0,0,0,0,1 };
	std::vector<int> m_row4 = { 1,0,0,0,0,0,0,0,0,1 };
	std::vector<int> m_row5 = { 1,0,0,0,0,0,0,0,0,1 };
	std::vector<int> m_row6 = { 1,0,0,0,0,0,0,0,0,1 };
	std::vector<int> m_row7 = { 1,0,0,0,0,0,0,0,0,1 };
	std::vector<int> m_row8 = { 1,0,0,0,0,0,0,0,0,1 };
	std::vector<int> m_row9 = { 1,1,1,1,1,1,1,1,1,1 };

	std::vector<std::vector<int>> m_rows;
};
