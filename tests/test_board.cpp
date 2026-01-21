#include <cassert>
#include <cmath>
#include <iostream>
#include <climits>
#include "board.h"

using namespace std;

void test_setter_getter() {
    Board b;
    char tmp_char = 'z';

    // Verify row 1
    assert (b.get_index(1, 1) == 'R');
    assert (b.get_index(1, 2) == 'H');
    assert (b.get_index(1, 3) == 'B');
    assert (b.get_index(1, 4) == 'Q');
    assert (b.get_index(1, 5) == 'K');
    assert (b.get_index(1, 6) == 'B');
    assert (b.get_index(1, 7) == 'H');
    assert (b.get_index(1, 8) == 'R');

    // Check for all pawns (Verify row 2)
    for (int i = 1; i <= 8; i++) {
	assert(b.get_index(2, i) == 'P');
    }

    // Verify row 7
    for (int i = 1; i <= 8; i++) {
	assert(b.get_index(7, i) == 'p');
    }

    // Verify row 8
    assert (b.get_index(8, 1) == 'r');
    assert (b.get_index(8, 2) == 'h');
    assert (b.get_index(8, 3) == 'b');
    assert (b.get_index(8, 4) == 'q');
    assert (b.get_index(8, 5) == 'k');
    assert (b.get_index(8, 6) == 'b');
    assert (b.get_index(8, 7) == 'h');
    assert (b.get_index(8, 8) == 'r');


    // Test 1: fill empty board
    // Perform setting
    for (int i = 1; i <= 8; i++) {
	for (int j = 1; j <= 8; j++) {
	    // Set new value
	    b.set_value(i, j, 'p'); // Fill entire board with black pawns
	}
    }

    // Test setting
    for (int i = 1; i <= 8; i++) {
	for (int j = 1; j <= 8; j++) {
	    tmp_char = b.get_index(i, j);
	    assert(tmp_char == 'p'); // Fill entire board with black pawns
	}
    }

    // Test 2: Fill with only white pawns and test
    // Perform setting
    for (int i = 1; i <= 8; i++) {
	for (int j = 1; j <= 8; j++) {
	    b.set_value(i, j, 'n'); // Clear board
	}
    }

    // Test setting
    for (int i = 1; i <= 8; i++) {
	for (int j = 1; j <= 8; j++) {
	    tmp_char = b.get_index(i, j);
	    
	    if (tmp_char != 'n'){ // Fail condition
		b.get_index(i, j);
		std::cout << "tmp_char for test 2 is incorrect" << std::endl;
		std::cout << "i: " << i << "\t\tj:" << j << "\t\ttmp_char: " << tmp_char << std::endl;
		std::cout << "\n";
	    }

	    // std::cout << "tmp_char for test2: " << tmp_char << std::endl;
	    assert(tmp_char == 'n'); // Fill entire board with black pawns

	}
    }

};


int test_board() {
    test_setter_getter();
    std::cout << "All tests in test_board.cpp finished successfully!" << endl;
    return 0;
}
