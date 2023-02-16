#include "Board.h"
using namespace std;

Board::Board() {

}

void Board::fenCodeToBoard(string fenCode, ostream& os) {
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

Piece Board::getPiece(Cell cell) const {
	//e5 = board[row + BOARD_SIZE + col] = board[3][4]
	int row = BOARD_SIZE - cell.rank;
	int col = cell.file - 'a';
	return board[row + BOARD_SIZE + col];
}