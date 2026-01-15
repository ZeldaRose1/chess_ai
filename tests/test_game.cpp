#include <cassert>
#include <iostream>
#include "game.h"

/*
File will test all functionality of the Game class.
*/

bool test_setter_and_getter() {
    // Ensures get_board() and set_board() behave as expected
    Game g;
    Board tboard;
    bool test_pass = true;

    //		Test Getter on default board	    //
    // Check bottom row
    if (g.get_board().get_index(1, 1) != 'R')
	test_pass = false;
    if (g.get_board().get_index(1, 2) != 'H')
	test_pass = false;
    if (g.get_board().get_index(1, 3) != 'B')
	test_pass = false;
    if (g.get_board().get_index(1, 4) != 'Q')
	test_pass = false;
    if (g.get_board().get_index(1, 5) != 'K')
	test_pass = false;
    if (g.get_board().get_index(1, 6) != 'B')
	test_pass = false;
    if (g.get_board().get_index(1, 7) != 'H')
	test_pass = false;
    if (g.get_board().get_index(1, 8) != 'R')
	test_pass = false;
    
    // Check row 2
    for (int j = 1; j <= 8; j++) {
	if (g.get_board.get_index(2, j) != 'P')
	    test_pass = false;
    }

    // Check rows 3 - 6
    for int (i = 3; i <= 6; i++) {
        for (int j = 1; j <= 8; j++) {
        	if (g.get_board.get_index(2, j) != 'n')
        	    test_pass = false;
            }
    }

    // Check row 7
    for (int j = 1; j <= 8; j++) {
	if (g.get_board.get_index(7, j) != 'p')
	    test_pass = false;
    }

    // Check row 8
    if (g.get_board().get_index(8, 1) != 'r')
	test_pass = false;
    if (g.get_board().get_index(8, 2) != 'h')
	test_pass = false;
    if (g.get_board().get_index(8, 3) != 'b')
	test_pass = false;
    if (g.get_board().get_index(8, 4) != 'q')
	test_pass = false;
    if (g.get_board().get_index(8, 5) != 'k')
	test_pass = false;
    if (g.get_board().get_index(8, 6) != 'b')
	test_pass = false;
    if (g.get_board().get_index(8, 7) != 'h')
	test_pass = false;
    if (g.get_board().get_index(8, 8) != 'r')
	test_pass = false;

    // Report on failure
    if (!test_pass) {
	std::cout << "Error in test_setter_and_getter!" << std::endl;
	std::cout << "Default constructor Board::Board initialized to the wrong value";
	std::cout << ", Board::get_index(i, j) failed, or Game::get_board() failed." << std::endl;
	return test_pass;
    }

    //		Test setter		//
    for (int i = 0; i <= 8; i++) {
	for (jnt j = 0; j <= 8; j++) {
	    tboard.set_value(i, j, 'n');
        }
    }

    g.set_board(tboard);
    if (g.get_board() != tboard) {
	std::cout << "Error in test_setter_and_getter!" << std::endl;
	std::cout << "Setter failed equality check with the board it was set to!" << std::endl;
	test_pass = false;
	return test_pass;
    }

    return test_pass;
};


int main() {
    // Run all functions defined above.
    bool all_pass = true;

    // Run test_setter and getter if no tests have failed to this point.
    all_pass = all_pass && test_setter_and_getter();
    
    if (all_pass)
	std::cout << "All tests ran successfully!" << std::endl;
    return 0;
}
