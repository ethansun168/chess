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
	Color playerTurn;
	int halfMoves;
	int fullMoves;
	std::pair<int, int> enPassant;

	//make sure to update the king locations after a move
	std::pair<int, int> whiteKingLocation;
	std::pair<int, int> blackKingLocation;

	//helper function for fenCodeToBoardStore
	void castleModify(bool K, bool Q, bool k, bool q);
	
	//check if [color] knights can check the king in [kingLocation]
	bool knightChecks(Color color, std::pair<int, int> kingLocation) const;
	
	//check if the [color] bishop can check the king in [kingLocation]
	bool bishopChecks(Color color, std::pair<int, int> kingLocation) const;
	
	//check if the [color] pawn can check the king in [kingLocation]
	bool pawnChecks(Color color, std::pair<int, int> kingLocation) const;

	//check if the [color] rook can check the king in [kingLocation]
	bool rookChecks(Color color, std::pair<int, int> kingLocation) const;

	//check if the [color] queen can check the king in [kingLocation]
	bool queenChecks(Color color, std::pair<int, int> kingLocation) const;

	//Horizontal checks
	//increment is the number of rowAdd or colAdd from [kingLocation]
	//Piece is the piece that is checking the king horizontally
	bool horizontalChecks(Piece piece, std::pair<int, int> kingLocation) const;

	//diag checks
	//increment is the number of rowAdd or colAdd from [kingLocation]
	//Piece is the piece that is checking the king diagonally
	bool diagonalChecks(Piece piece, std::pair<int, int> kingLocation) const;

	//Helper function to reduce code
	//Check if the piece on kingLocation + rowAdd + colAdd is [color] and [type]
	//IMPORTANT: colAdd is flipped because of the board representation
	bool kingCheckHelper(std::pair<int, int> kingLocation, int rowAdd, int colAdd, Piece piece) const;

	//helper function that checks if [piece] is [color] king and [color] is castling king side
	bool isCastleKing(Piece piece, Color color, std::pair<int, int> start, std::pair<int, int> end) const;

	//helper function that checks if [piece] is [color] king and [color] is castling queen side
	bool isCastleQueen(Piece piece, Color color, std::pair<int, int> start, std::pair<int, int> end) const;

	//set the position for [color] to castled position on king side
	//must pass isValidMove() and isCastleKing()
	void setCastleKing(Color color);

	//set the position for [color] to castled position on queen side
	//must pass isValidMove() and isCastleKing()
	void setCastleQueen(Color color);

public:
	//Initialize to the starting position
	Board();

	//use a FEN string to initialize the board 
	// https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
	// https://www.chess.com/terms/fen-chess
	//input string must be a valid fen string
	Board(std::string fen);

	//get the piece at location
	//requires a valid location
	Piece getPiece(std::pair<int, int> location) const;

	//set the piece at location
	//requires a valid piece and a valid location
	void setPiece(Piece piece, std::pair<int, int> location);

	//check if the location is valid
	//0 <= first <= 8, 0 <= second <= 8
	bool isValidLocation(std::pair<int, int> location) const;
	
	//checks for check
	//is the [playerTurn] king in check?
	bool isCheck(Color playerTurn) const;
	
	//checks for checkmate
	bool isCheckMate(Color playerTurn) const;

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
