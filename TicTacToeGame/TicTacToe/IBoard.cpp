#include "IBoard.h"
#include "Board.h"

IBoardPtr IBoard::Produce()
{
	return std::make_shared<Board>();
}
