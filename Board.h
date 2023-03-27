#pragma once
#include <vector>
#include "Piece.h"
#include "Player.h"

#define BOARD_SIZE 8

//enum Move_Type {
//	PAWN_MOVE,
//	ROOK_MOVE,
//	KNIGHT_MOVE,
//	BISHOP_MOVE,
//	QUEEN_MOVE,
//	KING_MOVE,
//	CASTLE_KING_SIDE,
//	CASTLE_QUEEN_SIDE
//};

enum Move_Return {
	MOVE_SUCCESSFUL,
	MOVE_CASTLE_KING_SUCCESSFUL,
	MOVE_CASTLE_QUEEN_SUCCESSFUL,
	MOVE_INVALID,
	MOVE_OBSTRUCTION,
	MOVE_CASTLE_FAILURE,
	PIECE_PINNED,
	KING_CHECKED
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
	int halfMoves;
	int fullMoves;
	std::pair<int, int> enPassant;
	std::vector<std::string> undoFen;

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
	//requires kingLocation to be a valid location
	//increment is the number of rowAdd or colAdd from [kingLocation]
	//Piece is the piece that is checking the king horizontally
	bool horizontalChecks(Piece piece, std::pair<int, int> kingLocation) const;

	//diag checks
	//requires kingLocation to be a valid location
	//increment is the number of rowAdd or colAdd from [kingLocation]
	//Piece is the piece that is checking the king diagonally
	bool diagonalChecks(Piece piece, std::pair<int, int> kingLocation) const;

	//Helper function to reduce code
	//Check if the piece on kingLocation + rowAdd + colAdd is [color] and [type]
	//IMPORTANT: colAdd is flipped because of the board representation
	bool kingCheckHelper(std::pair<int, int> kingLocation, int rowAdd, int colAdd, Piece piece) const;

	//helper function that checks if [color] is castling king side
	//requires the piece at [start] to be a KING
	bool attemptCastleKing(std::pair<int, int> start, std::pair<int, int> end) const;

	//helper function that checks if [color] is castling queen side
	//requires the piece at [start] to be a KING
	bool attemptCastleQueen(std::pair<int, int> start, std::pair<int, int> end) const;

	//set the position for [color] to castled position on king side
	//modifies king location and corresponding side's rook location
	//modifies corresponding castle booleans through movePiece()
	void setCastleKing();

	//set the position for [color] to castled position on queen side
	//modifies king location and corresponding side's rook location
	//modifies corresponding castle booleans through movePiece()
	void setCastleQueen();

	/*
	check if the move for the piece at start is valid
	the following functions require:
		start and end are valid cells
		start != end (might be a redundant requires)
		start is a [playerTurn] piece
		end is empty or a (not [playerTurn]) piece
		[start] is the same as the piece of the move it is checking
		for example, [start] for validPawnMove needs to be a Pawn
	*/
	Move_Return validPawnMove(std::pair<int, int> start, std::pair<int, int> end) const;
	Move_Return validRookMove(std::pair<int, int> start, std::pair<int, int> end) const;
	Move_Return validKnightMove(std::pair<int, int> start, std::pair<int, int> end) const;
	Move_Return validBishopMove(std::pair<int, int> start, std::pair<int, int> end) const;
	Move_Return validQueenMove(std::pair<int, int> start, std::pair<int, int> end) const;
	Move_Return validKingMove(std::pair<int, int> start, std::pair<int, int> end) const;
	
	/*
	Extra requires:
		start and end must be valid king castling locations
		e.g. {7,4} and {7,6} for white king
	These functions only check if [playerTurn] is able to castle on the specific side
	*/
	Move_Return validCastleKingSide(std::pair<int, int> start, std::pair<int, int> end) const;
	Move_Return validCastleQueenSide(std::pair<int, int> start, std::pair<int, int> end) const;

public:
	//Initialize to the starting position
	Board();
	
	/*
	use a FEN string to initialize the board 
	 https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
	 https://www.chess.com/terms/fen-chess
	input string must be a valid fen string
	*/
	Board(std::string fen);

	// Gets the current color of the player
	Color getColor() const;

	//get the piece at location
	//requires a valid location
	Piece getPiece(std::pair<int, int> location) const;

	//set the piece at location
	//requires a valid piece and a valid location
	//never use this -- use movePiece() instead, it has more checks
	void setPiece(Piece piece, std::pair<int, int> location);
	
	/*
	Moves a piece from [start] to [end], deals with setting all the correct squares to
	their respective values
	requires:
		start and end pass isValidMove
	modifies:
		kingLocation values if the king is moved
		castle booleans if the king or rook is moved
		undoFen stores the board's state before it is modified
	*/
	void movePiece(std::pair<int, int> start, std::pair<int, int> end);

	//checks for check
	//is the [playerTurn] king in check?
	bool isCheck() const;
	
	//checks if [playerTurn] is in checkmate
	bool isCheckMate() const;
	/*
	check if the move for the piece at start is valid
	requires none
	needs to account for piece obstruction, pins, in checks, can castle
	does all the error checking:	
		start != end
		start and end must be valid
		start piece must have color [playerTurn]
		start must not be empty
		end color must not be the same as [playerTurn]
	*/
	Move_Return isValidMove(std::pair<int, int> start, std::pair<int, int> end) const;

	//move piece after it passes isValidMove
	//requires none
	//returns Error_Return from isValidMove for I/O to parse
	Move_Return move(std::pair<int, int> start, std::pair<int, int> end);

	// Translate a line of FEN code into a board position
	void fenCodeToBoardPrint(std::string fenCode, std::ostream& os) const;
	
	//Store the pieces to board based on fen code
	void fenCodeToBoardStore(std::string fenCode);

	//generates FEN code based on the board
	std::string generateFenCode() const;

	//undoes the move
	//returns if undo was successful or not
	bool undo();
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

//check if the location is valid
//0 <= first <= 8, 0 <= second <= 8
bool validLocation(std::pair<int, int> location);

/*
convert file and rank to location on board
requires:
	'a' <= file <= 'h'
	1 <= rank <= 8
board[0][0] is a8, board[7][7] is h1
*/
std::pair<int, int> convert(char file, int rank);