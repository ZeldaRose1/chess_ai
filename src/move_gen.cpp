#include "move_gen.h"

/*
Logic to generate moves given a game state.
*/


MoveGen::MoveGen(){
};

void MoveGen::set_board(Board input_board) {
    b = input_board;
};

void MoveGen::generate_moves() {
    // Function will loop through all squares and call the specific piece_move function
    for (int i = 1; i <= 8; i++) {
	for (int j = 1; j <= 8; j++) {
	    switch (b.get_index(i, j)) {
		case 'p':
		    move_pawn(i, j);
		    break;
		case 'P':
		    move_pawn(i, j);
		    break;
		case 'b':
		    move_bishop(i, j);
		    break;
		case 'B':
		    move_bishop(i, j);
		    break;
		case 'r':
		    move_rook(i, j);
		    break;
		case 'R':
		    move_rook(i, j);
		    break;
		case 'h':
		    move_knight(i, j);
		    break;
		case 'H':
		    move_knight(i, j);
		    break;
		case 'q':
		    move_queen(i, j);
		    break;
		case 'Q':
		    move_queen(i, j);
		    break;
		case 'k':
		    move_king(i, j);
		    break;
		case 'K':
		    move_king(i, j);
		    break;
		default:
		    break;
	    }
	}
    }

    // All moves have been generated. Close function
    return;
};

