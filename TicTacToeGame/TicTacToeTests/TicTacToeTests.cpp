#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include<string>
#include "TicTacToe.h"

class MockTicTacToeListener :public ITicTacToeListener
{
public:
	MOCK_METHOD(void, OnGameOver, (std::string), (override));
};

TEST(TicTacToeTest, IsGameOver) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);

	TicTacToe game;
	MockTicTacToeListener listener;
	game.AddTicTacToeListener(&listener);
}