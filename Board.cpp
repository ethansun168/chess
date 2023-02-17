#include "Board.h"
#include <sstream>
using namespace std;

Board::Board() :
	whiteCanCastleKingSide(true),
	whiteCanCastleQueenSide(true),
	blackCanCastleKingSide(true),
	blackCanCastleQueenSide(true),
	playerTurn(WHITE)
{
	fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}


Board::Board(string fen) :
	whiteCanCastleKingSide(true),
	whiteCanCastleQueenSide(true),
	blackCanCastleKingSide(true),
	blackCanCastleQueenSide(true),
	playerTurn(WHITE) 
{
	assert(validFenCode(fen));
	fenCodeToBoardStore(fen);
}

Piece Board::getPiece(Cell cell) const {
	assert(validCell(cell));
	//e5 = board[row + BOARD_SIZE + col] = board[3][4]
	return board[BOARD_SIZE - cell.rank][cell.file - 'a'];
}

void Board::setPiece(Piece piece, Cell cell) {
	assert(validCell(cell));
	board[BOARD_SIZE - cell.rank][cell.file - 'a'] = piece;
}

bool Board::isCheck(Color playerTurn) const {
	return false;
}

bool Board::isCheckMate(Color playerTurn) const {
	return false;
}

// TODO: FIX LATER
bool Board::canCastle(Color playerTurn) const {
	if (playerTurn == WHITE) {
		return (whiteCanCastleKingSide) || (whiteCanCastleQueenSide);
	}
	else {
		return (blackCanCastleKingSide || blackCanCastleQueenSide);
	}
}

bool Board::isValidMove(Color playerTurn, Cell start, Cell end) const {
	assert(validCell(start) && validCell(end));
	return false;
}

bool Board::move(Cell start, Cell end) {
	assert(validCell(start) && validCell(end));
	if (isValidMove(playerTurn, start, end)) {
		// Gets the piece at start, and sets that piece to end location
		setPiece(getPiece(start), end);
		Piece piece;
		// this is really bad code
		setPiece(piece, end);
	}
}

void Board::fenCodeToBoardPrint(string fenCode, ostream& os) const {
	int rowNumber = 0, charNumber = 0, stringIndex = 0;
	os << "   _________________\n" << BOARD_SIZE << " | ";
	while (fenCode[stringIndex] != ' ') {
		int numberOfBlanks = fenCode[stringIndex] - '0';
		if (fenCode[stringIndex] == '/') {
			rowNumber++;
			charNumber = 0;
			os << "|\n" << BOARD_SIZE - rowNumber << " | ";
		}
		else if (numberOfBlanks > 0 && numberOfBlanks < 9) {
			for (int i = 0; i < numberOfBlanks; ++i) {
				os << ". ";
			}
			charNumber += numberOfBlanks;
		} else {
			os << fenCode[stringIndex] << " ";
			charNumber++;
		}
		stringIndex++;
	}
	os << "|\n  |_________________|\n    ";
	for (char ch = 'a'; ch <= 'h'; ch++) {
		os << ch << " ";
	}
}

void Board::fenCodeToBoardStore(string fenCode) {
	int rowNumber = 0, charNumber = 0, stringIndex = 0;
	while (fenCode[stringIndex] != ' ') {
		int numberOfBlanks = fenCode[stringIndex] - '0';
		if (fenCode[stringIndex] == '/') {
			charNumber = 0;
			rowNumber++;
		}
		else if (numberOfBlanks > 0 && numberOfBlanks < 9) {
			for (int i = 0; i < numberOfBlanks; ++i) {
				Piece piece;
				board[rowNumber][charNumber] = piece;
				charNumber++;
			}
		}
		else {
			board[rowNumber][charNumber] = charToPiece(fenCode[stringIndex]);
			charNumber++;
		}
		stringIndex++;
	}
}

string Board::generateFenCode() const {
	//may want to add the other parts of the fen code later
	string fenCode;
	for (int row = 0; row < BOARD_SIZE; row++) {
		int blank = 0;
		for (int col = 0; col < BOARD_SIZE; col++) {
			if (board[row][col].isEmpty()) {
				blank++;
			}
			else {
				if (blank != 0) {
					fenCode += to_string(blank);
					blank = 0;
				}
				fenCode += pieceToChar(board[row][col]);
			}
		}
		//if the last one is empty
		if (board[row][BOARD_SIZE - 1].isEmpty()) {
			fenCode += to_string(blank);
		}
		if (row != BOARD_SIZE - 1) {
			fenCode += "/";
		}
	}
	fenCode += " ";
	return fenCode;
}

ostream& operator<< (ostream& os, const Board& board) {
	board.fenCodeToBoardPrint(board.generateFenCode(), os);
	return os;
}

bool validCell(Cell cell) {
	return 1 <= cell.rank && 8 >= cell.rank && 'a' <= cell.file && 'h' >= cell.file;
}

bool validFenCode(string fen) {
	
	//check if it ends with a space
	if (fen[fen.length() - 1] != ' ') {
		return false;
	}
	
	stringstream ss;
	ss << fen;
	char in;
	int numSlash = 0;
	int rowNumPieces = 0;
	while (ss >> in) {
		if (in == '/') {
			numSlash++;
			//check if rowNumPieces == 8
			if (rowNumPieces != 8) {
				return false;
			}
			rowNumPieces = 0;
		}
		else if (validFenChar(in)) {
			rowNumPieces++;
		}
		else if(in <= '8' || in >= '1') {
			rowNumPieces += (int)(in - '0');
		}
		else {
			return false;
		}
	}
	//check for slashes
	if (numSlash != 7) {
		return false;
	}
	
	return true;
	
}

bool validFenChar(char ch) {
	//abbreviations[1] to abbreviations[6]
	for (int i = PAWN; i <= KING; i++) {
		if (ch == abbreviations[i] || ch == (char)tolower(abbreviations[i])) {
			return true;
		}
	}
	return false;
}