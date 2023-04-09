#pragma once

#include "ITicTacToe.h"

#include<utility>

class ConsoleView
{
public:
	ConsoleView(ITicTacToePtr game);
	~ConsoleView() = default;

	std::pair<int, int> GetInputPositions();
	void DisplayBoard();
	void Run();
	void GetPlayersName(std::string& namePlayer_1, std::string& namePlayer_2);
	void DisplayGameOptions();
	void DisplayGameDifficulties();

private:
	ITicTacToePtr m_game;
};

