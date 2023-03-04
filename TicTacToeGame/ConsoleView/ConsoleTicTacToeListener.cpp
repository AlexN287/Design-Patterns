#include "ConsoleTicTacToeListener.h"

#include<iostream>

void ConsoleTicTacToeListener::OnGameOver(std::string playerName)
{
	std::cout << "Congratulations, " << playerName << "you won !";
}
