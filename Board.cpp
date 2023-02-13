#include "Board.h"
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
	board[0][0] = bRook;
	board[0][1] = bKnight;
	board[0][2] = bBishop;
	board[0][3] = bQueen;
	board[0][4] = bKing;
	board[0][5] = bBishop;
	board[0][6] = bKnight;
	board[0][7] = bRook;

	for (int r = 1; r < BOARD_SIZE - 1; r++) {
		for (int c = 0; c < BOARD_SIZE; c++) {
			if (r == 1) {
				//black pawns
				board[r][c] = bPawn;
			}
			else if (r > 1 && r < 6) {
				//empty
				board[r][c] = piece;
			}
			else if (r == 6) {
				//white pawns
				board[r][c] = wPawn;
			}
		}
	}

	//white back row
	board[7][0] = wRook;
	board[7][1] = wKnight;
	board[7][2] = wBishop;
	board[7][3] = wQueen;
	board[7][4] = wKing;
	board[7][5] = wBishop;
	board[7][6] = wKnight;
	board[7][7] = wRook;
}

void Board::print(ostream& os) {
	os << "  _________________\n";
	for (int r = 0; r < BOARD_SIZE; r++) {
		os << BOARD_SIZE - r;
		for (int c = 0; c < BOARD_SIZE; c++) {
			os << " |";
			board[r][c].print(os);
		}
		os << endl;
	}
}

//ostream& operator<<(ostream& os, Board& board) {
//	os << "_________________\n";
//	for (int r = 0; r < BOARD_SIZE; r++) {
//		for (int c = 0; c < BOARD_SIZE; c++) {
//			os << BOARD_SIZE - r << " |" << "\n";
//		}
//	}
//	return os;
//}