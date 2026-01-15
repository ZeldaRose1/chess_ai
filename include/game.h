/*
Header for game class. This class will contain the attributes and functions needed to
generate moves and define the chess game logic.
*/

#pragma once

#include "board.h"

class Game{
    public:
	Game(); // Constructor
	Board get_board(); // Getter to access board
	void set_board(Board); // Setter to modify the board state
    private:
	bool white_turn; // true for white's move, false for black's move
	Board b; // Board status at current turn.
    
    class MoveGen {

    };
};
