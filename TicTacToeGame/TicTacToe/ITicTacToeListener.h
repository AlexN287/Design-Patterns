#pragma once

#include<string>
#include<utility>

class ITicTacToeListener
{
public:
	virtual void OnGameOver(std::string playerName) = 0;
	//virtual void OnMakeMove(std::pair<int, int> positions) = 0;
};