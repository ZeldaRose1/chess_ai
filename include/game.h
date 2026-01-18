/*
Header for game class. This class will contain the attributes and functions needed to
generate moves and define the chess game logic.
*/

#pragma once

#include <vector>
#include "board.h"

class Game{
    public:
	Game(); // Constructor
	// Game(Board); // Constructor with an argument;
	Board get_board(); // Getter to access board
	void set_board(Board); // Setter to modify the board state
	void generate_moves(); // Fill next level of available_moves
	bool get_white_turn();
	void set_white_turn(bool);
    private:
	bool white_turn; // true for white's move, false for black's move
	Board b; // Board status at current turn.
	vector<Board> available_moves;
};
