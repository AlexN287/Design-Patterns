#pragma once

#include"IBoard.h"

#include<array>

class Board :public IBoard
{
public:
	Board() = default;
	~Board() = default;

	int GetSize() const override;
	void SetValue(char value, int i, int j) override;
	char GetValue(int i,int j) const override;

private:
	const static int BOARD_SIZE = 3;
	std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> m_board;
};

