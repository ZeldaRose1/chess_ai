#include <cassert>
#include <cmath>
#include <iostream>
#include <climits>
#include "board.h"

using namespace std;

int test_subboard_select_operator() {
	SubBoard sb = SubBoard();

	// Test 1: single piece in slot 0
	sb.setBoard(5);
	assert(sb[0] == 5);

	// Test 2: Piece in slot 0 and piece in slot 1
	sb.setBoard(5 + (13 * 5));
	assert(sb[0] == 5);
	assert(sb[1] == 5);

	// Test 3: Piece in slot 1 and none in slot 0
	sb.setBoard(pow(13, 1) * 5);
	assert(sb[0] == 0);
	assert(sb[1] == 5);

	// Test 4: All pieces return 1
	unsigned long long int temp = 0;
	for (int i = 0; i < 16; i++) {
		temp += pow(13, i);
	};
	sb.setBoard(temp);
	
	for (int i = 0; i < 16; i++) {
		assert(sb[i] == 1);
	};
	
	// Test 5: All pieces return 12
	sb.setBoard(0);
	temp = 0;
	for (int i = 0; i < 16; i++) {
		sb.setBoard(sb.getBoard() + (pow(13, i) * 12));
		temp += (pow(13, i) * 12);
//		cout << "temp value: " << temp << endl;
		cout << "Board Value: " << sb.getBoard() << " at " << i << endl;
		assert (sb[i] == 12);
	};
	sb.setBoard(temp);

	for (int i = 0; i < 16; i++) {
		cout << "Value at " << i << " is " << sb[i] << endl;
		assert(sb[i] == 12);
	};

	return 1;
}

int main() {

	test_subboard_select_operator();

	cout << "All tests finished successfully" << endl;
}
