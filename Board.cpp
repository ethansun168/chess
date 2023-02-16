#include "Board.h"
using namespace std;

Board::Board() {

}

Piece Board::getPiece(Cell cell) const {
	//e5 = board[row + BOARD_SIZE + col] = board[3][4]
	return board[BOARD_SIZE - cell.rank][cell.file - 'a'];
}

void Board::setPiece(Piece piece, Cell cell) {
	board[BOARD_SIZE - cell.rank][cell.file - 'a'] = piece;
}

bool Board::isCheck(bool turn) const {

}

bool Board::isCheckMate(bool turn) const {

}

bool Board::canCastle(bool turn, Player player) const {
	if (!player.getCanCastle()) { return false; }
}

bool Board::isValidMove(bool turn, Cell start, Cell end) const {

}

void Board::move(Cell start, Cell end) {

}

void Board::fenCodeToBoardPrint(string fenCode, ostream& os) {
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

