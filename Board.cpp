#include "Board.h"
using namespace std;

Board::Board() {

}

Piece Board::getPiece(Cell cell) const {
	//e5 = board[row + BOARD_SIZE + col] = board[3][4]
	int row = BOARD_SIZE - cell.rank;
	int col = cell.file - 'a';
	return board[row + BOARD_SIZE + col];
}