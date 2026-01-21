#include <cassert>
#include <iostream>
#include "move_gen.h"

/*
File will test all functionality of the Game class.
*/

bool test_pawn_move() {
    MoveGen mg;

    // Board only has one white pawn at c2
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 17);
    mg.get_board().direct_set_board_section(4, 0);

    // Test 1: Single pawn, single move
    mg.generate_moves();
    if ((mg.get_board().next_moves.size() != 1) || (mg.get_board().next_moves[0].get_index(4, 3) != 'P')){
	std::cout << "test_pawn_move() failed at single pawn test" << std::endl;
	return false;
    }

    return true;
};


// Main driver function for this test module
int test_move_gen() {
    // Run all functions defined above.
    bool all_pass = true;

    // Run test_setter and getter if no tests have failed to this point.
    all_pass = all_pass && test_pawn_move();
    
    if (all_pass)
	std::cout << "All tests ran successfully!" << std::endl;
    return 0;
}
