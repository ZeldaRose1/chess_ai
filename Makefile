make: chess.cpp board.h
	g++ chess.cpp board.h -o chess

clean:
	rm chess
