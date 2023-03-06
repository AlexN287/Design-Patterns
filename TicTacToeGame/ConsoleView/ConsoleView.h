#pragma once

#include "ITicTacToe.h"

#include<utility>

class ConsoleView
{
public:
	ConsoleView() = default;
	~ConsoleView() = default;

	std::pair<int, int> GetInputPositions();
	void DisplayBoard();
	void Run();

private:
	ITicTacToePtr game = ITicTacToe::Produce(EgameType::Implem1);
};

