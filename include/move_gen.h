#pragma once

#include "board.h"

/*
This class will be used to create any future moves
*/

class MoveGen{
    public:
	Board get_board();
	void set_board(Board);
	void generate_moves();
    private:
	Board b;
	// Logic for moving individual pieces. All will use i, j to specify piece location 
	void pawn_move(int, int) 
	void knight_move(int, int)
	void bishop_move(int, int)
	void rook_move(int, int)
	void queen_move(int, int)
	void king_move(int, int)
}
