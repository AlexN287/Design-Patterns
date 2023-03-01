#pragma once
#include "ITicTacToe.h"
#include <string>

class TicTacToe:public ITicTacToe
{
public:
	bool CheckWin()const override;
	void NextMove(std::pair<int, int> position) override;
	bool PositionEmpty(std::pair<int, int>position)const override;

private:
	const int boardSize = 3;
	char m_board[3][3];
	int m_turnNumber;
	std::string m_player1;
	std::string m_player2;
};

