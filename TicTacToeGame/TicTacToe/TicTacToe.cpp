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

std::string TicTacToe::GetCurrentPlayer() const
{
	if (m_turnNumber % 2 == 1)
		return m_player1;
	return m_player2;
}

void TicTacToe::SetPlayersName(const std::string& namePlayer_1, const std::string& namePlayer_2)
{
	m_player1 = namePlayer_1;
	m_player2 = namePlayer_2;
}

char TicTacToe::GetValue(int i, int j) const
{
	return m_board->GetValue(i,j);
}


bool TicTacToe::CheckWin()const
{
	for (int i = 0; i < m_board->GetSize(); i++)
	{
		if (m_board->GetValue(i,0) != NULL && m_board->GetValue(i, 0) == m_board->GetValue(i, 1) && m_board->GetValue(i, 1) == m_board->GetValue(i, 2))
			return true;
	}

	for (int j = 0; j < m_board->GetSize(); j++)
	{
		if (m_board->GetValue(0, j) != NULL && m_board->GetValue(0,j) == m_board->GetValue(1,j) && m_board->GetValue(1,j) == m_board->GetValue(2, j))
			return true;
	}

	if (m_board->GetValue(0,0) != NULL && m_board->GetValue(0, 0) == m_board->GetValue(1,1) && m_board->GetValue(1,1) == m_board->GetValue(2,2))
		return true;

	if (m_board->GetValue(0,2) != NULL && m_board->GetValue(0,2) == m_board->GetValue(1,1) && m_board->GetValue(1,1) == m_board->GetValue(2,0))
		return true;

	return false;
}

bool TicTacToe::NextMove(std::pair<int, int> position)
{
	int poz1 = position.first;
	int poz2 = position.second;

	std::string currentPlayer = GetCurrentPlayer();

	if (poz1 > 2 || poz1 < 0 || poz2 < 0 || poz2>2)
	{
		std::cout << "Position invalid. \n";
	}
	else if (PositionEmpty(position))
	{
		if (m_turnNumber % 2 == 1)
			m_board->SetValue('X', poz1, poz2);
		else
		{
			m_board->SetValue('O', poz1, poz2);
		}
		m_turnNumber++;

		for (ITicTacToeListener* listener : listeners)
		{
			listener->OnMakeMove(poz1, poz2);
		}
	}
	else
	{
		std::cout << "Position Invalide";
	}

	if (CheckWin())
	{
		for (ITicTacToeListener* listener : listeners)
		{
			listener->OnGameOver(currentPlayer);
		}

		return false;
	}

	if (IsTie())
	{
		for (ITicTacToeListener* listener : listeners)
		{
			listener->OnTie(true);
		}

		return false;
	}

	return true;
}

bool TicTacToe::PositionEmpty(std::pair<int, int> position)const
{
	int poz1 = position.first;
	int poz2 = position.second;

	if (m_board->GetValue(poz1, poz2) == 'X' || m_board->GetValue(poz1, poz2) == 'O')
	{

		return false;
	}

	return true;
}

bool TicTacToe::IsTie() const
{
	if (m_turnNumber > 9)
	{
		return true;
	}
	return false;
}
