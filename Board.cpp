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
	board[0][0] = new Rook(BLACK);
	board[0][1] = new Knight(BLACK);
	board[0][2] = new Bishop(BLACK);
	board[0][3] = new Queen(BLACK);
	board[0][4] = new King(BLACK);
	board[0][5] = new Bishop(BLACK);
	board[0][6] = new Knight(BLACK);
	board[0][7] = new Rook(BLACK);

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
				//board[r][c] = bPawn;
				board[r][c] = new Pawn(BLACK);
			}
			else if (r > 1 && r < 6) {
				//empty
				//board[r][c] = piece;
				board[r][c] = new Piece();
			}
			else if (r == 6) {
				//white pawns
				//board[r][c] = wPawn;
				board[r][c] = new Pawn(WHITE);
			}
		}
	}

	//white back row
	board[7][0] = new Rook(WHITE);
	board[7][1] = new Knight(WHITE);
	board[7][2] = new Bishop(WHITE);
	board[7][3] = new Queen(WHITE);
	board[7][4] = new King(WHITE);
	board[7][5] = new Bishop(WHITE);
	board[7][6] = new Knight(WHITE);
	board[7][7] = new Rook(WHITE);
	/*board[7][0] = wRook;
	board[7][1] = wKnight;
	board[7][2] = wBishop;
	board[7][3] = wQueen;
	board[7][4] = wKing;
	board[7][5] = wBishop;
	board[7][6] = wKnight;
	board[7][7] = wRook;*/
}

void Board::print(ostream& os) {
	os << "   _______________\n";
	for (int r = 0; r < BOARD_SIZE; r++) {
		os << BOARD_SIZE - r << " ";
		for (int c = 0; c < BOARD_SIZE; c++) {
			//fix
			os << "|" << *board[r][c];
			if (c == BOARD_SIZE - 1) { os << "|"; }
		}
		os << endl;
	}
}

void Board::deleteBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			delete board[i][j];
		}
	}
}

ostream& operator<<(ostream& os, Board& board) {
	board.print(os);
	return os;
}