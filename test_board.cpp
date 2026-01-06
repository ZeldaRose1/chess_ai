#include <cassert>
#include <cmath>
#include <iostream>
#include <climits>
#include "board.h"

using namespace std;

void test_setter_getter() {
    // TODO Add Implementation after solving setters
    Board b;
    char tmp_char = 'z';

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

	    // Debug statement to print value before changes
	    if (i == 1 && j == 8) {
		// std::cout << "Value of ab before setting i=1, j=8\t\t" << b.ab << std::endl;
		cout << "";
	    }

	    b.set_value(i, j, 'n'); // Clear board

	    // Debug Statement to print value after changes
	    /*
	    if (i == 1 && j == 8) {
		std::cout << "Value of ab after setting i=1, j=8\t\t" << b.ab << std::endl;
	    }
	    */
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


int main() {
    test_setter_getter();
    std::cout << "All tests finished successfully!" << endl;
    return 0;
}
