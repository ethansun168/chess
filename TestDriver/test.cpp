#pragma once
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

TEST(BoardFenCode, general) {
	Board board;
	board.fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	EXPECT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", board.generateFenCode());
}

TEST(BoardFenCode, general2) {
	Board board;
	board.fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1");
	EXPECT_EQ("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1", board.generateFenCode());
}

TEST(BoardFenCode, general3) {
	Board board;
	board.fenCodeToBoardStore("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
	EXPECT_EQ("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", board.generateFenCode());
}

TEST(BoardPrint, general) {
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
		    << "    a b c d e f g h \n";
	EXPECT_EQ(os.str(), correct.str());
}

TEST(BoardPrint, general2) {
	Board board;
	board.fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1");
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
		    << "    a b c d e f g h \n";
	EXPECT_EQ(os.str(), correct.str());
}

TEST(BoardPrint, general3) {
	Board board("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
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
		    << "    a b c d e f g h \n";
	EXPECT_EQ(os.str(), correct.str());
}

TEST(BoardPrint, general4) {
	Board board("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 0 2");
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
		    << "    a b c d e f g h \n";
	EXPECT_EQ(os.str(), correct.str());
}

TEST(BoardValidFenCode, general) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 0 2";
	EXPECT_TRUE(validFenCode(fen));
}

TEST(BoardValidFenCode, general2) {
	string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	EXPECT_TRUE(validFenCode(fen));
}

TEST(BoardValidFenCode, general3) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w - e3 0 1";
	EXPECT_TRUE(validFenCode(fen));
}

TEST(BoardValidFenCode, generalFail) {
	string fen = "fehwuifuiewf";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(BoardValidFenCode, slashFail) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR/ w KQkq - 0 1";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(BoardValidFenCode, rowNumberFail) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/9/PPPP1PPP/RNBQKBNR w KQkq - 0 1";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(BoardValidFenCode, rowNumberFail2) {
	string fen = "rnbqkbnr/pp1pppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(BoardValidFenCode, noEndingFail) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR ";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(BoardValidFenCode, implementedFen) {
	Board board;
	EXPECT_TRUE(validFenCode(board.generateFenCode()));
}

TEST(BoardValidFenCode, castle1) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w K e3 0 1";
	EXPECT_TRUE(validFenCode(fen));
}

TEST(BoardValidFenCode, castle2) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w Kq e3 0 1";
	EXPECT_TRUE(validFenCode(fen));
}

TEST(BoardValidFenCode, castle4) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w Kk e3 0 1";
	EXPECT_TRUE(validFenCode(fen));
}

TEST(BoardValidFenCode, castleFail) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w fheuwiufhu e3 0 1";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(BoardValidFenCode, castleFailEdge) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w K-Qq e3 0 1";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(BoardValidFenCode, castleNone) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w - e3 0 1";
	EXPECT_TRUE(validFenCode(fen));
}

TEST(BoardValidFenCode, castleNoneFail) {
	string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w -- e3 0 1";
	EXPECT_FALSE(validFenCode(fen));
}

TEST(BoardGetPiece, getPiece) {
	Board board;
	ostringstream os;

	os << board.getPiece({ 3, 0 })
		<< board.getPiece({ 1, 2 })
		<< board.getPiece({ 6, 4 })
		<< board.getPiece({ 7,5 })
		<< board.getPiece({ 0,4 });
	/*os << board.getPiece({ 'a',5 })
	   << board.getPiece({ 'c',7 })
	   << board.getPiece({ 'e',2 })
	   << board.getPiece({ 'f',1 })
	   << board.getPiece({ 'e',8 });*/
	EXPECT_EQ(" pPBk", os.str());
}

TEST(BoardSetPiece, setPiece) {
	Board board;
	Piece bBishop(BISHOP, BLACK);
	board.setPiece(bBishop, { 5, 3 });
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
		    << "    a b c d e f g h \n";
	EXPECT_EQ(os.str(), correct.str());
}

