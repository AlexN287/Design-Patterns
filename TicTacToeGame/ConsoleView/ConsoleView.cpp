#include "ConsoleView.h"

#include<iostream>
#include<array>
//#include"IStrategy.h"

ConsoleView::ConsoleView(ITicTacToePtr game) :
	m_game(game)
{
}

Positions ConsoleView::GetInputPositions()
{
	int row, column;
	std::cout << "Insert row:";
	std::cin >> row;
	std::cout << "Insert column:";
	std::cin >> column;
	return std::make_pair(row - 1, column - 1);
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
	DisplayGameOptions();
	int gameOptions;
	bool isOk = false;

	while (!isOk)
	{
		std::cin >> gameOptions;
		if (gameOptions == 1 || gameOptions == 2)
		{
			isOk = true;
		}
	}

	if (gameOptions == 2) {
		std::string namePlayer_1, namePlayer_2;
		GetPlayersName(namePlayer_1, namePlayer_2);
		m_game->SetPlayersName(namePlayer_1, namePlayer_2);

		Positions positions;
		do {
			DisplayBoard();
			std::cout << m_game->GetCurrentPlayer() << "'s turn \n";
			positions = GetInputPositions();
		} while (m_game->NextMove(positions));
		DisplayBoard();
	}
	else 
	{
		DisplayGameDifficulties();
		int gameDifficulties;
		bool itsOk = false;
		IStrategyPtr difficulty;
		while (!itsOk)
		{
			std::cin >> gameDifficulties;
			switch (gameDifficulties)
			{
			case 1:
				difficulty = IStrategy::Produce(EDifficulty::Easy);
				itsOk = true;
				break;
			case 2:
				difficulty = IStrategy::Produce(EDifficulty::Medium);
				itsOk = true;
				break;
			case 3:
				difficulty = IStrategy::Produce(EDifficulty::Hard);
				itsOk = true;
				break;
			default:
				break;
			}
		}

		std::string namePlayer;
		bool nameInvalid = true;
		while (nameInvalid)
		{
			std::cout << "Enter player name: ";
			std::cin >> namePlayer;
			if (namePlayer != "CPU")
				nameInvalid = false;
		}
		m_game->SetPlayersName(namePlayer, "CPU");

		Positions positions;

		do{
			if (m_game->GetCurrentPlayer()!="CPU") 
			{
				DisplayBoard();
				std::cout << m_game->GetCurrentPlayer() << "'s turn \n";
				positions = GetInputPositions();
			}
			else
			{
				DisplayBoard();
				std::cout << m_game->GetCurrentPlayer() << "'s turn \n";
				Board board = GetBoard();
				positions = difficulty->GetNextMove(board);
			}
		} while (m_game->NextMove(positions));

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

Board ConsoleView::GetBoard()
{
	Board new_board;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			new_board.SetValue(m_game->GetValue(i, j), i, j);
		}
	}
	return new_board;
}

void ConsoleView::DisplayGameOptions()
{
	std::cout << "1 - VS Computer \n";
	std::cout << "2 - VS Player \n";
}

void ConsoleView::DisplayGameDifficulties()
{
	std::cout << "1 - Easy \n";
	std::cout << "2 - Medium \n";
	std::cout << "3 - Hard \n";
}

