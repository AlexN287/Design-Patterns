#include "TicTacToe.h"

bool TicTacToe::checkWin()
{
	for (int i = 0; i < TicTacToe::boardSize; i++)
	{
		if (m_board[i][0] == m_board[i][1] && m_board[i][1] == m_board[i][2])
			return true;
	}

	for (int j = 0; j < TicTacToe::boardSize; j++)
	{
		if (m_board[0][j] == m_board[1][j] && m_board[1][j] == m_board[2][j])
			return true;
	}

	if (m_board[0][0] == m_board[1][1] && m_board[1][1] == m_board[2][2])
		return true;

	if (m_board[0][2] == m_board[1][1] && m_board[1][1] == m_board[2][0])
		return true;

	return false;
}

void TicTacToe::nextMove(std::pair<int, int> position)
{
	int poz1 = position.first;
	int poz2 = position.second;
	if (m_turnNumber % 2 == 1)
		m_board[poz1][poz2] = 'X';
	else
	{
		m_board[poz1][poz2] = 'O';
	}
}

bool TicTacToe::positionEmpty(std::pair<int, int> position)
{
	int poz1 = position.first;
	int poz2 = position.second;
	if (m_board[poz1][poz2] == 'X' || m_board[poz1][poz2] == 'O')
	{
		return false;
	}
	return true;
}
