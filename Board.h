#pragma once
#include <vector>
#include "Piece.h"
#include "Player.h"

int const BOARD_SIZE = 8;

struct Cell {
	char file;
	int rank;
};

//Representation of Board
class Board {
private:
	Piece board[BOARD_SIZE][BOARD_SIZE];
	bool whiteCanCastleKingSide;
	bool whiteCanCastleQueenSide;
	bool blackCanCastleKingSide;
	bool blackCanCastleQueenSide;
	Color playerTurn;
	Cell enPassant;
	int halfMoves;
	int fullMoves;

	//helper function for fenCodeToBoardStore
	void castleModify(bool K, bool Q, bool k, bool q);
public:
	//Initialize to the starting position
	Board();

	//use a FEN string to initialize the board 
	// https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
	// https://www.chess.com/terms/fen-chess
	//input string must be a valid fen string
	Board(std::string fen);

	//get the piece at cell
	//requires a valid cell
	Piece getPiece(Cell cell) const;

	//set the piece at cell
	//requires a valid piece and a valid cell
	void setPiece(Piece piece, Cell cell);
	
	//checks for check
	bool isCheck(Color playerTurn) const;
	
	//checks for checkmate
	bool isCheckMate(Color playerTurn) const;

	//checks for castling rights
	bool canCastle(Color playerTurn) const;

	//check if the move for the piece at start is valid
	//requires start and end to be valid cells
	//needs to account for piece obstruction, pins, in checks, can castle
	bool isValidMove(Color playerTurn, Cell start, Cell end) const;

	//move piece after it passes isValidMove
	//requires start and end to be valid cells
	//returns true if move sucessfully executes
	//returns false if it does not
	bool move(Cell start, Cell end);

	// Translate a line of FEN code into a board position
	void fenCodeToBoardPrint(std::string fenCode, std::ostream& os) const;
	
	//Store the pieces to board based on fen code
	void fenCodeToBoardStore(std::string fenCode);

	//generates FEN code based on the board
	std::string generateFenCode() const;
};



//print the board to os
std::ostream& operator<< (std::ostream& os, const Board& board);

//checks if the cell is a valid cell
//valid cell means 1 <= rank <= 8 and a <= file <= h
bool validCell(Cell cell);

//checks if the string is a valid fen string
//is valid if characters are only r n b q k p P R N B Q K, 1-8, /
//must end with a space
//must have 7 /'s
//characters between each / must add up to 8
bool validFenCode(std::string fen);

//helper for validFenCode
bool validFenChar(char ch);