#pragma once
#include<iostream>

class TicTacToe
{
private:
	const int boardSize = 3;
	char m_board[3][3];
	int m_turnNumber;
	std::string m_player1;
	std::string m_player2;

public:
	bool checkWin();
	void nextMove(std::pair<int, int> position);
	bool positionEmpty(std::pair<int, int>position);
};

