#pragma once
#include "Piece.h"
#include <vector>
class Board {
private:
	std::vector<Piece> board;
public:
	//Initialize to the starting position
	Board();
	//use a FEN string to initialize the board https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
	Board(std::string fen);
	bool isValidMove(Piece piece, )
};
//print the board to os
std::ostream& operator<< (std::ostream& os, Board& board);