TEST(BoardIsCheck, whiteBishopCheck) {
	Board board("rnbqkbnr/ppppp1pp/8/5p1B/8/8/PPPPPPPP/RNBQK1NR b KQkq - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whiteBishopCheckBlocked) {
	Board board("rnbqkbnr/pppppppp/8/7B/8/8/PPPPPPPP/RNBQK1NR b KQkq - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, whiteBishopCheck2) {
	Board board("8/5K2/4B3/8/2k5/8/8/8 b - - 1 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackBishopCheck) {
	Board board("8/8/8/2K5/8/4b1k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackBishopCheck2) {
	Board board("8/8/8/2K5/3p4/b5k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackBishopCheckBlocked) {
	Board board("8/8/8/2K5/3p4/4b1k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, whiteKnightCheck) {
	Board board("rnbqkbnr/pppp2pp/5N2/4pp2/8/8/PPPPPPPP/RNBQKB1R b KQkq - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whiteKnightCheckBlocked) {
	Board board("rnbqkbnr/pppppppp/5N2/8/8/8/PPPPPPPP/RNBQKB1R b KQkq - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whiteKnightCheck2) {
	Board board("rnbqkbnr/pppppppp/3N4/8/8/8/PPPPPPPP/RNBQKB1R b KQkq - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackKnightCheck) {
	Board board("8/8/8/2K5/3p4/1n4k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackKnightCheckBlocked) {
	Board board("8/8/8/2K5/1pBp4/1n4k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackKnightCheck2) {
	Board board("8/8/4n3/2K5/1pBp4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whiteQueenCheckDiag) {
	Board board("8/5K2/4Q3/8/2k5/8/8/8 b - - 1 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whiteQueenCheckDiagBlocked) {
	Board board("8/5K2/4Q3/3b4/2k5/8/8/8 b - - 1 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, whiteQueenCheckUp) {
	Board board("4Q3/8/2B5/8/1p1p4/2n3K1/8/4k3 b - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whiteQueenCheckUpBlocked) {
	Board board("8/2Q2K2/8/2b5/2k5/8/8/8 b - - 1 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, whiteQueenCheckRight) {
	Board board("8/5K2/8/2b5/2k4Q/8/8/8 b - - 1 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whiteQueenCheckLeft) {
	Board board("8/8/2B5/8/1p1pQ2k/2n3K1/8/8 b - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whiteQueenCheckDiag2) {
	Board board("8/5K2/8/2b5/2k5/8/Q7/8 b - - 1 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whiteQueenCheckDownBlocked) {
	Board board("3k4/8/2B5/8/1p1p4/2n3K1/8/3Q4 b - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, whiteQueenCheckDown) {
	Board board("8/8/2B5/5K2/1p1p4/2n3k1/8/6Q1 b - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckDiag) {
	Board board("5q2/8/8/2K5/1pBp4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckDiag2) {
	Board board("8/q7/8/2K5/1pBp4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckDiagBlocked) {
	Board board("8/q7/1B6/2K5/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckRight) {
	Board board("8/8/1B6/2K3q1/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckRightBlocked) {
	Board board("8/8/8/2KB2q1/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckLeft) {
	Board board("8/8/8/q1KB4/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckLeftBlocked) {
	Board board("8/3B4/8/qnK5/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckUp) {
	Board board("2q5/4B3/8/1nK5/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckUpBlocked) {
	Board board("2q5/8/2B5/1nK5/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckDown) {
	Board board("8/8/2B5/1nK5/1p1p4/6k1/8/2q5 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackQueenCheckDownBlocked) {
	Board board("8/8/2B5/2K5/1p1p4/2n3k1/8/2q5 w - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, whiteRookCheckUpBlocked) {
	Board board("2R5/5K2/8/2B5/2kb4/8/8/8 b - - 1 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, whiteRookCheckUp) {
	Board board("2R5/5K2/8/8/2kb4/8/8/8 b - - 1 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whiteRookCheckRightBlocked) {
	Board board("8/5K2/8/8/2kb3R/8/8/8 b - - 1 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, whiteRookCheckRight) {
	Board board("8/5K2/8/2b5/2k4R/8/8/8 b - - 1 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackRookCheckRight2) {
	Board board("8/5k2/8/2b5/2K4r/8/8/8 w - - 1 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackRookCheckRight) {
	Board board("8/8/2B5/2K4r/1p1p4/2n3k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackRookCheckRightBlocked) {
	Board board("8/8/2B5/2Kp3r/1p6/2n3k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, blackRookCheckLeft) {
	Board board("8/8/2B5/r1Kp4/1p6/2n3k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackRookCheckLeftBlocked) {
	Board board("8/8/2B5/rpKp4/8/2n3k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, blackRookCheckDownBlocked) {
	Board board("2r5/8/2B5/1pKp4/8/2n3k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, blackRookCheckDown) {
	Board board("2r5/8/3B4/1pKp4/8/2n3k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackRookCheckUp) {
	Board board("8/8/3B4/1pKp4/8/1n4k1/8/2r5 w - - 0 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackRookCheckUpBlocked) {
	Board board("8/8/3B4/1pKp4/8/2n3k1/8/2r5 w - - 0 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, whitePawnCheckEdge) {
	Board board("k7/1P6/8/5K2/8/8/8/8 b - - 1 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, whitePawnCheck) {
	Board board("1k6/1P6/8/5K2/8/8/8/8 b - - 1 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(BoardIsCheck, blackPawnCheckEdge) {
	Board board("1k6/1P6/8/8/8/8/6p1/7K w - - 1 1");
	EXPECT_TRUE(board.isCheck());
}

TEST(BoardIsCheck, blackPawnCheck) {
	Board board("1k6/1P6/8/8/8/8/6p1/6K1 w - - 1 1");
	EXPECT_FALSE(board.isCheck());
}

TEST(Convert, general1) {
	EXPECT_EQ(convert('a', 6).first, 2);
	EXPECT_EQ(convert('a', 6).second, 0);
}

TEST(Convert, general2) {
	EXPECT_EQ(convert('f', 2).first, 6);
	EXPECT_EQ(convert('f', 2).second, 5);
}

TEST(Castle, whiteKingGeneral) {
	Board board("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 1), convert('g', 1)), MOVE_CASTLE_KING_SUCCESSFUL);
	EXPECT_EQ(board.getPiece(convert('g', 1)), Piece(KING,WHITE));
	EXPECT_EQ(board.getPiece(convert('f', 1)), Piece(ROOK, WHITE));
}

TEST(Castle, whiteKingInCheck) {
	Board board("r3k2r/4q3/8/8/8/8/8/R3K2R w KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 1), convert('g', 1)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, whiteKingThruCheck) {
	Board board("r3k2r/8/1q6/8/8/8/8/R3K2R w KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 1), convert('g', 1)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, whiteKingThruCheck2) {
	Board board("r3k2r/8/8/1q6/8/8/8/R3K2R w KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 1), convert('g', 1)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, whiteQueenGeneral) {
	Board board("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 1), convert('c', 1)), MOVE_CASTLE_QUEEN_SUCCESSFUL);
	EXPECT_EQ(board.getPiece(convert('c', 1)), Piece(KING, WHITE));
	EXPECT_EQ(board.getPiece(convert('d', 1)), Piece(ROOK, WHITE));
}

TEST(Castle, whiteQueenInCheck) {
	Board board("r3k2r/8/8/8/7q/8/8/R3K2R w KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 1), convert('c', 1)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, whiteQueenThruCheck) {
	Board board("r3k2r/8/8/8/3q4/8/8/R3K2R w KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 1), convert('c', 1)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, whiteQueenThruCheck2) {
	Board board("r3k2r/8/8/8/5q2/8/8/R3K2R w KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 1), convert('c', 1)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, whiteQueenThruCheck3) {
	Board board("r3k2r/8/8/5q2/8/8/8/R3K2R w KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 1), convert('c', 1)), MOVE_CASTLE_QUEEN_SUCCESSFUL);
}

TEST(Castle, blackKingGeneral) {
	Board board("r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 8), convert('g', 8)), MOVE_CASTLE_KING_SUCCESSFUL);
	EXPECT_EQ(board.getPiece(convert('g', 8)), Piece(KING, BLACK));
	EXPECT_EQ(board.getPiece(convert('f', 8)), Piece(ROOK, BLACK));
}

TEST(Castle, blackKingInCheck) {
	Board board("r3k2r/8/8/8/8/4Q3/8/R3K2R b KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 8), convert('g', 8)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, blackKingThruCheck) {
	Board board("r3k2r/8/8/8/1Q6/8/8/R3K2R b KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 8), convert('g', 8)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, blackKingThruCheck2) {
	Board board("r3k2r/8/8/8/6Q1/8/8/R3K2R b KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 8), convert('g', 8)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, blackQueenGeneral) {
	Board board("r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 8), convert('c', 8)), MOVE_CASTLE_QUEEN_SUCCESSFUL);
	EXPECT_EQ(board.getPiece(convert('c', 8)), Piece(KING, BLACK));
	EXPECT_EQ(board.getPiece(convert('d', 8)), Piece(ROOK, BLACK));
}

TEST(Castle, blackQueenInCheck) {
	Board board("r3k2r/8/8/8/Q7/8/8/R3K2R b KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 8), convert('c', 8)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, blackQueenThruCheck) {
	Board board("r3k2r/8/1N6/8/8/8/8/R3K2R b KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 8), convert('c', 8)), MOVE_CASTLE_FAILURE);
}

TEST(Castle, blackQueenThruCheck2) {
	Board board("r3k2r/8/8/8/2N5/6B1/8/R3K2R b KQkq - 0 1");
	EXPECT_EQ(board.move(convert('e', 8), convert('c', 8)), MOVE_CASTLE_QUEEN_SUCCESSFUL);
}

TEST(Undo, general) {
	Board board;
	board.move(convert('e', 2), convert('e', 4));
	EXPECT_EQ(board.generateFenCode(), "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1");
	board.undo();
	EXPECT_EQ(board.generateFenCode(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

TEST(Undo, doubleUndo) {
	Board board;
	board.move(convert('g', 1), convert('f', 3));
	board.move(convert('g', 8), convert('f', 6));
	EXPECT_TRUE(board.undo());
	EXPECT_TRUE(board.undo());
	EXPECT_EQ(board.generateFenCode(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	EXPECT_FALSE(board.undo());
}

TEST(validMove, kingGeneral) {
	Board board;
	EXPECT_EQ(board.isValidMove(convert('e', 1), convert('f', 1)), MOVE_INVALID);
	EXPECT_EQ(board.isValidMove(convert('e', 1), convert('a', 3)), MOVE_INVALID);
}

TEST(validMove, kingDiag) {
	Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPP2PP/RNBQKBNR w KQkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 1), convert('f', 2)), MOVE_SUCCESSFUL);
}

TEST(validMove, kingCastleObstruct) {
	Board board("rnbqkbnr/pppppppp/8/8/8/5N2/PPPP2PP/RNBQKB1R w KQkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 1), convert('g', 1)), MOVE_OBSTRUCTION);
}

TEST(validMove, bishopGeneral) {
	Board board("rnbqkbnr/pppppppp/8/8/2B5/8/PPPP2PP/RNBQK1NR w KQkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('c', 4), convert('e', 6)), MOVE_SUCCESSFUL);
}

TEST(validMove, bishopObstruct) {
	Board board("rnbqkbnr/pppppppp/8/3N4/2B5/8/PPPP2PP/RNBQK2R w KQkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('c', 4), convert('e', 6)), MOVE_OBSTRUCTION);
}

TEST(validMove, bishopObstruct2) {
	Board board("rnbqkb1r/pppppppp/4n3/8/5N2/1B6/PPPP2PP/RNBQK2R w KQkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('b', 3), convert('f', 7)), MOVE_OBSTRUCTION);
}

TEST(validMove, bishopInvalid) {
	Board board("rnbqkbnr/pppppppp/8/8/2B5/8/PPPP2PP/RNBQK1NR w KQkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('c', 4), convert('h', 3)), MOVE_INVALID);
}

TEST(validMove, bishopCapture) {
	Board board("rnbqkb1r/pppppppp/4n3/8/5N2/1B6/PPPP2PP/RNBQK2R w KQkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('b', 3), convert('e', 6)), MOVE_SUCCESSFUL);
}

TEST(validMove, rookGeneral) {
	Board board("rnbqkb1r/pppppppp/8/2n3R1/8/8/PPPP2PP/RNBQKBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('g', 5), convert('d', 5)), MOVE_SUCCESSFUL);
}

TEST(validMove, rookGeneral2) {
	Board board("rnbqkb1r/pppppppp/8/2n3R1/8/8/PPPP2PP/RNBQKBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('g', 5), convert('g', 3)), MOVE_SUCCESSFUL);
}

TEST(validMove, rookInvalid) {
	Board board("rnbqkb1r/pppppppp/8/8/2n3R1/8/PPPP2PP/RNBQKBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('g', 5), convert('e', 6)), MOVE_INVALID);
}

TEST(validMove, rookObstruction) {
	Board board("rnbqkb1r/pppppppp/8/2n3R1/8/8/PPPP2PP/RNBQKBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('g', 5), convert('a', 5)), MOVE_OBSTRUCTION);
}

TEST(validMove, rookObstruction2) {
	Board board("rnbqkb1r/pppppppp/8/2n3R1/8/8/PPPP2PP/RNBQKBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('g', 5), convert('g', 8)), MOVE_OBSTRUCTION);
}

TEST(validMove, rookCapture) {
	Board board("rnbqkb1r/pppppppp/8/2n3R1/8/8/PPPP2PP/RNBQKBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('g', 5), convert('c', 5)), MOVE_SUCCESSFUL);
}

TEST(validMove, queenGeneral) {
	Board board("rnbqkb1r/pppppppp/8/8/8/4Q3/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 3), convert('e', 6)), MOVE_SUCCESSFUL);
}

TEST(validMove, queenGeneral2) {
	Board board("rnbqkb1r/pppppppp/8/8/8/4Q3/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 3), convert('e', 2)), MOVE_SUCCESSFUL);
}

TEST(validMove, queenGeneral3) {
	Board board("rnbqkb1r/pppppppp/8/8/8/4Q3/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 3), convert('h', 6)), MOVE_SUCCESSFUL);
}

TEST(validMove, queenGeneral4) {
	Board board("rnbqkb1r/pppppppp/8/8/8/4Q3/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 3), convert('b', 6)), MOVE_SUCCESSFUL);
}

TEST(validMove, queenGeneral5) {
	Board board("rnbqkb1r/pppppppp/8/8/8/4Q3/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 3), convert('d', 2)), MOVE_SUCCESSFUL);
}

TEST(validMove, queenInvalid) {
	Board board("rnbqkb1r/pppppppp/8/8/8/4Q3/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 3), convert('d', 5)), MOVE_INVALID);
}

TEST(validMove, queenInvalid2) {
	Board board("rnbqkb1r/pppppppp/8/8/8/4Q3/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 3), convert('d', 8)), MOVE_INVALID);
}

TEST(validMove, queenObstruct) {
	Board board("rnbqkb1r/pppppppp/8/8/8/4Q3/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 3), convert('e', 8)), MOVE_OBSTRUCTION);
}

TEST(validMove, queenObstruct2) {
	Board board("rnbqkb1r/pppppppp/8/8/8/5Q2/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('f', 3), convert('a', 8)), MOVE_OBSTRUCTION);
}

TEST(validMove, queenCapture) {
	Board board("rnbqkb1r/pppppppp/8/8/8/4Q3/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 3), convert('e', 7)), MOVE_SUCCESSFUL);
}

TEST(validMove, queenCapture2) {
	Board board("rnbqkb1r/pppppppp/8/8/8/5Q2/PPP5/RNB1KBN1 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('f', 3), convert('b', 7)), MOVE_SUCCESSFUL);
}

TEST(validMove, knightGeneral) {
	Board board;
	EXPECT_EQ(board.isValidMove(convert('g', 1), convert('f', 3)), MOVE_SUCCESSFUL);
}

TEST(validMove, knightInvalid) {
	Board board;
	EXPECT_EQ(board.isValidMove(convert('g', 1), convert('d', 4)), MOVE_INVALID);
}

TEST(validMove, knightInvalid2) {
	Board board("rnbqkb1r/pppppppp/8/8/8/4N3/PPP5/RNB1KB2 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('e', 3), convert('c', 2)), MOVE_INVALID);
}

TEST(validMove, knightCapture) {
	Board board("rnbqkb1r/pppppppp/8/5N2/8/8/PPP5/RNB1KB2 w Qkq - 0 1");
	EXPECT_EQ(board.isValidMove(convert('f', 5), convert('g', 7)), MOVE_SUCCESSFUL);
}

