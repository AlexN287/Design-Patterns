#pragma once
#include<iostream>

class TicTacToe
{
private:
	char board[3][3];
	int turnNumber;
	std::string player1;
	std::string player2;

public:
	bool checkWin();
	void nextMove(std::pair<int, int> position);
};

