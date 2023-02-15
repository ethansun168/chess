#pragma once
#include <array>
#include <iostream>
#include "Piece.h"
//Representation of a Chess board

const int BOARD_SIZE = 8;

class Board {
private:
	Piece* board[BOARD_SIZE][BOARD_SIZE];
	friend std::ostream& operator<<(std::ostream& os, Board& board);
public:
	//Initialize board to the starting position
	Board();
	//helper function for the overloaded operator
	void print(std::ostream& os);
	//move white piece
	void moveWhite(Piece* piece, std::pair<int,int> end);
	//move black piece
	void moveBlack(Piece* piece, std::pair<int, int> end);
	//get the pointer to piece at location
	Piece* getPiece(std::pair<int, int>) const;
	//set the pointer to piece at location
	void setPiece(Piece* piece, std::pair<int, int> location);
	//Delete board object
	void deleteBoard();
};
//Print the current state of the board to the output stream
std::ostream& operator<<(std::ostream& os, Board& board);