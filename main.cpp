#include <iostream>
#include "Board.h"

using namespace std;

int main() {

	Piece wPawn(PAWN, WHITE);
	Piece piece;
	Piece bPawn(PAWN, BLACK);
	Piece bBishop(BISHOP, BLACK);
	cout << wPawn << piece << bPawn << bBishop << endl;

	char a = 'r';
	Piece bRook = charToPiece(a);
	cout << bRook;

	char b = ' ';
	Piece empty = charToPiece(b);
	cout << empty;

	char c = 'B';
	Piece wBishop = charToPiece(c);
	cout << wBishop << endl;

	
	Board board;
	board.fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	cout << board.generateFenCode() << endl;

	board.fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR ");
	cout << board.generateFenCode() << endl;

	board.fenCodeToBoardStore("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR ");
	cout << board.generateFenCode() << endl;

	cout << board;
	//board.getPiece({ 'a',5 });
	
	return 0;
}