#pragma once

#include<string>

class ITicTacToeListener
{
public:
	virtual void OnGameOver(std::string playerName) = 0;
};