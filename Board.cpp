#include "Board.h"
#include <cassert>
using namespace std;

Board::Board() {
	Pawn wPawn(WHITE);
	Pawn bPawn(BLACK);
	Bishop wBishop(WHITE);
	Bishop bBishop(BLACK);
	Knight wKnight(WHITE);
	Knight bKnight(BLACK);
	Rook wRook(WHITE);
	Rook bRook(BLACK);
	Queen wQueen(WHITE);
	Queen bQueen(BLACK);
	King wKing(WHITE);
	King bKing(BLACK);
	Piece piece;

	//black back row
	*at(0, 0) = bRook;
	*at(0, 1) = bKnight;
	*at(0, 2) = bBishop;
	*at(0, 3) = bQueen;
	*at(0, 4) = bKing;
	*at(0, 5) = bBishop;
	*at(0, 6) = bKnight;
	*at(0, 7) = bRook;
	/*board[0][0] = bRook;
	board[0][1] = bKnight;
	board[0][2] = bBishop;
	board[0][3] = bQueen;
	board[0][4] = bKing;
	board[0][5] = bBishop;
	board[0][6] = bKnight;
	board[0][7] = bRook;*/

	for (int r = 1; r < BOARD_SIZE - 1; r++) {
		for (int c = 0; c < BOARD_SIZE; c++) {
			if (r == 1) {
				//black pawns
				*at(r, c) = bPawn;
				//board[r][c] = bPawn;
			}
			else if (r > 1 && r < 6) {
				//empty
				*at(r, c) = piece;
				//board[r][c] = piece;
			}
			else if (r == 6) {
				//white pawns
				*at(r, c) = wPawn;
				//board[r][c] = wPawn;
			}
		}
	}

	//white back row
	*at(7, 0) = wRook;
	*at(7, 1) = wKnight;
	*at(7, 2) = wBishop;
	*at(7, 3) = wQueen;
	*at(7, 4) = wKing;
	*at(7, 5) = wBishop;
	*at(7, 6) = wKnight;
	*at(7, 7) = wRook;
	/*board[7][0] = wRook;
	board[7][1] = wKnight;
	board[7][2] = wBishop;
	board[7][3] = wQueen;
	board[7][4] = wKing;
	board[7][5] = wBishop;
	board[7][6] = wKnight;
	board[7][7] = wRook;*/
}

Piece* Board::at(int row, int col) {
	assert(row >= 0 && row < BOARD_SIZE);
	assert(col >= 0 && col < BOARD_SIZE);
	return &board[row * BOARD_SIZE + col];
}

void Board::print(ostream& os) {
	os << "  _________________\n";
	for (int r = 0; r < BOARD_SIZE; r++) {
		os << BOARD_SIZE - r;
		for (int c = 0; c < BOARD_SIZE; c++) {
			//fix
			os << " |" << *at(r, c);
		}
		os << endl;
	}
}

ostream& operator<<(ostream& os, Board& board) {
	board.print(os);
	return os;
}