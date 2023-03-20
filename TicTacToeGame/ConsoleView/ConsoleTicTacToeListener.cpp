#include "ConsoleTicTacToeListener.h"

#include<iostream>

void ConsoleTicTacToeListener::OnGameOver(std::string playerName)
{
	std::cout << "Player " << playerName << " won. Congratulations ! \n";
}

void ConsoleTicTacToeListener::OnMakeMove(int i, int j)
{
	//std::cout << "Position Valide \n";;
}

void ConsoleTicTacToeListener::OnTie(bool isTie)
{
	if (isTie)
	{
		std::cout << "The match resulted with a tie. \n";
	}
}

