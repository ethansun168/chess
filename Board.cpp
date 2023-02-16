#include "Board.h"
using namespace std;

Board::Board() {
	fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Piece Board::getPiece(Cell cell) const {
	//e5 = board[row + BOARD_SIZE + col] = board[3][4]
	return board[BOARD_SIZE - cell.rank][cell.file - 'a'];
}

void Board::setPiece(Piece piece, Cell cell) {
	board[BOARD_SIZE - cell.rank][cell.file - 'a'] = piece;
}

bool Board::isCheck(bool turn) const {
	return false;
}

bool Board::isCheckMate(bool turn) const {
	return false;
}

bool Board::canCastle(bool turn, Player player) const {
	/*if (!player.getCanCastle()) { 
		return false; 
	}*/
	return false;
}

bool Board::isValidMove(bool turn, Cell start, Cell end) const {
	return false;
}

void Board::move(Cell start, Cell end) {

}

void Board::fenCodeToBoardPrint(string fenCode, ostream& os) const {
	int rowNumber = 0, charNumber = 0, stringIndex = 0;
	while (fenCode[stringIndex] != ' ') {
		int numberOfBlanks = fenCode[stringIndex] - '0';
		if (fenCode[stringIndex] == '/') {
			os << "\n";
			charNumber = 0;
			rowNumber++;
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