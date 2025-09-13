#include <iostream>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>

/*
 * This file contains the board class that we are using to keep
 * track of game states.
 *
 * There are 64 squares on a chess board with 13 separate options.
 * For every square we would need to use 2 ^ n bits where 2 ^ n >= 13
 * The lowest value of n that matches this is 4. This means we would
 * need 4 * 64 bits to store a board state.
 *
*/

class Board{
	public:
		unsigned short int operator[](int);
	private:
		unsigned long long int board_top;
		unsigned long long int board_mid_top;
		unsigned long long int board_mid_low;
		unsigned long long int board_low;
		
};

class SubBoard {
	public:
		unsigned short int operator[](int);
		void updateBoard(int, int); // Change value of index to a specific value
		void setBoard(unsigned long long int); // Update SubBoard with full value
		unsigned long long int getBoard(); // Pull value
		SubBoard(); // Constructor function
	private:
		unsigned long long int status;
};


/*
 * Sub Board functions
*/
unsigned short int SubBoard::operator[](int x) {
	if (x == 0) {
		return status % 13;
	} else {
		return static_cast<unsigned long long int>(status / static_cast<unsigned long long int>(pow(13, x))) % 13;
	};
};

void SubBoard::updateBoard(int index, int value) {
	// Change value of board at index to value

	// Pull value at the index
	int value_at_index = (status / int(pow(13, index)));
	// If the space isn't blank, remove the current value
	if (value_at_index != 0) {
		status -= pow(13, index) * value_at_index;
	}
	// Add the value into the status to update
	status += (int(pow(13, index)) * value);
	return;
};

SubBoard::SubBoard() {
	// Empty Constructor
	status = 0;
};

void SubBoard::setBoard(unsigned long long int x) {
	// Set board to one number
	status = x;
	return;
};

unsigned long long int SubBoard::getBoard(){
	return status;
};
