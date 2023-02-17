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

TEST(Piece, printVarious) {
	Piece wPawn(PAWN, WHITE);
	Piece piece;
	Piece bPawn(PAWN, BLACK);
	Piece bBishop(BISHOP, BLACK);

	ostringstream output;
	output << wPawn << piece << bPawn << bBishop;
	EXPECT_EQ(output.str(), "P pb");

}

TEST(Piece, charToPiece) {
	char a = 'r';
	Piece bRook = charToPiece(a);

	char b = ' ';
	Piece empty = charToPiece(b);

	char c = 'B';
	Piece wBishop = charToPiece(c);
	ostringstream output;
	output << bRook << empty << wBishop;
	EXPECT_EQ(output.str(), "r B");
}

TEST(Board, fenCode1) {
	Board board;
	board.fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	EXPECT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR ", board.generateFenCode());
}

TEST(Board, fenCode2) {
	Board board;
	board.fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR ");
	EXPECT_EQ("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR ", board.generateFenCode());
}

TEST(Board, fenCode3) {
	Board board;
	board.fenCodeToBoardStore("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR ");
	EXPECT_EQ("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR ", board.generateFenCode());
}

TEST(Board, printBoard1) {
	Board board;
	ostringstream os;
	os << board;
	ostringstream correct;
	correct << "   _________________\n"
		    << "8 | r n b q k b n r |\n"
		    << "7 | p p p p p p p p |\n"
		    << "6 | . . . . . . . . |\n"
		    << "5 | . . . . . . . . |\n"
		    << "4 | . . . . . . . . |\n"
		    << "3 | . . . . . . . . |\n"
		    << "2 | P P P P P P P P |\n"
		    << "1 | R N B Q K B N R |\n"
		    << "  |_________________|\n"
		    << "    a b c d e f g h ";
	EXPECT_EQ(os.str(), correct.str());
}

TEST(Board, printBoard2) {
	Board board;
	board.fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR ");
	ostringstream os;
	os << board;
	ostringstream correct;
	correct << "   _________________\n"
		    << "8 | r n b q k b n r |\n"
		    << "7 | p p p p p p p p |\n"
		    << "6 | . . . . . . . . |\n"
		    << "5 | . . . . . . . . |\n"
		    << "4 | . . . . P . . . |\n"
		    << "3 | . . . . . . . . |\n"
		    << "2 | P P P P . P P P |\n"
		    << "1 | R N B Q K B N R |\n"
		    << "  |_________________|\n"
		    << "    a b c d e f g h ";
	EXPECT_EQ(os.str(), correct.str());
}

TEST(Board, printBoard3) {
	Board board("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR ");
	ostringstream os;
	os << board;
	ostringstream correct;
	correct << "   _________________\n"
		    << "8 | r n b q k b n r |\n"
		    << "7 | p p . p p p p p |\n"
		    << "6 | . . . . . . . . |\n"
		    << "5 | . . p . . . . . |\n"
		    << "4 | . . . . P . . . |\n"
		    << "3 | . . . . . . . . |\n"
		    << "2 | P P P P . P P P |\n"
		    << "1 | R N B Q K B N R |\n"
		    << "  |_________________|\n"
		    << "    a b c d e f g h ";
	EXPECT_EQ(os.str(), correct.str());
}

TEST(Board, printBoard4) {
	Board board("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R ");
	ostringstream os;
	os << board;
	ostringstream correct;
	correct << "   _________________\n"
		    << "8 | r n b q k b n r |\n"
		    << "7 | p p . p p p p p |\n"
		    << "6 | . . . . . . . . |\n"
		    << "5 | . . p . . . . . |\n"
		    << "4 | . . . . P . . . |\n"
		    << "3 | . . . . . N . . |\n"
		    << "2 | P P P P . P P P |\n"
		    << "1 | R N B Q K B . R |\n"
		    << "  |_________________|\n"
		    << "    a b c d e f g h ";
	EXPECT_EQ(os.str(), correct.str());
}

TEST(Board, validCellGeneral) {
	Cell cell = { 'a', 5 };
	EXPECT_TRUE(validCell(cell));
}

TEST(Board, validCellGeneralFail) {
	Cell cell = { 'l', 5 };
	EXPECT_FALSE(validCell(cell));
}

TEST(Board, validCellEdgeCase) {
	Cell cell = { 'a', 8 };
	EXPECT_TRUE(validCell(cell));
}

TEST(Board, validCellGeneralFail2) {
	Cell cell = { 'z', 1 };
	EXPECT_FALSE(validCell(cell));
}

TEST(Board, validCellEdgeCase2) {
	Cell cell = { 'a', 0 };
	EXPECT_FALSE(validCell(cell));
}

TEST(Board, validFenCodeGeneral) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R ";
	EXPECT_TRUE(validFenCode(fen));
}

TEST(Board, validFenCodeGeneral2) {
	string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR ";
	EXPECT_TRUE(validFenCode(fen));
}

TEST(Board, validFenCodeGeneral3) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR ";
	EXPECT_TRUE(validFenCode(fen));
}

TEST(Board, validFenCodeGeneralFail) {
	string fen = "fehwuifuiewf";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(Board, validFenCodeSlashFail) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR/ ";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(Board, validFenCodeRowNumberFail) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/9/PPPP1PPP/RNBQKBNR ";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(Board, validFenCodeRowNumberFail2) {
	string fen = "rnbqkbnr/pp1pppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR ";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(Board, validFenCodeNoSpaceFail) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(Board, validFenCodeImplementedFen) {
	Board board;
	EXPECT_TRUE(validFenCode(board.generateFenCode()));
}

TEST(Board, getPiece) {
	Board board;
	ostringstream os;
	os << board.getPiece({ 'a',5 })
	   << board.getPiece({ 'c',7 })
	   << board.getPiece({ 'e',2 })
	   << board.getPiece({ 'f',1 })
	   << board.getPiece({ 'e',8 });
	EXPECT_EQ(" pPBk", os.str());
}

TEST(Board, setPiece) {
	Board board;
	Piece bBishop(BISHOP, BLACK);
	board.setPiece(bBishop, { 'd', 3 });
	ostringstream os;
	os << board;
	ostringstream correct;
	correct << "   _________________\n"
		    << "8 | r n b q k b n r |\n"
		    << "7 | p p p p p p p p |\n"
		    << "6 | . . . . . . . . |\n"
		    << "5 | . . . . . . . . |\n"
		    << "4 | . . . . . . . . |\n"
		    << "3 | . . . b . . . . |\n"
		    << "2 | P P P P P P P P |\n"
		    << "1 | R N B Q K B N R |\n"
		    << "  |_________________|\n"
		    << "    a b c d e f g h ";
	EXPECT_EQ(os.str(), correct.str());
}