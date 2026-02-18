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

bool MoveGen::is_black(char c){
    // Simple function to check if a character belongs to the opponent
    switch(c){
	case 'p':
	    return true;
	    break;
	case 'b':
	    return true;
	    break;
	case 'r':
	    return true;
	    break;
	case 'h':
	    return true;
	    break;
	case 'q':
	    return true;
	    break;
	case 'k':
	    return true;
	    break;
	default:
	    return false;
    };
};


bool MoveGen::is_white(char c){
    // Simple function to check if a character belongs to the opponent
    switch(c){
	case 'P':
	    return true;
	    break;
	case 'B':
	    return true;
	    break;
	case 'R':
	    return true;
	    break;
	case 'H':
	    return true;
	    break;
	case 'Q':
	    return true;
	    break;
	case 'K':
	    return true;
	    break;
	default:
	    return false;
    };
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

	    // Debug statement to stop program at specific iteration
	    if (i == 6 && j == 8)
		cout << "";

	    switch (b.get_index(i, j)) {
		case 'n':
		    continue;
		    break;
		case 'p':
		    continue;
		    break;
		case 'r':
		    continue;
		    break;
		case 'b':
		    continue;
		    break;
		case 'h':
		    continue;
		    break;
		case 'k':
		    continue;
		    break;
		case 'q':
		    continue;
		    break;
		case 'P':
		    pawn_move(i, j);
		    continue;
		    break;
		case 'B':
		    bishop_move(i, j);
		    continue;
		    break;
		case 'R':
		    rook_move(i, j);
		    continue;
		    break;
		case 'H':
		    knight_move(i, j);
		    continue;
		    break;
		case 'Q':
		    queen_move(i, j);
		    continue;
		    break;
		case 'K':
		    king_move(i, j);
		    continue;
		    break;
		default:
		    std::cout << "Error, board returning incorrect value!" << std::endl;
		    std::cout << b.get_index(i, j) << std::endl;
		    std::cout << "i:\t" << i << "\tj:\t" << j << std::endl;
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
    
    if (i < 1 || i > 8 || j < 1 || j > 8) {
	std::cout << "Error: pawn_move() called with invalid indices!\t";
	std::cout << "i = " << i << "\t\t j = " << j << std::endl;
	throw std::logic_error("pawn_move() called with invalid indices");
    };

    if (b.get_index(i, j) != 'P') {
	std::cout << "Error: pawn_move() called on a non-pawn piece or wrong color pawn." << std::endl;
	throw std::logic_error("pawn_move() called on non-pawn piece");
    }

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
	    left_cap == 'n' && i == 5 && b.board_history.size() > 0 &&
	    b.board_history.back().get_index(7, j - 1) == 'p' &&
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
	    right_cap == 'n' && i == 5 && b.board_history.size() > 0
	    && b.board_history.back().get_index(7, j + 1) == 'p' &&
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
    /*
     * Function to generate all moves of a bishop from
     * board location i, j and append them to the current
     * MoveGen's active Board object
    */

    // Check preconditions
    if (i < 1 || i > 8 || j < 1 || j > 8) {
	std::cout << "Error: bishop_move() called with invalid indices!\t";
	std::cout << "i = " << i << "\t\t j = " << j << std::endl;
	throw std::logic_error("bishop_move() called with invalid indices");
    };

    if (b.get_index(i, j) != 'B') {
	std::cout << "Error bishop_move() called on a non-bishop piece or wrong color bishop." << std::endl;
	throw std::logic_error("bishop_move() called on non-bishop piece");
    }

    // Initialize variables
    int x = i + 1;
    int y = j + 1;
    bool capture = false;
    Board b_app;

    // Search upper right moving diagonal
    while (true){
	// If no space left in current direction, exit while loop
	if (x < 1 || x > 8 || y < 1 || y > 8){
	    break;
	};

        char cur_space = b.get_index(x, y);

	// Cannot move here, break loop.
	if (is_white(cur_space))
	    break;

        if (is_black(cur_space))
	    capture = true;

	// Conditions hold to move the bishop
	b_app = b;
	b_app.set_value(x, y, 'B');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);


	// If capture was successful, we can go no further in this direction
	if (capture)
	    break;

	// End of iteration; append indices
	x++;
	y++;
    }

    // Search upper left diagonal
    x = i + 1;
    y = j - 1;
    capture = false;
    while (true){
	// If no space left in current direction, exit while loop
	if (x < 1 || x > 8 || y < 1 || y > 8){
	    break;
	};

        char cur_space = b.get_index(x, y);

	// Cannot move here, break loop.
	if (is_white(cur_space))
	    break;

        if (is_black(cur_space))
	    capture = true;

	// Conditions hold to move the bishop
	b_app = b;
	b_app.set_value(x, y, 'B');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);


	// If capture was successful, we can go no further in this direction
	if (capture)
	    break;

	// End of iteration; append indices
	x++;
	y--;
    }

    // Search lower left diagonal
    x = i - 1;
    y = j - 1;
    capture = false;
    while (true){
	// If no space left in current direction, exit while loop
	if (x < 1 || x > 8 || y < 1 || y > 8){
	    break;
	};

        char cur_space = b.get_index(x, y);

	// Cannot move here, break loop.
	if (is_white(cur_space))
	    break;

        if (is_black(cur_space))
	    capture = true;

	// Conditions hold to move the bishop
	b_app = b;
	b_app.set_value(x, y, 'B');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);


	// If capture was successful, we can go no further in this direction
	if (capture)
	    break;

	// End of iteration; append indices
	x--;
	y--;
    }

    // Search lower right diagonal
    x = i - 1;
    y = j + 1;
    capture = false;
    while (true){
	// If no space left in current direction, exit while loop
	if (x < 1 || x > 8 || y < 1 || y > 8){
	    break;
	};

        char cur_space = b.get_index(x, y);

	// Cannot move here, break loop.
	if (is_white(cur_space))
	    break;

        if (is_black(cur_space))
	    capture = true;

	// Conditions hold to move the bishop
	b_app = b;
	b_app.set_value(x, y, 'B');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);


	// If capture was successful, we can go no further in this direction
	if (capture)
	    break;

	// End of iteration; append indices
	x--;
	y++;
    }
    
    return;
};