// Begin move functions
void MoveGen::pawn_move(int i, int j){
    // Function takes coordinates of square and generates all moves for a pawn
    // based on current board state.
    
    /*       Ensure pre-conditions      */

    if (b.get_index(i, j) != 'p' || b.get_index(i, j) != 'P') {
	std::cout << "Error: pawn_move() called on a non-pawn piece." << std::endl;
	throw std::logic_error;
    }

    if (i < 1 || i > 8 || j < 1 || j > 8) {
	std::cout << "Error: pawn_move() called with invalid indices!\t";
	std::cout << "i = " << i << "\t\t j = " << j << std::endl;
	throw std::logic_error;
    };

    // Check if it is the correct turn.
    if (b.white_turn && b.get_index(i, j) == 'p')
	return
    if (!b.white_turn && b.get_index(i, j) == 'P')
	return
    
    /*      Generate pawn moves      */
    if (b.get_white_turn) {
	Board b_app;

	// Double square move on initial pawn space
	if (i == 2 && b.get_index(3, j) == 'n' && b.get_index(4, j) == 'n') {
	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(4, j, 'P');
	    b_app.set_white_turn(false);
	    b_app.board_history.append(b);
	    b.next_moves.append(b_app);
	}
	
	// Default pawn move
	if (i < 7 && b.get_index(i + 1, j) == 'n') { // basic move cannot enter last row.
	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i + 1, j, 'P');
	    b_app.set_white_turn(false);
	    b_app.board_history.append(b);
	    b.next_moves.append(b_app);
	}

	// Standard capture rule (left)
	
	if (j > 1 && i < 8) { 
	    char left_cap = b.get_index(i + 1, j - 1);
	    if ( // Check if piece one forward and left is enemy piece
		left_cap == 'p' || left_cap == 'r' || left_cap == 'b' || 
		left_cap == 'h' || left_cap == 'q' || left_cap == 'k'
	    ) { // Capture enemy piece
		b_app = b;
		b_app.set_value(i + 1, j - 1, 'P');
		b_app.set_value(i, j, 'n');
		b_app.set_white_turn(false);
	        b_app.board_history.append(b);
		b.next_moves.append(b_app);
	    } else if ( // En Passant rule
		left_cap == 'n' && i == 5 && b.board_history.back().get_index(7, j - 1) == 'p' &&
		b.get_index(5, j - 1) == 'p' && b.get_index(7, j - 1) == 'n'
	    ) {
		b_app = b;
		b_app.set_value(i + 1, j - 1, 'P');
		b_app.set_value(i, j, 'n');
	
	    }b_app.set_value(i, j - 1, 'n');
		b_app.set_white_turn(false);
	        b_app.board_history.append(b);
	    }

	// Standard capture rule (right)
	
	if (j < 8 && i < 8) { 
	    char right_cap = b.get_index(i + 1, j + 1);
	    right_cap ( // Check if piece one forward and left is enemy piece
		right_cap == 'p' || right_cap == 'r' || right_cap == 'b' || 
		right_cap == 'h' || right_cap == 'q' || right_cap == 'k'
	    ) { // Capture enemy piece
		b_app = b;
		b_app.set_value(i + 1, j + 1, 'P');
		b_app.set_value(i, j, 'n');
		b_app.set_white_turn(false);
	        b_app.board_history.append(b);
		b.next_moves.append(b_app);
	    } else if ( // En Passant rule
		right_cap == 'n' && i == 5 && b.board_history.back().get_index(7, j + 1) == 'p' &&
		b.get_index(5, j + 1) == 'p' && b.get_index(7, j + 1) == 'n'
	    ) {
		b_app = b;
		b_app.set_value(i + 1, j + 1, 'P');
		b_app.set_value(i, j, 'n');
		b_app.set_value(i, j + 1, 'n');
		b_app.set_white_turn(false);
	        b_app.board_history.append(b);
	}
    }

	// Promotion rule
	
	if (i == 7 && b.get_index(8, j) == 'n') {
	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i + 1, j, 'R');
	    b_app.set_white_turn(false);
	    b_app.board_history.append(b);

	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i + 1, j, 'B');
	    b_app.set_white_turn(false);
	    b_app.board_history.append(b);

	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i + 1, j, 'H');
	    b_app.set_white_turn(false);
	    b_app.board_history.append(b);

	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i + 1, j, 'Q');
	    b_app.set_white_turn(false);
	    b_app.board_history.append(b);
	}
    } else { // Black's turn

	// TODO!! Rewrite this to work for black's moves

	// Double square move on initial pawn space
	if (i == 7 && b.get_index(6, j) == 'n' && b.get_index(5, j) == 'n') {
	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i - 2, j, 'p');
	    b_app.set_white_turn(true);
	    b_app.board_history.append(b);
	    b.next_moves.append(b_app);
	}
	
	// Default pawn move
	if (i > 2 && b.get_index(i - 1, j) == 'n') { // basic move cannot enter last row.
	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i - 1, j, 'p');
	    b_app.set_white_turn(true);
	    b_app.board_history.append(b);
	    b.next_moves.append(b_app);
	}

	// Standard capture rule (left)
	
	if (j > 1 && i < 8) { 
	    char left_cap = b.get_index(i - 1, j + 1);
	    if ( // Check if piece one forward and left is enemy piece
		left_cap == 'P' || left_cap == 'R' || left_cap == 'B' || 
		left_cap == 'H' || left_cap == 'Q' || left_cap == 'K'
	    ) { // Capture enemy piece
		b_app = b;
		b_app.set_value(i - 1, j + 1, 'p');
		b_app.set_value(i, j, 'n');
		b_app.set_white_turn(true);
	        b_app.board_history.append(b);
		b.next_moves.append(b_app);
	    } else if ( // En Passant rule // TODO Edits stopped here
		left_cap == 'n' && i == 4 && b.board_history.back().get_index(7, j - 1) == 'p' &&
		b.get_index(4, j + 1) == 'p' && b.get_index(7, j - 1) == 'n'
	    ) {
		b_app = b;
		b_app.set_value(i + 1, j - 1, 'P');
		b_app.set_value(i, j, 'n');
	
	    }b_app.set_value(i, j - 1, 'n');
		b_app.set_white_turn(false);
	        b_app.board_history.append(b);
	    }

	// Standard capture rule (right)
	
	if (j < 8 && i < 8) { 
	    char right_cap = b.get_index(i + 1, j + 1);
	    right_cap ( // Check if piece one forward and left is enemy piece
		right_cap == 'p' || right_cap == 'r' || right_cap == 'b' || 
		right_cap == 'h' || right_cap == 'q' || right_cap == 'k'
	    ) { // Capture enemy piece
		b_app = b;
		b_app.set_value(i + 1, j + 1, 'P');
		b_app.set_value(i, j, 'n');
		b_app.set_white_turn(false);
	        b_app.board_history.append(b);
		b.next_moves.append(b_app);
	    } else if ( // En Passant rule
		right_cap == 'n' && i == 5 && b.board_history.back().get_index(7, j + 1) == 'p' &&
		b.get_index(5, j + 1) == 'p' && b.get_index(7, j + 1) == 'n'
	    ) {
		b_app = b;
		b_app.set_value(i + 1, j + 1, 'P');
		b_app.set_value(i, j, 'n');
		b_app.set_value(i, j + 1, 'n');
		b_app.set_white_turn(false);
	        b_app.board_history.append(b);
	}
    }

	// Promotion rule
	
	if (i == 7 && b.get_index(8, j) == 'n') {
	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i + 1, j, 'R');
	    b_app.set_white_turn(false);
	    b_app.board_history.append(b);

	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i + 1, j, 'B');
	    b_app.set_white_turn(false);
	    b_app.board_history.append(b);

	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i + 1, j, 'H');
	    b_app.set_white_turn(false);
	    b_app.board_history.append(b);

	    b_app = b;
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i + 1, j, 'Q');
	    b_app.set_white_turn(false);
	    b_app.board_history.append(b);
	}
    }

};
