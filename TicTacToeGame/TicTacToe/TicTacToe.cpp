#include "TicTacToe.h"

#include<iostream>

void TicTacToe::AddTicTacToeListener(ITicTacToeListener* listener)
{
	listeners.push_back(listener);
}

void TicTacToe::RemoveTicTacToeListener(ITicTacToeListener* listener)
{
	for (auto it = listeners.begin(); it != listeners.end(); ++it)
	{
		if (*it == listener)
		{
			listeners.erase(it);
			break;
		}
	}
}

std::array<std::array<char, 3>, 3> TicTacToe::GetBoard() const
{
	return m_board;
}

bool TicTacToe::CheckWin()const
{
	for (int i = 0; i < TicTacToe::BOARD_SIZE; i++)
	{
		if (m_board[i][0] != NULL && m_board[i][0] == m_board[i][1] && m_board[i][1] == m_board[i][2])
			return true;
	}

	for (int j = 0; j < TicTacToe::BOARD_SIZE; j++)
	{
		if (m_board[0][j] != NULL && m_board[0][j] == m_board[1][j] && m_board[1][j] == m_board[2][j])
			return true;
	}

	if (m_board[0][0] != NULL && m_board[0][0] == m_board[1][1] && m_board[1][1] == m_board[2][2])
		return true;

	if (m_board[0][2] != NULL && m_board[0][2] == m_board[1][1] && m_board[1][1] == m_board[2][0])
		return true;

	return false;
}

void TicTacToe::NextMove(std::pair<int, int> position)
{
	int poz1 = position.first;
	int poz2 = position.second;

	if (poz1 > 2 || poz1 < 0 || poz2 < 0 || poz2>2)
	{
		std::cout << "Position invalid. \n";
	}
	else if (PositionEmpty(position))
	{
		if (m_turnNumber % 2 == 1)
			m_board[poz1][poz2] = 'X';
		else
		{
			m_board[poz1][poz2] = 'O';
		}
		m_turnNumber++;
	}
	else
	{
		std::cout << "Position occupied. \n";
	}
}

bool TicTacToe::PositionEmpty(std::pair<int, int> position)const
{
	int poz1 = position.first;
	int poz2 = position.second;

	if (m_board[poz1][poz2] == 'X' || m_board[poz1][poz2] == 'O')
	{
		return false;
	}

	return true;
}
