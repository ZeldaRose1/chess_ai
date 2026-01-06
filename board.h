#include <iostream>
#include <stdexcept>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>

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
	// Get the values with either one or two indices.
//	unsigned short int operator[](int);
	char get_index(int, int);

	// Set value with an index and a value
	void set_value(int, int, char); // Row index, column index, piece character
	unsigned long long int ab;
	unsigned long long int cd;
	unsigned long long int ef;
	unsigned long long int gh;

    private:
	unsigned long long int* utility_pointer;
	char i_to_p(int);  // Convert integer value of a piece to it's char representation
	int p_to_i(char); // Convert character value of piece to it's int representation
};



/*
    Start Board functions
*/

Board::Board() {
    // Constructor for board.
    ab = 0;
    cd = 0;
    ef = 0;
    gh = 0;
};

int Board::p_to_i(char c) {
    /*
	Returns the integer value associated with a specific character
	The values are as follows:
	    n: Empty - 0

	    p: black pawn - 13
            r: black rook - 12
            b: black bishop - 11
            h: black knight (horse) - 10
            q: black queen - 09
            k: black king - 08

	    P: white pawn - 01
	    R: white rook - 02
	    B: white bishop - 03
	    H: white knight (horse)- 04
	    Q: white queen - 05
	    K: white king - 06
    */
    int ret_val = -1;

    switch(c) {
	case 'n':
	    ret_val =  0;
	    break;
	case 'p':
	    ret_val =  13;
	    break;
	case 'r':
	    ret_val =  12;
	    break;
	case 'b':
	    ret_val =  11;
	    break;
	case 'h':
	    ret_val =  10;
	    break;
	case 'q':
	    ret_val =  9;
	    break;
	case 'k':
	    ret_val =  8;
	    break;
	case 'P':
	    ret_val =  1;
	    break;
	case 'R':
	    ret_val =  2;
	    break;
	case 'B':
	    ret_val =  3;
	    break;
	case 'H':
	    ret_val =  4;
	    break;
	case 'Q':
	    ret_val =  5;
	    break;
	case 'K':
	    ret_val =  6;
	    break;
	default:
	    std::cout << "Error! " << c << " is not a valid argument for p_to_i" << std::endl;
	    break;
    }

    // if (ret_val == -1)
    //     std::cout << "Error! " << c << " is not a valid argument for p_to_i" << std::endl;
    return ret_val;

};


char Board::i_to_p(int i) {
    // Convert an integer back into a character value using the same notation as p_to_i
    char ret_char = 'z';
    switch(i) {
	case 0:
	    ret_char = 'n';
	    break;
	case 13:
	    ret_char = 'p';
	    break;
	case 12:
	    ret_char =  'r';
	    break;
	case 11:
	    ret_char =  'b';
	    break;
	case 10:
	    ret_char =  'h';
	    break;
	case 9:
	    ret_char =  'q';
	    break;
	case 8:
	    ret_char =  'k';
	    break;
	case 1:
	    ret_char =  'P';
	    break;
	case 2:
	    ret_char =  'R';
	    break;
	case 3:
	    ret_char =  'B';
	    break;
	case 4:
	    ret_char =  'H';
	    break;
	case 5:
	    ret_char =  'Q';
	    break;
	case 6:
	    ret_char =  'K';
	    break;
	default:
	    std::cout << "Error! " << i << " is not a valid argument for i_to_p" << std::endl;
	    break;
    }

    if (ret_char == 'z')
	std::cout << "Error! " << i << " is not a valid argument for i_to_p" << std::endl;

    return ret_char;

};


// Setter

void Board::set_value(int i, int j, char piece) {
    /*
	This function will check the value at a current square,
	remove the value if it exists,
	then fill the value with the appropriate number

	Params:
	    i: Index value of row to set
	    j: Index value of column to set
	    piece: value to fill the space with
	
	Returns:
	    None
    */

    // Make pointer to the correct part of the board
    switch(i) {
	case 1:
	    utility_pointer = &ab;
	    break;
	case 2:
	    utility_pointer = &ab;
	    break;
	case 3:
	    utility_pointer = &cd;
	    break;
	case 4:
	    utility_pointer = &cd;
	    break;
	case 5:
	    utility_pointer = &ef;
	    break;
	case 6:
	    utility_pointer = &ef;
	    break;
	case 7:
	    utility_pointer = &gh;
	    break;
	case 8:
	    utility_pointer = &gh;
	    break;
    }

    // Read value
    unsigned long long int read_value = (*utility_pointer) / ((unsigned long long int) pow(16, 8 * ((i - 1) % 2) + (j - 1))) % 16;

    // DEBUG STATEMENTS
    // std::cout << "Iteration:\t i = " << i << "\t j = " << j << std::endl;
    // std::cout << "Value read in first for set_value: " << read_value << std::endl;
    // std::cout << "Full sub_board value: " << *utility_pointer << std::endl;
    //std::cout << "Output of power command: " << ((unsigned long long int) pow(16, 8 * ((i - 1) % 2) + (j - 1))) << std::endl;

    
    // Delete value so we don't change other board states
    if (read_value != 0)
	*utility_pointer -= read_value * ((unsigned long long int) pow(16, 8 * ((i - 1) % 2) + (j - 1)));

    // Add new value to the board
    unsigned long long int set_increase = p_to_i(piece) * ((unsigned long long int) pow(16, ((i - 1) % 2) * 8 + j - 1));
    (*utility_pointer) += set_increase;
    // std::cout << "4 bit value of given square: " << p_to_i(piece) << std::endl;
    // std::cout << "Increasing sub-board value by " << set_increase << std::endl;
    // std::cout << "New value of board: " << (*utility_pointer) << std::endl;
    // std::cout << std::endl;

    // Prevent any chance of accidental setting
    utility_pointer = nullptr;

    return;

};

// Access function
char Board::get_index(int i, int j) {
    // Pulls value from row i, column j
    if (i < 1 || i > 8){
	std::cout << "Error: Index for i must be between 1 and 8. Value of i is " << i << std::endl;
	throw std::invalid_argument("");
    }
    if (j < 1 || j > 8){
	cout << "Error: Index for j must be between 1 and 8. Value of j is " << j << endl;
	throw std::invalid_argument("");
    }

    // Control what integer to read based on value of i
    switch(i) {
	case 1:
	    utility_pointer = &ab;
	    break;
	case 2:
	    utility_pointer = &ab;
	    break;
	case 3:
	    utility_pointer = &cd;
	    break;
	case 4:
	    utility_pointer = &cd;
	    break;
	case 5:
	    utility_pointer = &ef;
	    break;
	case 6:
	    utility_pointer = &ef;
	    break;
	case 7:
	    utility_pointer = &gh;
	    break;
	case 8:
	    utility_pointer = &gh;
	    break;
    }

    unsigned long long int exponent = 8 * ((i - 1) % 2) + (j - 1);
    unsigned short int return_val = (*utility_pointer) / ((unsigned long long int) pow(16, exponent)) % 16;
    utility_pointer = nullptr;
    return i_to_p(return_val);
    

};

