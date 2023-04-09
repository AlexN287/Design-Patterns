#pragma once

#include "ITicTacToeListener.h"

#include <utility>
#include <memory>

using ITicTacToePtr = std::shared_ptr<class ITicTacToe>; /*<! Is a declaration of a type for a shared_ptr to the 
ITicTacToe class*/

/*!The enum class containing the game type that you want to produce */
enum class EgameType 
{
	Implem1,
	Implem2
};


/*! The ITicTacToe interface class is a tool that can be used to create a Tic Tac Toe game. This class defines
the basic methods and properties required for a Tic Tac Toe game, which can be implemented by a programmer 
to create a fully functional game. */

class ITicTacToe
{
public:
	static ITicTacToePtr Produce(EgameType type); /*!<This function is a factory method that creates an 
	instance of the ITicTacToe interface based on the specified game type. The function takes a single parameter
	of type EgameType which represents the type of game to be produced. */

	virtual char GetValue(int i, int j) const = 0; /*!< The GetValue function takes as parameters the positions 
	of the value that you want to get and return it*/

	virtual void AddTicTacToeListener(ITicTacToeListener* listener) = 0; /*!<Add a new listener.  This listener
	object is responsible for handling events. The function takes a single parameter of type ITicTacToeListener*
	which is a pointer to an object that implements the ITicTacToeListener interface.*/

	virtual void RemoveTicTacToeListener(ITicTacToeListener* listener) = 0; /*!<Remove a listener. The function 
	takes a single parameter of type ITicTacToeListener* which is a pointer to an object that implements the 
	ITicTacToeListener interface.*/

	virtual bool CheckWin() const = 0; /*!< This function check if a player won the game and return true in this case, otherwise return false*/

	virtual bool NextMove(std::pair<int, int> position) = 0; /*!< This function is responsible for handling the
	next move of a player and updating the state of the game board accordingly. The function takes in a pair of 
	integers representing the position on the game board where the player wants to place their mark. The
	function return true if any moves can be done, otherwise return false*/

	virtual bool PositionEmpty(std::pair<int, int>position) const = 0; /*!<The function takes in a pair of 
	integers representing the position on the game board that needs to be checked. The function returns a 
	boolean value indicating whether the specified position is empty or not. If the position is empty,
	the function returns true. If the position is already occupied, the function returns false.*/

	virtual bool IsTie() const = 0; /*!<The function return true if the match finished with a draw, otherwise
	return false*/

	virtual std::string GetCurrentPlayer() const = 0; /*!<The function does not take any parameters and returns
	a string representing the name of the player who is currently taking their turn.*/

	virtual void SetPlayersName(const std::string& namePlayer_1, const std::string& namePlayer_2) = 0;/*!<This function
	set the names of the palyer 1 and player 2*/

	virtual std::vector<std::pair<int, int>> GetEmptyCells() const = 0;

	virtual ~ITicTacToe() = default; /*!<The virtual destructor*/
};
