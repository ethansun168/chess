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

	// Black pawns
	for (int i = 0; i < BOARD_SIZE; ++i) {
		board[1][i] = new Pawn(BLACK, { 1, i });
	}

	// White pawns
	for (int i = 0; i < BOARD_SIZE; ++i) {
		board[6][i] = new Pawn(WHITE, { 6, i });
	}

	// Empty Pieces
	for (int i = 0; i < BOARD_SIZE; ++i) {
		board[2][i] = new Piece();
		board[3][i] = new Piece();
		board[4][i] = new Piece();
		board[5][i] = new Piece();
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

PieceMovement Board::moveWhite(pair<int,int> start, pair<int,int> end) {
	//beautiful code
	Piece* currentPiece = getPiece(start);
	switch (currentPiece->getType()) {
	case PAWN: //move two
		if ((start.first - end.first) == 2 && pawnStartLocation(true, start.first)) {
			if (pieceExists({ start.first - 1, start.second }) ||
				pieceExists({ start.first - 2, start.second })) {
				return PIECE_IN_WAY;
			}
			else {
				currentPiece->setLocation(end);
				setPiece(currentPiece, start, end);
				return MOVE_SUCCESS;
			}
		}	//move one
		else if ((start.first - end.first) == 1) {
			if (pieceExists({ start.first - 1, start.second })) {
				return PIECE_IN_WAY;
			}
			else {
				currentPiece->setLocation(end);
				setPiece(currentPiece, start, end);
				return MOVE_SUCCESS;
			}
		}	// diagonal
		else if ((abs(end.second - start.second)) == 1) {
			if (pieceExists(end)) {
				getPiece(end)->setType(NONE);
				currentPiece->setLocation(end);
				setPiece(currentPiece, start, end);
				return MOVE_SUCCESS;
			}
			else {
				return INVALID_MOVEMENT;
			}
		}
		break;
	case KNIGHT:

		break;
	case BISHOP:

		break;
	case QUEEN:

		break;
	case KING:

		break;
	default:
		return INVALID_MOVEMENT;
	}
	return INVALID_MOVEMENT;
}

PieceMovement Board::moveBlack(pair<int,int> start, pair<int, int> end) {
	switch (getPiece(start)->getType()) {
	case PAWN:
		//e7 = [][1]
		if (start.second == 1) {
			//can move 2
		}
		else {
			//only move 1 or diagonal
		}
		break;
	case KNIGHT:

		break;
	case BISHOP:

		break;
	case QUEEN:

		break;
	case KING:

		break;
	default:
		return INVALID_MOVEMENT;
	}
	return INVALID_MOVEMENT;
}

Piece* Board::getPiece(pair<int,int> location) const {
	return board[location.first][location.second];
}

void Board::setPiece(Piece* piece, pair<int, int> start, pair<int, int> end) {
	board[start.first][start.second]->setType(NONE);
	board[end.first][end.second] = piece;
}

bool Board::pawnStartLocation(bool isWhite, int startLoc) {
	return isWhite ? (startLoc == 1) : (startLoc == 6);
}

bool Board::pieceExists(pair<int, int> location) const {
	return (board[location.first][location.second]->getColor() != NEITHER);
}

ostream& operator<<(ostream& os, Board& board) {
	board.print(os);
	return os;
}