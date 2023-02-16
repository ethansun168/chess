#pragma once
#include "Piece.h"
#include <vector>

int const BOARD_SIZE = 8;

struct Cell {
	char file;
	int rank;
};

//Representation of Board
class Board {
private:
	std::vector<Piece> board;
public:
	//Initialize to the starting position
	Board();

	//use a FEN string to initialize the board https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
	Board(std::string fen);

	//get the piece at cell
	Piece getPiece(Cell cell) const;

	//set the piece at cell
	void setPiece(Piece piece, Cell cell);
	
	//checks for check
	//turn = true check if white is in check, turn = false check if black is in check
	bool isCheck(bool turn) const;
	
	//checks for checkmate
	//turn = true check if white is in checkmate, turn = false check if black is in checkmate
	bool isCheckMate(bool turn) const;

	//checks for castling rights
	//turn = true check if white can castle, turn = false check if black can castle
	bool canCastle(bool turn) const;

	//check if the move for the piece at start is valid
	//turn = true is white's move, turn = false is black's move
	//needs to account for piece obstruction, pins, in checks, can castle
	bool isValidMove(bool turn, Cell start, Cell end) const;

	//move piece after it passes isValidMove
	void move(Cell start, Cell end);

	// Translate a line of FEN code into a board position
	void fenCodeToBoard(std::string fenCode, ostream& os);
};
//print the board to os
std::ostream& operator<< (std::ostream& os, Board& board);