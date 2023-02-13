#include "Board.h"
using namespace std;

Board::Board() {
	Piece whitePawn(PAWN, WHITE);
	Piece blackPawn(PAWN, BLACK);
	for (int r = 0; r < BOARD_SIZE; r++) {
		for (int c = 0; c < BOARD_SIZE; c++) {
			
		}
	}
}

ostream& operator<<(ostream& os, Board& board) {
	os << "_________________\n";
	for (int r = BOARD_SIZE - 1; r >= 0; r--) {
		for (int c = 0; c < BOARD_SIZE; c++) {
			os << r << " |" << "\n";
		}
	}
	return os;
}