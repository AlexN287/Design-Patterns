#include <iostream>

#include "ConsoleView.h"
#include "ConsoleTicTacToeListener.h"

int main()
{
	ITicTacToePtr game = ITicTacToe::Produce(EgameType::Implem1);

	ConsoleView consoleGame(game); 
	ConsoleTicTacToeListener listener;
	game->AddTicTacToeListener(&listener);

	consoleGame.DisplayGameOptions();
	int gameOptions;
	bool isOk = false;

	while (!isOk)
	{
		std::cin >> gameOptions;
		switch (gameOptions)
		{
		default:
			break;
		}
	}

	consoleGame.Run();
	return 0;
} 