#include <sstream>
#include "pch.h"
#include "../Player.h"
#include "../Player.cpp"
#include "../Board.h"
#include "../Board.cpp"
#include "../Piece.h"
#include "../Piece.cpp"

using namespace std;

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(PrintPiece, printVarious) {
	Piece wPawn(PAWN, WHITE);
	Piece piece;
	Piece bPawn(PAWN, BLACK);
	Piece bBishop(BISHOP, BLACK);

	ostringstream output;
	output << wPawn << piece << bPawn << bBishop;
	EXPECT_EQ(output.str(), "P pb");
}



/*
std::ostringstream output;

printFoo(output);

// Not that familiar with gtest, but I think this is how you test they are
// equal. Not sure if it will work with stringstream.
EXPECT_EQ(output, "Successful");

cout << "***Print piece test cases***" << endl;

cout << "Expected:\tP pb\nActual: \t";
cout << wPawn << piece << bPawn << bBishop << endl << endl;

cout << "***charToPiece() test cases***" << endl;
cout << "Expected:\tr B\nActual: \t";
char a = 'r';
Piece bRook = charToPiece(a);
cout << bRook;

char b = ' ';
Piece empty = charToPiece(b);
cout << empty;

char c = 'B';
Piece wBishop = charToPiece(c);
cout << wBishop << endl << endl;

cout << "***fenCodeToBoardStore() and print board test cases***" << endl;
Board board;
board.fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
cout << "Expected:\trnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR\nActual: \t";
cout << board.generateFenCode() << endl << endl;

board.fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR ");
cout << "Expected:\trnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR\nActual: \t";
cout << board.generateFenCode() << endl << endl;

cout << "Expected:\trnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR\nActual: \t";
board.fenCodeToBoardStore("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR ");
cout << board.generateFenCode() << endl << endl;

cout << "1. e4 c5" << endl;
cout << board << endl << endl;

cout << "1. e4 c5 2. Nf3" << endl;
board.fenCodeToBoardStore("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");
cout << board << endl << endl;

cout << "***validCell() test cases***" << endl;
Cell cell = { 'a', 5 };
cout << "Expected:\t1\nActual: \t";
cout << validCell(cell) << endl << endl;

Cell cell2 = { 'l', 5 };
cout << "Expected:\t0\nActual: \t";
cout << validCell(cell2) << endl << endl;

Cell cell3 = { 'a', 8 };
cout << "Expected:\t1\nActual: \t";
cout << validCell(cell3) << endl << endl;

Cell cell4 = { 'z', 1 };
cout << "Expected:\t0\nActual: \t";
cout << validCell(cell4) << endl << endl;

Cell cell5 = { 'a', 0 };
cout << "Expected:\t0\nActual: \t";
cout << validCell(cell5) << endl << endl;

Cell cell6 = { 'd', 7 };
cout << "Expected:\t1\nActual: \t";
cout << validCell(cell6) << endl << endl;

cout << "***validFenCode() test cases***" << endl;
string fen1 = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R ";
cout << "Expected:\t1\nActual: \t";
cout << validFenCode(fen1) << endl << endl;

string fen2 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR ";
cout << "Expected:\t1\nActual: \t";
cout << validFenCode(fen2) << endl << endl;

string fen3 = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR ";
cout << "Expected:\t1\nActual: \t";
cout << validFenCode(fen3) << endl << endl;

string fen4 = "fehwuifuiewf";
cout << "Expected:\t0\nActual: \t";
cout << validFenCode(fen4) << endl << endl;

string fen5 = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR/ ";
cout << "Expected:\t0\nActual: \t";
cout << validFenCode(fen5) << endl << endl;

string fen6 = "rnbqkbnr/pp1ppppp/8/2p5/4P3/9/PPPP1PPP/RNBQKBNR ";
cout << "Expected:\t0\nActual: \t";
cout << validFenCode(fen6) << endl << endl;

string fen7 = "rnbqkbnr/pp1pppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR ";
cout << "Expected:\t0\nActual: \t";
cout << validFenCode(fen7) << endl << endl;

string fen8 = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR";
cout << "Expected:\t0\nActual: \t";
cout << validFenCode(fen8) << endl << endl;

cout << "Expected:\t1\nActual: \t";
cout << validFenCode(board.generateFenCode()) << endl << endl;

cout << "***getPiece() test cases***" << endl;
cout << "Expected:\t pPNk\nActual: \t";
cout << board.getPiece({ 'a',5 })
<< board.getPiece({ 'c',5 })
<< board.getPiece({ 'e',4 })
<< board.getPiece({ 'f',3 })
<< board.getPiece({ 'e',8 })
<< endl << endl;

cout << "***setPiece() test cases" << endl;
board.setPiece(bBishop, { 'd', 3 });
cout << board << endl << endl;
*/