#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include<string>
#include "TicTacToe.h"

using namespace testing;

class MockTicTacToeListener :public ITicTacToeListener
{
public:
	MOCK_METHOD(void, OnGameOver, (std::string), (override));
	MOCK_METHOD(void, OnMakeMove, (int , int), (override));
	MOCK_METHOD(void, OnTie, (bool), (override));
};

TEST(TicTacToeTest, IsValidePosition) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);

	TicTacToe game;
	MockTicTacToeListener listener;
	game.AddTicTacToeListener(&listener);

	EXPECT_CALL(listener, OnMakeMove(1,1));
	EXPECT_CALL(listener, OnMakeMove(2,2));

	game.NextMove(std::make_pair(1, 1));
	game.NextMove(std::make_pair(2, 2));
	game.NextMove(std::make_pair(4, 4));

	Mock::VerifyAndClearExpectations(&listener);
	game.RemoveTicTacToeListener(&listener);
}

TEST(TicTacToeTest, IsWin)
{
	TicTacToe game;
	MockTicTacToeListener listener;
	game.AddTicTacToeListener(&listener);

	EXPECT_CALL(listener, OnMakeMove(0, 0));
	EXPECT_CALL(listener, OnMakeMove(0, 1));
	EXPECT_CALL(listener, OnMakeMove(1, 1));
	EXPECT_CALL(listener, OnMakeMove(1, 2));
	EXPECT_CALL(listener, OnMakeMove(2, 2));
	EXPECT_CALL(listener, OnGameOver("A"));

	game.SetPlayersName("A", "B");
	game.NextMove(std::make_pair(0, 0));
	game.NextMove(std::make_pair(0, 1));
	game.NextMove(std::make_pair(1, 1));
	game.NextMove(std::make_pair(1, 2));
	game.NextMove(std::make_pair(2, 2));
	

	Mock::VerifyAndClearExpectations(&listener);
	game.RemoveTicTacToeListener(&listener);
}

TEST(TicTacToeTest, IsTie)
{
	TicTacToe game;
	MockTicTacToeListener listener;
	game.AddTicTacToeListener(&listener);

	EXPECT_CALL(listener, OnMakeMove(0, 0));
	EXPECT_CALL(listener, OnMakeMove(0, 1));
	EXPECT_CALL(listener, OnMakeMove(0, 2));
	EXPECT_CALL(listener, OnMakeMove(1, 0));
	EXPECT_CALL(listener, OnMakeMove(1, 2));
	EXPECT_CALL(listener, OnMakeMove(2, 0));
	EXPECT_CALL(listener, OnMakeMove(1, 1));
	EXPECT_CALL(listener, OnMakeMove(2, 2));
	EXPECT_CALL(listener, OnMakeMove(2, 1));
	EXPECT_CALL(listener, OnTie(true));

	game.NextMove(std::make_pair(0, 0));
	game.NextMove(std::make_pair(0, 1));
	game.NextMove(std::make_pair(0, 2));
	game.NextMove(std::make_pair(1, 0));
	game.NextMove(std::make_pair(1, 2));
	game.NextMove(std::make_pair(2, 0));
	game.NextMove(std::make_pair(1, 1));
	game.NextMove(std::make_pair(2, 2));
	game.NextMove(std::make_pair(2, 1));


	Mock::VerifyAndClearExpectations(&listener);
	game.RemoveTicTacToeListener(&listener);
}
