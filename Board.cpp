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
		return true;
	}
	return false;
}

// TODO redo
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
			//update the blanks
			if (board[row][col].isEmpty()) {
				blank++;
			}
			else {
				//add to row string
				if (blank != 0) {
					fenCode += to_string(blank);
					blank = 0;
				}
				fenCode += pieceToChar(board[row][col]);
			}
		}
		//if the last one in row is empty
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

// TODO Fix this function
bool validFenCode(string inputFenString) {
	regex value("([rnbqkpRNBQKP1-8]+\/){7}([rnbqkpRNBQKP1-8]+)\s[wb]\s([K]?[Q]?[k]?[q]?|-)\s([a-h][1-8]|-)\s[0-50]\s(\d+)");
	return regex_match(inputFenString, value);
}

bool validFenChar(char fenChar) {
	regex value("[PBNRQK]", regex_constants::icase);
	return regex_search(&fenChar, value);
}