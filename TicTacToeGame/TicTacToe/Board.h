#pragma once

#include<array>

class Board
{
public:
	Board() = default;
	~Board() = default;

	int GetSize() const;
	void SetValue(char value, int i, int j);
	char GetValue(int i, int j) const;

private:
	const static int BOARD_SIZE = 3;
	std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> m_board;
};

