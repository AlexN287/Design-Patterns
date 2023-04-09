#pragma once

#include<array>
#include<vector>
#include<utility>

class Board
{
public:
	Board() = default;
	~Board() = default;

	int GetSize() const;
	void SetValue(char value, int i, int j);
	char GetValue(int i, int j) const;
	std::vector<std::pair<int, int>> GetEmptyCells() const;

private:
	const static int BOARD_SIZE = 3;
	std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> m_board;
};

