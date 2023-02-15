#pragma once
#include <array>
#include <iostream>
#include "Piece.h"
//Representation of a Chess board

const int BOARD_SIZE = 8;

enum PieceMovement {
	MOVE_SUCCESS,
	PIECE_IN_WAY,
	INVALID_MOVEMENT,
};

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
	PieceMovement moveWhite(std::pair<int, int> start, std::pair<int, int> end);
	//move black piece
	PieceMovement moveBlack(std::pair<int, int> start, std::pair<int, int> end);
	//get the pointer to piece at location
	Piece* getPiece(std::pair<int, int>) const;
	//set the pointer to piece at location
	void setPiece(Piece* piece, std::pair<int, int> start, std::pair<int, int> end);
	//Delete board object
	void deleteBoard();
	// returns whether a piece exists on that tile
	bool pieceExists(std::pair<int, int>) const;
	// Checks if the pawn is currently at a starting location
	bool pawnStartLocation(bool isWhite, int startLoc);
};
//Print the current state of the board to the output stream
std::ostream& operator<<(std::ostream& os, Board& board);