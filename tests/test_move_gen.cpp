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
        mg.get_board().next_moves[1].get_index(6, 3) != 'P' 
       ) {
	std::cout << "test_move_gen test_pawn_move test 3 failed!" << std::endl;
	std::cout << "en-passant right capture failed:" << std::endl;
	mg.get_board().next_moves[1].print_board();
	return false;
    }


    // Test 4: black's turn
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    // Test setup
    mg.get_board().set_value(7, 1, 'p');
    mg.get_board().set_value(6, 2, 'P');
    mg.get_board().set_white_turn(false); // Force black's turn.

    // Generate moves
    mg.generate_moves();
    
    // Validate behavior
    // 1. Double step
    if ( // Fail conditions
        mg.get_board().next_moves[0].get_index(5, 1) != 'p' ||
        mg.get_board().next_moves[0].get_index(7, 1) != 'n' ||
        mg.get_board().next_moves[0].get_index(6, 2) != 'P' 
    ) {
        std::cout << "test_move_gen failed at pawn test 4.1!" << std::endl;
        mg.get_board().next_moves[0].print_board();
        return false;  
    } else if ( // Standard move
        mg.get_board().next_moves[1].get_index(5, 1) != 'n' ||
        mg.get_board().next_moves[1].get_index(6, 1) != 'p' ||
        mg.get_board().next_moves[1].get_index(7, 1) != 'n' ||
        mg.get_board().next_moves[1].get_index(6, 2) != 'P' 
    ) {
        std::cout << "test_move_gen failed at pawn test 4.2!" << std::endl;
        mg.get_board().next_moves[1].print_board();
        return false;
    } else if ( // Left capture test
        mg.get_board().next_moves[2].get_index(5, 1) != 'n' ||
        mg.get_board().next_moves[2].get_index(6, 1) != 'n' ||
        mg.get_board().next_moves[2].get_index(7, 1) != 'n' ||
        mg.get_board().next_moves[2].get_index(6, 2) != 'p' 
    ) {
        std::cout << "test_move_gen failed at pawn test 4.3!" << std::endl;
        mg.get_board().next_moves[2].print_board();
        return false;
    }

    return true;
};


