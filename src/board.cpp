#include <cmath>
#include <iostream>
#include <stdexcept>

#include "board.h"

using namespace std;

/*
   Function definitions for the Board class
*/

Board::Board() {
    // Constructor for board.
    ab = 1229782938568512322;
    cd = 0;
    ef = 0;
    gh = 14607596558135188957;

    white_turn = true;
};

Board::Board(const Board &input) {
    // Copy Constructor
    ab = input.ab;
    cd = input.cd;
    ef = input.ef;
    gh = input.gh;
    
    white_turn = input.white_turn;
    next_moves = input.next_moves;
    board_history = board_history;
}

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
	    H: white knight (horse) - 04
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

    unsigned short int exponent = 8 * ((i - 1) % 2) + (j - 1);
    unsigned long long int return_val = ((*utility_pointer) / ((unsigned long long int) pow(16, exponent))) % 16;
    utility_pointer = nullptr;
    return i_to_p(return_val);
    

};


void Board::print_board() {
    // Prints board to screen

    // Initializations
    char cur_space;

    // Loop over all squares on the board
    for (int i = 8; i >= 1; i--) {
	for (int j = 1; j <= 8; j++) {
	    cur_space = get_index(i, j);
	    std::cout << cur_space << ' ';
	}
	std::cout << std::endl;
    }
};


void Board::direct_set_board_section(int section_no, unsigned long long int new_val) {
    switch(section_no) {
	case 1: // This is the lower section of the board
	    ab = new_val;
	    break;
	case 2: // Mid-lower
	    cd = new_val;
	    break;
	case 3: // Mid-upper
	    ef = new_val;
	    break;
	case 4: // Top
	    gh = new_val;
	    break;
	default:
	    std::cout << "Invalid argument passed to direct_set_board_section()\t\t" << section_no << std::endl;
    };
}


bool Board::get_white_turn(){
    return white_turn;
};

void Board::set_white_turn(bool wt){
    white_turn = wt;
};
