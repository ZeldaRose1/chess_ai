#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>

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
	char get_index(int, int); // Row index, column index
	void set_value(int, int, char); // Row index, column index, piece character
	void print_board(); // Print board to screen

    private:
	// Segments of the board by algebraic notation
	unsigned long long int ab;
	unsigned long long int cd;
	unsigned long long int ef;
	unsigned long long int gh;

	// Pointer to help us choose the correct sub-board
	unsigned long long int* utility_pointer;

	// Functions to convert values to character representations
	char i_to_p(int);  // Convert integer value of a piece to it's char representation
	int p_to_i(char); // Convert character value of piece to it's int representation
};



