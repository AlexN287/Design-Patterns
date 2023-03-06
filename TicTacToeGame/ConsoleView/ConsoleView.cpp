#include "ConsoleView.h"

#include<iostream>
#include<array>

std::pair<int, int> ConsoleView::GetInputPositions()
{
	int row, column;
	std::cout << "Insert row:";
	std::cin >> row;
	std::cout << "Insert column:";
	std::cin >> column;
	return std::make_pair(row,column);
}

void ConsoleView::DisplayBoard()
{
	std::array<std::array<char, 3>, 3> board = game->GetBoard();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == 'X' || board[i][j] == 'O')
				std::cout << board[i][j] << ' ';
			else
				std::cout << '-' << ' ';
		}

		std::cout << std::endl;
	}

}

void ConsoleView::Run()
{
	DisplayBoard();

	while (game->CheckWin() == false)
	{
		std::pair<int,int >positions = GetInputPositions();
		game->NextMove(positions);
		DisplayBoard();
	}

	//DisplayBoard();
}
