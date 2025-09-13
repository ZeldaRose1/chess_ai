make: chess.cpp board.h
	g++ chess.cpp board.h -o chess

test: test_board.cpp board.h
	g++ test_board.cpp board.h -o test
	./test

clean:
	rm chess test
