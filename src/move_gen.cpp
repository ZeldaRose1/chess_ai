#include "move_gen.h"

/*
Logic to generate moves given a game state.
*/


MoveGen::MoveGen(){
};

Board& MoveGen::get_board() {
    return b;
};

void MoveGen::set_board(Board input_board) {
    b = input_board;
};

void MoveGen::generate_moves() {
    /*
	Function to generate all possible moves from a given board state.

	This will swap the pieces on the board to simplify the logic
	behind the individual move generators.

	That is, if it's black's turn, it will mirror the board and change
	the colors of the board before calling the minor move_gen functions.
    */
    if (b.next_moves.size() > 0) {
	b.next_moves.clear();
    };

    // Handle board color.
    if (!b.get_white_turn()){
	b.change_color();
    }

    // Function will loop through all squares and call the specific piece_move function
    for (int i = 1; i <= 8; i++) {
	for (int j = 1; j <= 8; j++) {
	    switch (b.get_index(i, j)) {
		case 'n':
		    continue;
		case 'P':
		    pawn_move(i, j);
		    continue;
		case 'B':
		    bishop_move(i, j);
		    continue;
		case 'R':
		    rook_move(i, j);
		    continue;
		case 'H':
		    knight_move(i, j);
		    continue;
		case 'Q':
		    queen_move(i, j);
		    continue;
		case 'K':
		    king_move(i, j);
		    continue;
		default:
		    continue;
	    }
	}
    }

    // Swap colors back to the original board state
    if (!b.get_white_turn()){
	b.change_color();
	// Note unsigned long int is used to avoid warnings of unmatched int types
	// It does not change the outcome of the counting index.
	for (unsigned long int i = 0; i < b.next_moves.size(); i++)
	    b.next_moves[i].change_color();
    }

    // All moves have been generated. Close function
    return;
};

// Begin move functions
void MoveGen::pawn_move(int i, int j){
    // Function takes coordinates of square and generates all moves for a pawn
    // based on current board state.
    
    /*       Ensure pre-conditions      */

    if (b.get_index(i, j) != 'P') {
	std::cout << "Error: pawn_move() called on a non-pawn piece or wrong color pawn." << std::endl;
	throw std::logic_error("pawn_move() called on non-pawn piece");
    }

    if (i < 1 || i > 8 || j < 1 || j > 8) {
	std::cout << "Error: pawn_move() called with invalid indices!\t";
	std::cout << "i = " << i << "\t\t j = " << j << std::endl;
	throw std::logic_error("pawn_move() called with invalid indices");
    };

    // Declare board variable used for appends.
    Board b_app;

    /*      Generate pawn moves      */

    // Double square move on initial pawn space
    if (i == 2 && b.get_index(3, j) == 'n' && b.get_index(4, j) == 'n') {
        b_app = b;
        b_app.set_value(i, j, 'n');
        b_app.set_value(4, j, 'P');
        b_app.set_white_turn(!b_app.get_white_turn());
        b_app.board_history.push_back(b);
        b.next_moves.push_back(b_app);
    }

    // Default pawn move
    if (i < 7 && b.get_index(i + 1, j) == 'n') { // basic move cannot enter last row.
	b_app = b;
	b_app.set_value(i, j, 'n');
	b_app.set_value(i + 1, j, 'P');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);
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
	    b_app.set_white_turn(!b_app.get_white_turn());
	    b_app.board_history.push_back(b);
	    b.next_moves.push_back(b_app);
	} else if ( // En Passant rule
	    left_cap == 'n' && i == 5 && b.board_history.back().get_index(7, j - 1) == 'p' &&
	    b.get_index(5, j - 1) == 'p' && b.get_index(7, j - 1) == 'n'
	) {
	    b_app = b;
	    b_app.set_value(i + 1, j - 1, 'P'); // Move white pawn up and to the left
	    b_app.set_value(i, j, 'n'); // Delete pawn from starting position
	    b_app.set_value(i, j - 1, 'n'); // Remove black pawn that did a double step
	    b_app.set_white_turn(!b_app.get_white_turn());
	    b_app.board_history.push_back(b);
	    b.next_moves.push_back(b_app);
	}
    }

    // Standard capture rule (right)
    if (j < 8 && i < 8) { 
	char right_cap = b.get_index(i + 1, j + 1);
	if ( // Check if piece one forward and left is enemy piece
	    right_cap == 'p' || right_cap == 'r' || right_cap == 'b' || 
	    right_cap == 'h' || right_cap == 'q' || right_cap == 'k'
	) { // Capture enemy piece
	    b_app = b;
	    b_app.set_value(i + 1, j + 1, 'P');
	    b_app.set_value(i, j, 'n');
	    b_app.set_white_turn(!b_app.get_white_turn());
	    b_app.board_history.push_back(b);
	    b.next_moves.push_back(b_app);
	} else if ( // En Passant rule
	    right_cap == 'n' && i == 5 && b.board_history.back().get_index(7, j + 1) == 'p' &&
	    b.get_index(5, j + 1) == 'p' && b.get_index(7, j + 1) == 'n'
	) {
	    b_app = b;
	    b_app.set_value(i + 1, j + 1, 'P');
	    b_app.set_value(i, j, 'n');
	    b_app.set_value(i, j + 1, 'n');
	    b_app.set_white_turn(!b_app.get_white_turn());
	    b_app.board_history.push_back(b);
	    b.next_moves.push_back(b_app);
	}
    }

	// Promotion rule
    if (i == 7 && b.get_index(8, j) == 'n') {
	b_app = b;
	b_app.set_value(i, j, 'n');
	b_app.set_value(i + 1, j, 'R');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);

	b_app = b;
	b_app.set_value(i, j, 'n');
	b_app.set_value(i + 1, j, 'B');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);

	b_app = b;
	b_app.set_value(i, j, 'n');
	b_app.set_value(i + 1, j, 'H');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);

	b_app = b;
	b_app.set_value(i, j, 'n');
	b_app.set_value(i + 1, j, 'Q');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
    }
};

void MoveGen::bishop_move(int i, int j) {
    return;
};

void MoveGen::rook_move(int i, int j) {
    return;
};

void MoveGen::knight_move(int i, int j) {
    return;
};

void MoveGen::queen_move(int i, int j) {
    return;
};

void MoveGen::king_move(int i, int j) {
    return;
};

