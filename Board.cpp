#include "Board.h"
#include <cassert>
using namespace std;

Board::Board() {


	//black back row
	board[0][0] = new Rook(BLACK, { 0,0 });
	board[0][1] = new Knight(BLACK, { 0,1 });
	board[0][2] = new Bishop(BLACK, { 0,2 });
	board[0][3] = new Queen(BLACK, { 0,3 });
	board[0][4] = new King(BLACK, { 0,4 });
	board[0][5] = new Bishop(BLACK, { 0,5 });
	board[0][6] = new Knight(BLACK, { 0,6 });
	board[0][7] = new Rook(BLACK, { 0,7 });

	for (int r = 1; r < BOARD_SIZE - 1; r++) {
		for (int c = 0; c < BOARD_SIZE; c++) {
			if (r == 1) {
				//black pawns
				board[r][c] = new Pawn(BLACK, { r,c });
			}
			else if (r > 1 && r < 6) {
				//empty
				board[r][c] = new Piece();
			}
			else if (r == 6) {
				//white pawns
				board[r][c] = new Pawn(WHITE, { r,c });
			}
		}
	}

	//white back row
	board[7][0] = new Rook(WHITE, { 7,0 });
	board[7][1] = new Knight(WHITE, { 7,1 });
	board[7][2] = new Bishop(WHITE, { 7,2 });
	board[7][3] = new Queen(WHITE, { 7,3 });
	board[7][4] = new King(WHITE, { 7,4 });
	board[7][5] = new Bishop(WHITE, { 7,5 });
	board[7][6] = new Knight(WHITE, { 7,6 });
	board[7][7] = new Rook(WHITE, { 7,7 });
}

void Board::print(ostream& os) {
	os << "   _______________\n";
	for (int r = 0; r < BOARD_SIZE; r++) {
		os << BOARD_SIZE - r << " ";
		for (int c = 0; c < BOARD_SIZE; c++) {
			//fix
			os << "|" << *board[r][c];
			if (c == BOARD_SIZE - 1) { 
				os << "|"; 
			}
		}
		os << endl;
	}
	os << "  -----------------\n";
	os << "   a b c d e f g h\n";
}

void Board::deleteBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			delete board[i][j];
		}
	}
}

void Board::move(Piece* piece, pair<int,int> end) {
	switch (piece->getType()) {
	case PAWN:

		break;
	}
}

Piece* Board::getPiece(pair<int,int> location) const {
	return board[location.first][location.second];
}

void Board::setPiece(Piece* piece, pair<int, int> location) {
	board[location.first][location.second] = piece;
}

ostream& operator<<(ostream& os, Board& board) {
	board.print(os);
	return os;
}