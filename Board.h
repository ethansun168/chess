#pragma once
#include <vector>
#include <iostream>
#include "Piece.h"
//Representation of a Chess board

const int BOARD_SIZE = 8;

class Board {
private:
	std::vector<std::vector<Piece>> board;
	friend std::ostream& operator<<(std::ostream& os, Board& board);
public:
	//Initialize board to the starting position
	Board();

};
//Print the current state of the board to the output stream
std::ostream& operator<<(std::ostream& os, Board& board);