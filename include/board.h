#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

/*
 * This file contains the board class that we are using to keep
 * track of game states.
 *
 * There are 64 squares on a chess board with 13 separate options.
 * For every square we would need to use 2 ^ n bits where 2 ^ n >= 13
 * The lowest value of n that matches this is 4. This means we would
 * need 4 * 64 bits to store a board state.
 *
 * The board will start with 0 as A1 in the lower left corner of the
 * board and continue with "algebraic" notation for the rest of the
 * board until 63 is H8.
 * 
 * There will be four smaller numbers that represent two rows. The
 * logic to index between them will be handled by the Board clss.
*/

class Board{
    public:
	Board(); // Constructor
	Board(const Board &); // Copy Constructor
	void print_board(); // Print board to screen

	char get_index(int, int); // Row index, column index
	void set_value(int, int, char); // Row index, column index, piece character

	bool get_white_turn();
	void set_white_turn(bool);

	void direct_set_board_section(int, unsigned long long int); // Only meant to be used for testing

	// Vector to store all potential moves
	vector<Board> next_moves;
	// Vector to store all moves preceding the current game state.
	vector<Board> board_history; // Effectively treated as a stack

    private:
	// Segments of the board by algebraic notation
	unsigned long long int ab;
	unsigned long long int cd;
	unsigned long long int ef;
	unsigned long long int gh;

	// Pointer to help us choose the correct sub-board
	unsigned long long int* utility_pointer;

	// Boolean value to track whom's turn it is
	bool white_turn;

	// Functions to convert values to character representations
	char i_to_p(int);  // Convert integer value of a piece to it's char representation
	int p_to_i(char); // Convert character value of piece to it's int representation
	
	// Declare friend class
	// friend class MoveGen;
};