bool test_bishop_move(){
    // Function to validate performance of bishop_move()
    MoveGen mg;
    
    /*    Test 1: Upper Right Diagonal    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    mg.get_board().set_value(1, 1, 'B');
    mg.get_board().set_value(6, 6, 'p');

    // Run generator function
    mg.generate_moves();

    // Validate move generator
    if (mg.get_board().next_moves.size() != 5){
	std::cout << "test_bishop() failed at test 1!";
	std::cout << "Incorrect number of moves generated" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[0].get_index(1, 1) != 'n' ||
	mg.get_board().next_moves[0].get_index(2, 2) != 'B' ||
	mg.get_board().next_moves[0].get_index(3, 3) != 'n' ||
	mg.get_board().next_moves[0].get_index(4, 4) != 'n' ||
	mg.get_board().next_moves[0].get_index(5, 5) != 'n' ||
	mg.get_board().next_moves[0].get_index(6, 6) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 1!";
	std::cout << "Invalid next_moves[0]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[1].get_index(1, 1) != 'n' ||
	mg.get_board().next_moves[1].get_index(2, 2) != 'n' ||
	mg.get_board().next_moves[1].get_index(3, 3) != 'B' ||
	mg.get_board().next_moves[1].get_index(4, 4) != 'n' ||
	mg.get_board().next_moves[1].get_index(5, 5) != 'n' ||
	mg.get_board().next_moves[1].get_index(6, 6) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 1!";
	std::cout << "Invalid next_moves[1]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[2].get_index(1, 1) != 'n' ||
	mg.get_board().next_moves[2].get_index(2, 2) != 'n' ||
	mg.get_board().next_moves[2].get_index(3, 3) != 'n' ||
	mg.get_board().next_moves[2].get_index(4, 4) != 'B' ||
	mg.get_board().next_moves[2].get_index(5, 5) != 'n' ||
	mg.get_board().next_moves[2].get_index(6, 6) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 1!";
	std::cout << "Invalid next_moves[2]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[3].get_index(1, 1) != 'n' ||
	mg.get_board().next_moves[3].get_index(2, 2) != 'n' ||
	mg.get_board().next_moves[3].get_index(3, 3) != 'n' ||
	mg.get_board().next_moves[3].get_index(4, 4) != 'n' ||
	mg.get_board().next_moves[3].get_index(5, 5) != 'B' ||
	mg.get_board().next_moves[3].get_index(6, 6) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 1!";
	std::cout << "Invalid next_moves[3]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[4].get_index(1, 1) != 'n' ||
	mg.get_board().next_moves[4].get_index(2, 2) != 'n' ||
	mg.get_board().next_moves[4].get_index(3, 3) != 'n' ||
	mg.get_board().next_moves[4].get_index(4, 4) != 'n' ||
	mg.get_board().next_moves[4].get_index(5, 5) != 'n' ||
	mg.get_board().next_moves[4].get_index(6, 6) != 'B'
    ) {
	std::cout << "test_bishop() failed at test 1!";
	std::cout << "Invalid next_moves[4]" << std::endl;
	return false;
    } 

    /*    Test 2: Upper Left Diagonal    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    mg.get_board().set_value(1, 8, 'B');
    mg.get_board().set_value(6, 3, 'p');

    // Run generator function
    mg.generate_moves();

    // Validate move generator
    if (mg.get_board().next_moves.size() != 5){
	std::cout << "test_bishop() failed at test 2!";
	std::cout << "Incorrect number of moves generated" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[0].get_index(1, 8) != 'n' ||
	mg.get_board().next_moves[0].get_index(2, 7) != 'B' ||
	mg.get_board().next_moves[0].get_index(3, 6) != 'n' ||
	mg.get_board().next_moves[0].get_index(4, 5) != 'n' ||
	mg.get_board().next_moves[0].get_index(5, 4) != 'n' ||
	mg.get_board().next_moves[0].get_index(6, 3) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 2!";
	std::cout << "Invalid next_moves[0]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[1].get_index(1, 8) != 'n' ||
	mg.get_board().next_moves[1].get_index(2, 7) != 'n' ||
	mg.get_board().next_moves[1].get_index(3, 6) != 'B' ||
	mg.get_board().next_moves[1].get_index(4, 5) != 'n' ||
	mg.get_board().next_moves[1].get_index(5, 4) != 'n' ||
	mg.get_board().next_moves[1].get_index(6, 3) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 2!";
	std::cout << "Invalid next_moves[1]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[2].get_index(1, 8) != 'n' ||
	mg.get_board().next_moves[2].get_index(2, 7) != 'n' ||
	mg.get_board().next_moves[2].get_index(3, 6) != 'n' ||
	mg.get_board().next_moves[2].get_index(4, 5) != 'B' ||
	mg.get_board().next_moves[2].get_index(5, 4) != 'n' ||
	mg.get_board().next_moves[2].get_index(6, 3) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 2!";
	std::cout << "Invalid next_moves[2]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[3].get_index(1, 8) != 'n' ||
	mg.get_board().next_moves[3].get_index(2, 7) != 'n' ||
	mg.get_board().next_moves[3].get_index(3, 6) != 'n' ||
	mg.get_board().next_moves[3].get_index(4, 5) != 'n' ||
	mg.get_board().next_moves[3].get_index(5, 4) != 'B' ||
	mg.get_board().next_moves[3].get_index(6, 3) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 2!";
	std::cout << "Invalid next_moves[3]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[4].get_index(1, 8) != 'n' ||
	mg.get_board().next_moves[4].get_index(2, 7) != 'n' ||
	mg.get_board().next_moves[4].get_index(3, 6) != 'n' ||
	mg.get_board().next_moves[4].get_index(4, 5) != 'n' ||
	mg.get_board().next_moves[4].get_index(5, 4) != 'n' ||
	mg.get_board().next_moves[4].get_index(6, 3) != 'B'
    ) {
	std::cout << "test_bishop() failed at test 2!";
	std::cout << "Invalid next_moves[4]" << std::endl;
	return false;
    } 

    /*    Test 3: Lower Left Diagonal    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    mg.get_board().set_value(8, 8, 'B');
    mg.get_board().set_value(3, 3, 'p');

    // Run generator function
    mg.generate_moves();

    // Validate move generator
    if (mg.get_board().next_moves.size() != 5){
	std::cout << "test_bishop() failed at test 3!";
	std::cout << "Incorrect number of moves generated" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[0].get_index(8, 8) != 'n' ||
	mg.get_board().next_moves[0].get_index(7, 7) != 'B' ||
	mg.get_board().next_moves[0].get_index(6, 6) != 'n' ||
	mg.get_board().next_moves[0].get_index(5, 5) != 'n' ||
	mg.get_board().next_moves[0].get_index(4, 4) != 'n' ||
	mg.get_board().next_moves[0].get_index(3, 3) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 3!";
	std::cout << "Invalid next_moves[0]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[1].get_index(8, 8) != 'n' ||
	mg.get_board().next_moves[1].get_index(7, 7) != 'n' ||
	mg.get_board().next_moves[1].get_index(6, 6) != 'B' ||
	mg.get_board().next_moves[1].get_index(5, 5) != 'n' ||
	mg.get_board().next_moves[1].get_index(4, 4) != 'n' ||
	mg.get_board().next_moves[1].get_index(3, 3) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 3!";
	std::cout << "Invalid next_moves[1]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[2].get_index(8, 8) != 'n' ||
	mg.get_board().next_moves[2].get_index(7, 7) != 'n' ||
	mg.get_board().next_moves[2].get_index(6, 6) != 'n' ||
	mg.get_board().next_moves[2].get_index(5, 5) != 'B' ||
	mg.get_board().next_moves[2].get_index(4, 4) != 'n' ||
	mg.get_board().next_moves[2].get_index(3, 3) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 3!";
	std::cout << "Invalid next_moves[2]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[3].get_index(8, 8) != 'n' ||
	mg.get_board().next_moves[3].get_index(7, 7) != 'n' ||
	mg.get_board().next_moves[3].get_index(6, 6) != 'n' ||
	mg.get_board().next_moves[3].get_index(5, 5) != 'n' ||
	mg.get_board().next_moves[3].get_index(4, 4) != 'B' ||
	mg.get_board().next_moves[3].get_index(3, 3) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 3!";
	std::cout << "Invalid next_moves[3]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[4].get_index(8, 8) != 'n' ||
	mg.get_board().next_moves[4].get_index(7, 7) != 'n' ||
	mg.get_board().next_moves[4].get_index(6, 6) != 'n' ||
	mg.get_board().next_moves[4].get_index(5, 5) != 'n' ||
	mg.get_board().next_moves[4].get_index(4, 4) != 'n' ||
	mg.get_board().next_moves[4].get_index(3, 3) != 'B'
    ) {
	std::cout << "test_bishop() failed at test 3!";
	std::cout << "Invalid next_moves[4]" << std::endl;
	return false;
    } 

    /*    Test 4: Lower Right Diagonal    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    mg.get_board().set_value(8, 1, 'B');
    mg.get_board().set_value(3, 6, 'p');

    // Run generator function
    mg.generate_moves();

    // Validate move generator
    if (mg.get_board().next_moves.size() != 5){
	std::cout << "test_bishop() failed at test 4!";
	std::cout << "Incorrect number of moves generated" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[0].get_index(8, 1) != 'n' ||
	mg.get_board().next_moves[0].get_index(7, 2) != 'B' ||
	mg.get_board().next_moves[0].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[0].get_index(5, 4) != 'n' ||
	mg.get_board().next_moves[0].get_index(4, 5) != 'n' ||
	mg.get_board().next_moves[0].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 4!";
	std::cout << "Invalid next_moves[0]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[1].get_index(8, 1) != 'n' ||
	mg.get_board().next_moves[1].get_index(7, 2) != 'n' ||
	mg.get_board().next_moves[1].get_index(6, 3) != 'B' ||
	mg.get_board().next_moves[1].get_index(5, 4) != 'n' ||
	mg.get_board().next_moves[1].get_index(4, 5) != 'n' ||
	mg.get_board().next_moves[1].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 4!";
	std::cout << "Invalid next_moves[1]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[2].get_index(8, 1) != 'n' ||
	mg.get_board().next_moves[2].get_index(7, 2) != 'n' ||
	mg.get_board().next_moves[2].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[2].get_index(5, 4) != 'B' ||
	mg.get_board().next_moves[2].get_index(4, 5) != 'n' ||
	mg.get_board().next_moves[2].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 4!";
	std::cout << "Invalid next_moves[2]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[3].get_index(8, 1) != 'n' ||
	mg.get_board().next_moves[3].get_index(7, 2) != 'n' ||
	mg.get_board().next_moves[3].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[3].get_index(5, 4) != 'n' ||
	mg.get_board().next_moves[3].get_index(4, 5) != 'B' ||
	mg.get_board().next_moves[3].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_bishop() failed at test 4!";
	std::cout << "Invalid next_moves[3]" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[4].get_index(8, 1) != 'n' ||
	mg.get_board().next_moves[4].get_index(7, 2) != 'n' ||
	mg.get_board().next_moves[4].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[4].get_index(5, 4) != 'n' ||
	mg.get_board().next_moves[4].get_index(4, 5) != 'n' ||
	mg.get_board().next_moves[4].get_index(3, 6) != 'B'
    ) {
	std::cout << "test_bishop() failed at test 4!";
	std::cout << "Invalid next_moves[4]" << std::endl;
	return false;
    } 

    // Tests for all four directions passed
    return true;

};


bool test_rook_move(){
    // Validate performance of rook_move()
    MoveGen mg;

    /*    Test 1: Move Right    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    mg.get_board().set_value(1, 1, 'R');
    mg.get_board().set_value(1, 6, 'p');
    mg.get_board().set_value(2, 1, 'P'); // Block moving up
    mg.get_board().set_value(3, 1, 'p'); // Block pawn from moving

    // Run generator function
    mg.generate_moves();

    // Check output
    if (mg.get_board().next_moves.size() != 5){
	std::cout << "rook_move test 1 failed. Incorrect number of moves." << std::endl;
	std::cout << mg.get_board().next_moves.size() << "\tmove count" << std::endl;
	return false;
    }

    if (
	mg.get_board().next_moves[0].get_index(1, 1) != 'n' ||
	mg.get_board().next_moves[0].get_index(1, 2) != 'R' ||
	mg.get_board().next_moves[0].get_index(1, 3) != 'n' ||
	mg.get_board().next_moves[0].get_index(1, 4) != 'n' ||
	mg.get_board().next_moves[0].get_index(1, 5) != 'n' ||
	mg.get_board().next_moves[0].get_index(1, 6) != 'p' 
    ) {
	std::cout << "rook_move() failed test 1, board 0" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[1].get_index(1, 1) != 'n' ||
	mg.get_board().next_moves[1].get_index(1, 2) != 'n' ||
	mg.get_board().next_moves[1].get_index(1, 3) != 'R' ||
	mg.get_board().next_moves[1].get_index(1, 4) != 'n' ||
	mg.get_board().next_moves[1].get_index(1, 5) != 'n' ||
	mg.get_board().next_moves[1].get_index(1, 6) != 'p' 
    ) {
	std::cout << "rook_move() failed test 1, board 1" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[2].get_index(1, 1) != 'n' ||
	mg.get_board().next_moves[2].get_index(1, 2) != 'n' ||
	mg.get_board().next_moves[2].get_index(1, 3) != 'n' ||
	mg.get_board().next_moves[2].get_index(1, 4) != 'R' ||
	mg.get_board().next_moves[2].get_index(1, 5) != 'n' ||
	mg.get_board().next_moves[2].get_index(1, 6) != 'p' 
    ) {
	std::cout << "rook_move() failed test 1, board 2" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[3].get_index(1, 1) != 'n' ||
	mg.get_board().next_moves[3].get_index(1, 2) != 'n' ||
	mg.get_board().next_moves[3].get_index(1, 3) != 'n' ||
	mg.get_board().next_moves[3].get_index(1, 4) != 'n' ||
	mg.get_board().next_moves[3].get_index(1, 5) != 'R' ||
	mg.get_board().next_moves[3].get_index(1, 6) != 'p' 
    ) {
	std::cout << "rook_move() failed test 1, board 3" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[4].get_index(1, 1) != 'n' ||
	mg.get_board().next_moves[4].get_index(1, 2) != 'n' ||
	mg.get_board().next_moves[4].get_index(1, 3) != 'n' ||
	mg.get_board().next_moves[4].get_index(1, 4) != 'n' ||
	mg.get_board().next_moves[4].get_index(1, 5) != 'n' ||
	mg.get_board().next_moves[4].get_index(1, 6) != 'R' 
    ) {
	std::cout << "rook_move() failed test 1, board 4" << std::endl;
	return false;
    } 

    /*    Test 2: Move Up    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    mg.get_board().set_value(1, 8, 'R');
    mg.get_board().set_value(6, 8, 'p');
    mg.get_board().set_value(1, 7, 'P'); // Block moving left
    mg.get_board().set_value(2, 7, 'p'); // Block pawn from moving

    // Run generator function
    mg.generate_moves();

    // Check output
    if (mg.get_board().next_moves.size() != 5){
	std::cout << "rook_move test 2 failed. Incorrect number of moves." << std::endl;
	return false;
    }

    if (
	mg.get_board().next_moves[0].get_index(1, 8) != 'n' ||
	mg.get_board().next_moves[0].get_index(2, 8) != 'R' ||
	mg.get_board().next_moves[0].get_index(3, 8) != 'n' ||
	mg.get_board().next_moves[0].get_index(4, 8) != 'n' ||
	mg.get_board().next_moves[0].get_index(5, 8) != 'n' ||
	mg.get_board().next_moves[0].get_index(6, 8) != 'p' 
    ) {
	std::cout << "rook_move() failed test 2, board 0" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[1].get_index(1, 8) != 'n' ||
	mg.get_board().next_moves[1].get_index(2, 8) != 'n' ||
	mg.get_board().next_moves[1].get_index(3, 8) != 'R' ||
	mg.get_board().next_moves[1].get_index(4, 8) != 'n' ||
	mg.get_board().next_moves[1].get_index(5, 8) != 'n' ||
	mg.get_board().next_moves[1].get_index(6, 8) != 'p' 
    ) {
	std::cout << "rook_move() failed test 2, board 1" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[2].get_index(1, 8) != 'n' ||
	mg.get_board().next_moves[2].get_index(2, 8) != 'n' ||
	mg.get_board().next_moves[2].get_index(3, 8) != 'n' ||
	mg.get_board().next_moves[2].get_index(4, 8) != 'R' ||
	mg.get_board().next_moves[2].get_index(5, 8) != 'n' ||
	mg.get_board().next_moves[2].get_index(6, 8) != 'p' 
    ) {
	std::cout << "rook_move() failed test 2, board 2" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[3].get_index(1, 8) != 'n' ||
	mg.get_board().next_moves[3].get_index(2, 8) != 'n' ||
	mg.get_board().next_moves[3].get_index(3, 8) != 'n' ||
	mg.get_board().next_moves[3].get_index(4, 8) != 'n' ||
	mg.get_board().next_moves[3].get_index(5, 8) != 'R' ||
	mg.get_board().next_moves[3].get_index(6, 8) != 'p' 
    ) {
	std::cout << "rook_move() failed test 2, board 3" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[4].get_index(1, 8) != 'n' ||
	mg.get_board().next_moves[4].get_index(2, 8) != 'n' ||
	mg.get_board().next_moves[4].get_index(3, 8) != 'n' ||
	mg.get_board().next_moves[4].get_index(4, 8) != 'n' ||
	mg.get_board().next_moves[4].get_index(5, 8) != 'n' ||
	mg.get_board().next_moves[4].get_index(6, 8) != 'R' 
    ) {
	std::cout << "rook_move() failed test 2, board 4" << std::endl;
	return false;
    } 


    /*    Test 3: Move Left    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    mg.get_board().set_value(8, 8, 'R');
    mg.get_board().set_value(8, 3, 'p');
    mg.get_board().set_value(7, 8, 'P'); // Block moving down

    // Run generator function
    mg.generate_moves();

    // Check output
    if (mg.get_board().next_moves.size() != 5){
	std::cout << "rook_move test 3 failed. Incorrect number of moves." << std::endl;
	return false;
    }

    if (
	mg.get_board().next_moves[0].get_index(8, 8) != 'n' ||
	mg.get_board().next_moves[0].get_index(8, 7) != 'R' ||
	mg.get_board().next_moves[0].get_index(8, 6) != 'n' ||
	mg.get_board().next_moves[0].get_index(8, 5) != 'n' ||
	mg.get_board().next_moves[0].get_index(8, 4) != 'n' ||
	mg.get_board().next_moves[0].get_index(8, 3) != 'p' 
    ) {
	std::cout << "rook_move() failed test 3, board 0" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[1].get_index(8, 8) != 'n' ||
	mg.get_board().next_moves[1].get_index(8, 7) != 'n' ||
	mg.get_board().next_moves[1].get_index(8, 6) != 'R' ||
	mg.get_board().next_moves[1].get_index(8, 5) != 'n' ||
	mg.get_board().next_moves[1].get_index(8, 4) != 'n' ||
	mg.get_board().next_moves[1].get_index(8, 3) != 'p' 
    ) {
	std::cout << "rook_move() failed test 3, board 1" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[2].get_index(8, 8) != 'n' ||
	mg.get_board().next_moves[2].get_index(8, 7) != 'n' ||
	mg.get_board().next_moves[2].get_index(8, 6) != 'n' ||
	mg.get_board().next_moves[2].get_index(8, 5) != 'R' ||
	mg.get_board().next_moves[2].get_index(8, 4) != 'n' ||
	mg.get_board().next_moves[2].get_index(8, 3) != 'p' 
    ) {
	std::cout << "rook_move() failed test 3, board 2" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[3].get_index(8, 8) != 'n' ||
	mg.get_board().next_moves[3].get_index(8, 7) != 'n' ||
	mg.get_board().next_moves[3].get_index(8, 6) != 'n' ||
	mg.get_board().next_moves[3].get_index(8, 5) != 'n' ||
	mg.get_board().next_moves[3].get_index(8, 4) != 'R' ||
	mg.get_board().next_moves[3].get_index(8, 3) != 'p' 
    ) {
	std::cout << "rook_move() failed test 3, board 3" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[4].get_index(8, 8) != 'n' ||
	mg.get_board().next_moves[4].get_index(8, 7) != 'n' ||
	mg.get_board().next_moves[4].get_index(8, 6) != 'n' ||
	mg.get_board().next_moves[4].get_index(8, 5) != 'n' ||
	mg.get_board().next_moves[4].get_index(8, 4) != 'n' ||
	mg.get_board().next_moves[4].get_index(8, 3) != 'R' 
    ) {
	std::cout << "rook_move() failed test 3, board 4" << std::endl;
	return false;
    } 

    /*    Test 4: Move Down    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    mg.get_board().set_value(8, 1, 'R');
    mg.get_board().set_value(3, 1, 'p');
    mg.get_board().set_value(8, 2, 'P'); // Block moving right

    // Run generator function
    mg.generate_moves();

    // Check output
    if (mg.get_board().next_moves.size() != 5){
	std::cout << "rook_move test 4 failed. Incorrect number of moves." << std::endl;
	return false;
    }

    if (
	mg.get_board().next_moves[0].get_index(8, 1) != 'n' ||
	mg.get_board().next_moves[0].get_index(7, 1) != 'R' ||
	mg.get_board().next_moves[0].get_index(6, 1) != 'n' ||
	mg.get_board().next_moves[0].get_index(5, 1) != 'n' ||
	mg.get_board().next_moves[0].get_index(4, 1) != 'n' ||
	mg.get_board().next_moves[0].get_index(3, 1) != 'p' 
    ) {
	std::cout << "rook_move() failed test 4, board 0" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[1].get_index(8, 1) != 'n' ||
	mg.get_board().next_moves[1].get_index(7, 1) != 'n' ||
	mg.get_board().next_moves[1].get_index(6, 1) != 'R' ||
	mg.get_board().next_moves[1].get_index(5, 1) != 'n' ||
	mg.get_board().next_moves[1].get_index(4, 1) != 'n' ||
	mg.get_board().next_moves[1].get_index(3, 1) != 'p' 
    ) {
	std::cout << "rook_move() failed test 4, board 1" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[2].get_index(8, 1) != 'n' ||
	mg.get_board().next_moves[2].get_index(7, 1) != 'n' ||
	mg.get_board().next_moves[2].get_index(6, 1) != 'n' ||
	mg.get_board().next_moves[2].get_index(5, 1) != 'R' ||
	mg.get_board().next_moves[2].get_index(4, 1) != 'n' ||
	mg.get_board().next_moves[2].get_index(3, 1) != 'p' 
    ) {
	std::cout << "rook_move() failed test 4, board 2" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[3].get_index(8, 1) != 'n' ||
	mg.get_board().next_moves[3].get_index(7, 1) != 'n' ||
	mg.get_board().next_moves[3].get_index(6, 1) != 'n' ||
	mg.get_board().next_moves[3].get_index(5, 1) != 'n' ||
	mg.get_board().next_moves[3].get_index(4, 1) != 'R' ||
	mg.get_board().next_moves[3].get_index(3, 1) != 'p' 
    ) {
	std::cout << "rook_move() failed test 4, board 3" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[4].get_index(8, 1) != 'n' ||
	mg.get_board().next_moves[4].get_index(7, 1) != 'n' ||
	mg.get_board().next_moves[4].get_index(6, 1) != 'n' ||
	mg.get_board().next_moves[4].get_index(5, 1) != 'n' ||
	mg.get_board().next_moves[4].get_index(4, 1) != 'n' ||
	mg.get_board().next_moves[4].get_index(3, 1) != 'R' 
    ) {
	std::cout << "rook_move() failed test 4, board 4" << std::endl;
	return false;
    } 


    return true;
};


bool test_knight_move(){
    // Validate performance of knight_move()
    MoveGen mg;

    /*    Test 1: Capture tests    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    // Place knight
    mg.get_board().set_value(4, 4, 'H');

    // Place enemy pawns in order of move gen
    mg.get_board().set_value(5, 6, 'p');
    mg.get_board().set_value(6, 5, 'p');
    mg.get_board().set_value(6, 3, 'p');
    mg.get_board().set_value(5, 2, 'p');
    mg.get_board().set_value(3, 2, 'p');
    mg.get_board().set_value(2, 3, 'p');
    mg.get_board().set_value(2, 5, 'p');
    mg.get_board().set_value(3, 6, 'p');

    // Run generator function
    mg.generate_moves();

    // Validate output
    if (mg.get_board().next_moves.size() != 8) {
	std::cout << "test_knight_move test 1 failed. Wrong move count\t" << std::endl;
	std::cout << "Number of moves generated: " << mg.get_board().next_moves.size() << std::endl;
	return false;
    };

    if (
	mg.get_board().next_moves[0].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[0].get_index(5, 6) != 'H' ||
	mg.get_board().next_moves[0].get_index(6, 5) != 'p' ||
	mg.get_board().next_moves[0].get_index(6, 3) != 'p' ||
	mg.get_board().next_moves[0].get_index(5, 2) != 'p' ||
	mg.get_board().next_moves[0].get_index(3, 2) != 'p' ||
	mg.get_board().next_moves[0].get_index(2, 3) != 'p' ||
	mg.get_board().next_moves[0].get_index(2, 5) != 'p' ||
	mg.get_board().next_moves[0].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_knight_move() failed at test 1: board 0" << std::endl;
	mg.get_board().next_moves[0].print_board();
	return false;
    } else if (
	mg.get_board().next_moves[1].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[1].get_index(5, 6) != 'p' ||
	mg.get_board().next_moves[1].get_index(6, 5) != 'H' ||
	mg.get_board().next_moves[1].get_index(6, 3) != 'p' ||
	mg.get_board().next_moves[1].get_index(5, 2) != 'p' ||
	mg.get_board().next_moves[1].get_index(3, 2) != 'p' ||
	mg.get_board().next_moves[1].get_index(2, 3) != 'p' ||
	mg.get_board().next_moves[1].get_index(2, 5) != 'p' ||
	mg.get_board().next_moves[1].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_knight_move() failed at test 1: board 1" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[2].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[2].get_index(5, 6) != 'p' ||
	mg.get_board().next_moves[2].get_index(6, 5) != 'p' ||
	mg.get_board().next_moves[2].get_index(6, 3) != 'H' ||
	mg.get_board().next_moves[2].get_index(5, 2) != 'p' ||
	mg.get_board().next_moves[2].get_index(3, 2) != 'p' ||
	mg.get_board().next_moves[2].get_index(2, 3) != 'p' ||
	mg.get_board().next_moves[2].get_index(2, 5) != 'p' ||
	mg.get_board().next_moves[2].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_knight_move() failed at test 1: board 2" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[3].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[3].get_index(5, 6) != 'p' ||
	mg.get_board().next_moves[3].get_index(6, 5) != 'p' ||
	mg.get_board().next_moves[3].get_index(6, 3) != 'p' ||
	mg.get_board().next_moves[3].get_index(5, 2) != 'H' ||
	mg.get_board().next_moves[3].get_index(3, 2) != 'p' ||
	mg.get_board().next_moves[3].get_index(2, 3) != 'p' ||
	mg.get_board().next_moves[3].get_index(2, 5) != 'p' ||
	mg.get_board().next_moves[3].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_knight_move() failed at test 1: board 3" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[4].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[4].get_index(5, 6) != 'p' ||
	mg.get_board().next_moves[4].get_index(6, 5) != 'p' ||
	mg.get_board().next_moves[4].get_index(6, 3) != 'p' ||
	mg.get_board().next_moves[4].get_index(5, 2) != 'p' ||
	mg.get_board().next_moves[4].get_index(3, 2) != 'H' ||
	mg.get_board().next_moves[4].get_index(2, 3) != 'p' ||
	mg.get_board().next_moves[4].get_index(2, 5) != 'p' ||
	mg.get_board().next_moves[4].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_knight_move() failed at test 1: board 4" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[5].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[5].get_index(5, 6) != 'p' ||
	mg.get_board().next_moves[5].get_index(6, 5) != 'p' ||
	mg.get_board().next_moves[5].get_index(6, 3) != 'p' ||
	mg.get_board().next_moves[5].get_index(5, 2) != 'p' ||
	mg.get_board().next_moves[5].get_index(3, 2) != 'p' ||
	mg.get_board().next_moves[5].get_index(2, 3) != 'H' ||
	mg.get_board().next_moves[5].get_index(2, 5) != 'p' ||
	mg.get_board().next_moves[5].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_knight_move() failed at test 1: board 5" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[6].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[6].get_index(5, 6) != 'p' ||
	mg.get_board().next_moves[6].get_index(6, 5) != 'p' ||
	mg.get_board().next_moves[6].get_index(6, 3) != 'p' ||
	mg.get_board().next_moves[6].get_index(5, 2) != 'p' ||
	mg.get_board().next_moves[6].get_index(3, 2) != 'p' ||
	mg.get_board().next_moves[6].get_index(2, 3) != 'p' ||
	mg.get_board().next_moves[6].get_index(2, 5) != 'H' ||
	mg.get_board().next_moves[6].get_index(3, 6) != 'p'
    ) {
	std::cout << "test_knight_move() failed at test 1: board 6" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[7].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[7].get_index(5, 6) != 'p' ||
	mg.get_board().next_moves[7].get_index(6, 5) != 'p' ||
	mg.get_board().next_moves[7].get_index(6, 3) != 'p' ||
	mg.get_board().next_moves[7].get_index(5, 2) != 'p' ||
	mg.get_board().next_moves[7].get_index(3, 2) != 'p' ||
	mg.get_board().next_moves[7].get_index(2, 3) != 'p' ||
	mg.get_board().next_moves[7].get_index(2, 5) != 'p' ||
	mg.get_board().next_moves[7].get_index(3, 6) != 'H'
    ) {
	std::cout << "test_knight_move() failed at test 1: board 7" << std::endl;
	return false;
    }

    // Debug statement
    std::cout << "test_knight_move() test 1 passed!" << std::endl;

    
    /*    Test 2: Move tests    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    // Place knight
    mg.get_board().set_value(4, 4, 'H');

    // Place enemy pawns in order of move gen
    // mg.get_board().set_value(5, 6, 'n');
    // mg.get_board().set_value(6, 5, 'n');
    // mg.get_board().set_value(6, 3, 'n');
    // mg.get_board().set_value(5, 2, 'n');
    // mg.get_board().set_value(3, 2, 'n');
    // mg.get_board().set_value(2, 3, 'n');
    // mg.get_board().set_value(2, 5, 'n');
    // mg.get_board().set_value(3, 6, 'n');

    // Run generator function
    mg.generate_moves();

    // Validate output
    if (mg.get_board().next_moves.size() != 8) {
	std::cout << "test_knight_move test 2 failed. Wrong move count\t" << std::endl;
	std::cout << "Number of moves generated: " << mg.get_board().next_moves.size() << std::endl;
	return false;
    };

    if (
	mg.get_board().next_moves[0].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[0].get_index(5, 6) != 'H' ||
	mg.get_board().next_moves[0].get_index(6, 5) != 'n' ||
	mg.get_board().next_moves[0].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[0].get_index(5, 2) != 'n' ||
	mg.get_board().next_moves[0].get_index(3, 2) != 'n' ||
	mg.get_board().next_moves[0].get_index(2, 3) != 'n' ||
	mg.get_board().next_moves[0].get_index(2, 5) != 'n' ||
	mg.get_board().next_moves[0].get_index(3, 6) != 'n'
    ) {
	std::cout << "test_knight_move() failed at test 2: board 0" << std::endl;
	mg.get_board().next_moves[0].print_board();
	return false;
    } else if (
	mg.get_board().next_moves[1].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[1].get_index(5, 6) != 'n' ||
	mg.get_board().next_moves[1].get_index(6, 5) != 'H' ||
	mg.get_board().next_moves[1].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[1].get_index(5, 2) != 'n' ||
	mg.get_board().next_moves[1].get_index(3, 2) != 'n' ||
	mg.get_board().next_moves[1].get_index(2, 3) != 'n' ||
	mg.get_board().next_moves[1].get_index(2, 5) != 'n' ||
	mg.get_board().next_moves[1].get_index(3, 6) != 'n'
    ) {
	std::cout << "test_knight_move() failed at test 2: board 1" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[2].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[2].get_index(5, 6) != 'n' ||
	mg.get_board().next_moves[2].get_index(6, 5) != 'n' ||
	mg.get_board().next_moves[2].get_index(6, 3) != 'H' ||
	mg.get_board().next_moves[2].get_index(5, 2) != 'n' ||
	mg.get_board().next_moves[2].get_index(3, 2) != 'n' ||
	mg.get_board().next_moves[2].get_index(2, 3) != 'n' ||
	mg.get_board().next_moves[2].get_index(2, 5) != 'n' ||
	mg.get_board().next_moves[2].get_index(3, 6) != 'n'
    ) {
	std::cout << "test_knight_move() failed at test 2: board 2" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[3].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[3].get_index(5, 6) != 'n' ||
	mg.get_board().next_moves[3].get_index(6, 5) != 'n' ||
	mg.get_board().next_moves[3].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[3].get_index(5, 2) != 'H' ||
	mg.get_board().next_moves[3].get_index(3, 2) != 'n' ||
	mg.get_board().next_moves[3].get_index(2, 3) != 'n' ||
	mg.get_board().next_moves[3].get_index(2, 5) != 'n' ||
	mg.get_board().next_moves[3].get_index(3, 6) != 'n'
    ) {
	std::cout << "test_knight_move() failed at test 2: board 3" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[4].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[4].get_index(5, 6) != 'n' ||
	mg.get_board().next_moves[4].get_index(6, 5) != 'n' ||
	mg.get_board().next_moves[4].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[4].get_index(5, 2) != 'n' ||
	mg.get_board().next_moves[4].get_index(3, 2) != 'H' ||
	mg.get_board().next_moves[4].get_index(2, 3) != 'n' ||
	mg.get_board().next_moves[4].get_index(2, 5) != 'n' ||
	mg.get_board().next_moves[4].get_index(3, 6) != 'n'
    ) {
	std::cout << "test_knight_move() failed at test 2: board 4" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[5].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[5].get_index(5, 6) != 'n' ||
	mg.get_board().next_moves[5].get_index(6, 5) != 'n' ||
	mg.get_board().next_moves[5].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[5].get_index(5, 2) != 'n' ||
	mg.get_board().next_moves[5].get_index(3, 2) != 'n' ||
	mg.get_board().next_moves[5].get_index(2, 3) != 'H' ||
	mg.get_board().next_moves[5].get_index(2, 5) != 'n' ||
	mg.get_board().next_moves[5].get_index(3, 6) != 'n'
    ) {
	std::cout << "test_knight_move() failed at test 2: board 5" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[6].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[6].get_index(5, 6) != 'n' ||
	mg.get_board().next_moves[6].get_index(6, 5) != 'n' ||
	mg.get_board().next_moves[6].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[6].get_index(5, 2) != 'n' ||
	mg.get_board().next_moves[6].get_index(3, 2) != 'n' ||
	mg.get_board().next_moves[6].get_index(2, 3) != 'n' ||
	mg.get_board().next_moves[6].get_index(2, 5) != 'H' ||
	mg.get_board().next_moves[6].get_index(3, 6) != 'n'
    ) {
	std::cout << "test_knight_move() failed at test 2: board 6" << std::endl;
	return false;
    } else if (
	mg.get_board().next_moves[7].get_index(4, 4) != 'n' ||

	mg.get_board().next_moves[7].get_index(5, 6) != 'n' ||
	mg.get_board().next_moves[7].get_index(6, 5) != 'n' ||
	mg.get_board().next_moves[7].get_index(6, 3) != 'n' ||
	mg.get_board().next_moves[7].get_index(5, 2) != 'n' ||
	mg.get_board().next_moves[7].get_index(3, 2) != 'n' ||
	mg.get_board().next_moves[7].get_index(2, 3) != 'n' ||
	mg.get_board().next_moves[7].get_index(2, 5) != 'n' ||
	mg.get_board().next_moves[7].get_index(3, 6) != 'H'
    ) {
	std::cout << "test_knight_move() failed at test 2: board 7" << std::endl;
	return false;
    }

    // Debug statement
    std::cout << "test_knight_move() test 2 passed!" << std::endl;
 
    /*    Test 3: White Blocking    */
    // Setup board for initial Test
    mg.get_board().direct_set_board_section(1, 0);
    mg.get_board().direct_set_board_section(2, 0);
    mg.get_board().direct_set_board_section(3, 0);
    mg.get_board().direct_set_board_section(4, 0);

    // Place knight
    mg.get_board().set_value(4, 4, 'H');

    // Place enemy pawns in order of move gen
    mg.get_board().set_value(5, 6, 'P');
    mg.get_board().set_value(6, 5, 'P');
    mg.get_board().set_value(6, 3, 'P');
    mg.get_board().set_value(5, 2, 'P');
    mg.get_board().set_value(3, 2, 'P');
    mg.get_board().set_value(2, 3, 'P');
    mg.get_board().set_value(2, 5, 'P');
    mg.get_board().set_value(3, 6, 'P');

    // Block pawns from moving
    mg.get_board().set_value(6, 6, 'p');
    mg.get_board().set_value(7, 5, 'p');
    mg.get_board().set_value(7, 3, 'p');
    mg.get_board().set_value(6, 2, 'p');
    mg.get_board().set_value(4, 2, 'p');
    mg.get_board().set_value(3, 3, 'p');
    mg.get_board().set_value(3, 5, 'p');
    mg.get_board().set_value(4, 6, 'p');

    std::cout << "test_knight_move() test 3 board setup!" << std::endl;
    // Run generator function
    mg.generate_moves();

    // Validate output
    if (mg.get_board().next_moves.size() != 0){
	std::cout << "test_knight_move() failed at test 3. Wrong move count generated" << std::endl;
	std::cout << "Expected:  0\t\tOutput:  " << mg.get_board().next_moves.size() << std::endl;
	return false;
    };

    // If all tests pass, return true
    return true;
};


// Main driver function for this test module
int test_move_gen() {
    // Run all functions defined above.
    bool all_pass = true;

    // Run test_setter and getter if no tests have failed to this point.
    all_pass = all_pass && test_pawn_move();
    all_pass = all_pass && test_bishop_move();
    all_pass = all_pass && test_rook_move();
    all_pass = all_pass && test_knight_move();
    
    if (all_pass)
	std::cout << "All tests ran successfully!" << std::endl;
    return 0;
}
