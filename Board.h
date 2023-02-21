#pragma once
#include <vector>
#include "Piece.h"
#include "Player.h"

#define BOARD_SIZE 8

//Representation of Board
class Board {
private:
	Piece board[BOARD_SIZE][BOARD_SIZE];
	bool whiteCanCastleKingSide;
	bool whiteCanCastleQueenSide;
	bool blackCanCastleKingSide;
	bool blackCanCastleQueenSide;
	Color playerTurn;;
	int halfMoves;
	int fullMoves;
	std::pair<int, int> whiteKingLocation;
	std::pair<int, int> blackKingLocation;

	//helper function for fenCodeToBoardStore
	void castleModify(bool K, bool Q, bool k, bool q);
	//check if [color] knights can check the king in [kingCell]
	bool knightChecks(Color currentPlayer, std::pair<int, int> kingLocation) const;
	// Helper function to reduce code, passes in horse arguments
	bool kingCheckHelper(std::pair<int, int> kingLocation, int rowAdd, int colAdd, Color color, Type pieceType) const;
	//check if the [color] bishop can check the king in [kingCell]
	bool bishopChecks(Color currentPlayer, std::pair<int, int> kingLocation) const;
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
	Piece getPiece(std::pair<int, int> location) const;

	//set the piece at cell
	//requires a valid piece and a valid cell
	void setPiece(Piece piece, std::pair<int, int> location);

	bool isValidLocation(std::pair<int, int> location) const;
	
	//checks for check
	bool isCheck(Color playerTurn) const;
	
	//checks for checkmate
	bool isCheckMate(Color playerTurn) const;

	//checks for castling rights
	bool canCastle(Color playerTurn) const;

	//check if the move for the piece at start is valid
	//requires start and end to be valid cells
	//needs to account for piece obstruction, pins, in checks, can castle
	bool isValidMove(Color playerTurn, std::pair<int, int> start, std::pair<int, int> end) const;

	//move piece after it passes isValidMove
	//requires start and end to be valid cells
	//returns true if move sucessfully executes
	//returns false if it does not
	bool move(std::pair<int, int> start, std::pair<int, int> end);

	// Translate a line of FEN code into a board position
	void fenCodeToBoardPrint(std::string fenCode, std::ostream& os) const;
	
	//Store the pieces to board based on fen code
	void fenCodeToBoardStore(std::string fenCode);

	//generates FEN code based on the board
	std::string generateFenCode() const;
};

//print the board to os
std::ostream& operator<< (std::ostream& os, const Board& board);

//checks if the string is a valid fen string
//is valid if characters are only r n b q k p P R N B Q K, 1-8, /
//must end with a space
//must have 7 /'s
//characters between each / must add up to 8
bool validFenCode(std::string fen);

//helper for validFenCode
bool validFenChar(char ch);