void MoveGen::rook_move(int i, int j) {
    /*
    Generate moves based on the current position of a rook
    */

    // Check pre-conditions
    if (b.get_index(i, j) != 'R'){
	std::cout << "Error! rook_move called on non-rook piece!" << std::endl;
    }

    // Initialize variables
    int x = i + 1;
    int y = j + 1;
    bool blocked = false;
    Board b_app;

    // Branch 1: Move right
    while (y <= 8 && !blocked) {

	// Verify piece is not blocked
	if (is_white(b.get_index(i, y)))
	    break;
	else if (is_black(b.get_index(i, y))){
	    blocked = true;
	}

	// Space is either empty or capturable; append new board to next_moves
	b_app = b;
	b_app.set_value(i, y, 'R');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);

	// Increase iterator
	y++;
    }

    // Reset breaking variable
    blocked = false;

    // Branch 2: Move up
    while (x <= 8 && !blocked) {

	// Verify piece is not blocked
	if (is_white(b.get_index(x, j)))
	    break;
	else if (is_black(b.get_index(x, j))){
	    blocked = true;
	}

	// Space is either empty or capturable; append new board to next_moves
	b_app = b;
	b_app.set_value(x, j, 'R');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);

	// Increase iterator
	x++;
    }


    // Reset breaking variable
    blocked = false;
    x = i - 1;
    y = j - 1;

    // Branch 3: Move left
    while (y >= 1 && !blocked) {

	// Verify piece is not blocked
	if (is_white(b.get_index(i, y)))
	    break;
	else if (is_black(b.get_index(i, y))){
	    blocked = true;
	}

	// Space is either empty or capturable; append new board to next_moves
	b_app = b;
	b_app.set_value(i, y, 'R');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);

	// Increase iterator
	y--;
    }


    // Reset breaking variable
    blocked = false;

    // Branch 4: Move down
    while (x >= 1 && !blocked) {

	// Verify piece is not blocked
	if (is_white(b.get_index(x, j)))
	    break;
	else if (is_black(b.get_index(x, j))){
	    blocked = true;
	}

	// Space is either empty or capturable; append new board to next_moves
	b_app = b;
	b_app.set_value(x, j, 'R');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);

	// Increase iterator
	x--;
    }

    return;
};

void MoveGen::knight_move(int i, int j) {
    // Generate moves for a knight on the board

    // Ensure piece is correct
    if (b.get_index(i, j) != 'H'){
	std::cout << "Error! knight_move() called on a non-knight piece!" << std::endl;
	throw 0;
    }

    // Initialize variables
    int x;
    int y;
    Board b_app;

    // Move 1: 2 right, 1 up
    x = i + 1;
    y = j + 2;
    if (x <= 8 && y <= 8 && !is_white(b.get_index(x, y))) {
	b_app = b;
	b_app.set_value(x, y, 'H');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);
    }

    // Move 2: 1 right, 2 up
    x = i + 2;
    y = j + 1;
    if (x <= 8 && y <= 8 && !is_white(b.get_index(x, y))) {
	b_app = b;
	b_app.set_value(x, y, 'H');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);
    }

    // Move 3: 1 left, 2 up
    x = i + 2;
    y = j - 1;
    if (x <= 8 && y >= 1 && !is_white(b.get_index(x, y))) {
	b_app = b;
	b_app.set_value(x, y, 'H');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);
    }

    // Move 4: 2 left, 1 up
    x = i + 1;
    y = j - 2;
    if (x <= 8 && y >= 1 && !is_white(b.get_index(x, y))) {
	b_app = b;
	b_app.set_value(x, y, 'H');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);
    }

    // Move 5: 2 left, 1 down
    x = i - 1;
    y = j - 2;
    if (x >= 1 && y >= 1 && !is_white(b.get_index(x, y))) {
	b_app = b;
	b_app.set_value(x, y, 'H');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);
    }

    // Move 6: 1 left, 2 down
    x = i - 2;
    y = j - 1;
    if (x >= 1 && y >= 1 && !is_white(b.get_index(x, y))) {
	b_app = b;
	b_app.set_value(x, y, 'H');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);
    }

    // Move 7: 1 right, 2 down
    x = i - 2;
    y = j + 1;
    if (x >= 1 && y <= 8 && !is_white(b.get_index(x, y))) {
	b_app = b;
	b_app.set_value(x, y, 'H');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);
    }

    // Move 8: 2 right, 1 down
    x = i - 1;
    y = j + 2;
    if (x >= 1 && y <= 8 && !is_white(b.get_index(x, y))) {
	b_app = b;
	b_app.set_value(x, y, 'H');
	b_app.set_value(i, j, 'n');
	b_app.set_white_turn(!b_app.get_white_turn());
	b_app.board_history.push_back(b);
	b.next_moves.push_back(b_app);
    }

    return;
};

void MoveGen::queen_move(int i, int j) {
    return;
};

void MoveGen::king_move(int i, int j) {
    return;
};

