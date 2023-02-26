#include "TicTacToe.h"

void TicTacToe::nextMove(std::pair<int, int> position)
{
	int poz1 = position.first;
	int poz2 = position.second;
	if (turnNumber % 2 == 1)
		board[poz1][poz2] = 'X';
	else
	{
		board[poz1][poz2] = 'O';
	}
}

bool TicTacToe::positionEmpty(std::pair<int, int> position)
{
	int poz1 = position.first;
	int poz2 = position.second;
	if (board[poz1][poz2] == 'X' || board[poz1][poz2] == 'O')
	{
		return false;
	}
	return true;
}
