#include "ConsoleView.h"

#include<iostream>
#include<array>

ConsoleView::ConsoleView(ITicTacToePtr game) :
	m_game(game)
{
}

std::pair<int, int> ConsoleView::GetInputPositions()
{
	int row, column;
	std::cout << "Insert row:";
	std::cin >> row;
	std::cout << "Insert column:";
	std::cin >> column;
	return std::make_pair(row - 1,column - 1);
}

void ConsoleView::DisplayBoard()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (m_game->GetValue(i,j) == 'X' || m_game->GetValue(i,j) == 'O')
				std::cout << m_game->GetValue(i,j) << ' ';
			else
				std::cout << '-' << ' ';
		}

		std::cout << std::endl;
	}
}

void ConsoleView::Run()
{
	std::string namePlayer_1, namePlayer_2;
	GetPlayersName(namePlayer_1, namePlayer_2);
	m_game->SetPlayersName(namePlayer_1, namePlayer_2);

	DisplayBoard();

	while (m_game->CheckWin() == false && m_game->IsTie() == false)
	{
		std::cout << m_game->GetCurrentPlayer() << "'s turn \n";
		std::pair<int,int >positions = GetInputPositions();
		m_game->NextMove(positions);
		DisplayBoard();
	}

}

void ConsoleView::GetPlayersName(std::string& namePlayer_1, std::string& namePlayer_2)
{
	std::cout << "Enter player 1 name: ";
	std::cin >> namePlayer_1;
	std::cout << "Enter player 2 name: ";
	std::cin >> namePlayer_2;
	std::cout << "\n";
}
