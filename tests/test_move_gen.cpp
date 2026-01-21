#include <cassert>
#include <iostream>
#include "move_gen.h"

/*
File will test all functionality of the Game class.
*/

bool test_pawn_move() {
    MoveGen mg;

    // Board tests only one white pawn (d2)
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);
    mg.get_board().set_value(2, 4, 'P');
    mg.get_board().set_value(7, 1, 'p');

    // Test 1: Single pawn, may move single or double space.
    mg.generate_moves();
    if (mg.get_board().next_moves.size() != 2){
	std::cout << "test_pawn_move() failed to generate 2 moves on single pawn at row 2" << std::endl;
	std::cout << "Size of next_moves vector: << " << mg.get_board().next_moves.size() << std::endl;
	return false;
    } else if (
	    mg.get_board().next_moves[0].get_index(2, 4) != 'n' ||
	    mg.get_board().next_moves[0].get_index(3, 4) != 'n' ||
	    mg.get_board().next_moves[0].get_index(4, 4) != 'P'
	) {
	mg.get_board().next_moves[0].print_board();
	std::cout << "test_pawn_move() on single pawn test failed to generate the double step";
	std::cout << " properly." << std::endl;
	return false;
    } else if (
	    mg.get_board().next_moves[1].get_index(2, 4) != 'n' ||
	    mg.get_board().next_moves[1].get_index(3, 4) != 'P' ||
	    mg.get_board().next_moves[1].get_index(4, 4) != 'n'
	) {
	mg.get_board().next_moves[1].print_board();
	std::cout << "test_pawn_move() on single pawn test failed to generate the single step";
	std::cout << " properly." << std::endl;
	return false;
    }
    

    // Test 2: Capture left and right from white's turn.
    // Board setup
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);
    mg.get_board().set_value(3, 4, 'P');
    mg.get_board().set_value(4, 3, 'p');
    mg.get_board().set_value(4, 5, 'p');

    mg.generate_moves();
    if (
	mg.get_board().next_moves[1].get_index(4, 3) != 'P' ||
	mg.get_board().next_moves[1].get_index(3, 4) != 'n' ||
	mg.get_board().next_moves[1].get_index(4, 5) != 'p'
       ) {
	std::cout << "test_move_gen test_pawn_move test 2 failed!" << std::endl;
	std::cout << "left capture failed:" << std::endl;
	mg.get_board().next_moves[1].print_board();
	return false;
    }else if (
	mg.get_board().next_moves[2].get_index(4, 3) != 'p' ||
	mg.get_board().next_moves[2].get_index(3, 4) != 'n' ||
	mg.get_board().next_moves[2].get_index(4, 5) != 'P'
       ) {
	std::cout << "test_move_gen test_pawn_move test 2 failed!" << std::endl;
	std::cout << "right capture failed:" << std::endl;
	mg.get_board().next_moves[2].print_board();
	return false;
    }

    // Test 3: White move with en-passant
    // Board setup
    Board previous_board;

    previous_board.direct_set_board_section(1, 0);
    previous_board.direct_set_board_section(2, 0);
    previous_board.direct_set_board_section(3, 0);
    previous_board.direct_set_board_section(4, 0);

    previous_board.set_value(7, 1, 'p');
    previous_board.set_value(7, 3, 'p');

    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    mg.get_board().set_value(5, 1, 'p');
    mg.get_board().set_value(5, 3, 'p');
    mg.get_board().set_value(5, 2, 'P');
    mg.get_board().set_value(6, 2, 'k'); // Block white pawn from moving forward
    mg.get_board().board_history.push_back(previous_board);

    mg.generate_moves();
    mg.get_board().print_board();
    if ( // next_moves[0] is the left capture scenario
	mg.get_board().next_moves[0].get_index(5, 1) != 'n' ||
	mg.get_board().next_moves[0].get_index(5, 2) != 'n' ||
	mg.get_board().next_moves[0].get_index(6, 1) != 'P' ||
	mg.get_board().next_moves[0].get_index(6, 2) != 'k' ||
        mg.get_board().next_moves[0].get_index(5, 3) != 'p' 
       ) {
	std::cout << "test_move_gen test_pawn_move test 3 failed!" << std::endl;
	std::cout << "en-passant left capture failed:" << std::endl;
	mg.get_board().next_moves[0].print_board();
	return false;
    }else if (
	mg.get_board().next_moves[1].get_index(5, 1) != 'p' ||
	mg.get_board().next_moves[1].get_index(5, 2) != 'n' ||
	mg.get_board().next_moves[1].get_index(6, 1) != 'n' ||
	mg.get_board().next_moves[1].get_index(6, 2) != 'k' ||
        mg.get_board().next_moves[1].get_index(5, 3) != 'P' 
       ) {
	std::cout << "test_move_gen test_pawn_move test 3 failed!" << std::endl;
	std::cout << "en-passant right capture failed:" << std::endl;
	mg.get_board().next_moves[1].print_board();
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
