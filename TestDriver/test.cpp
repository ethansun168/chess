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
		    << "    a b c d e f g h ";
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
		    << "    a b c d e f g h ";
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
		    << "    a b c d e f g h ";
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
		    << "    a b c d e f g h ";
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

TEST(BoardGetPiece, getPiece) {
	Board board;
	ostringstream os;
	os << board.getPiece({ 'a',5 })
	   << board.getPiece({ 'c',7 })
	   << board.getPiece({ 'e',2 })
	   << board.getPiece({ 'f',1 })
	   << board.getPiece({ 'e',8 });
	EXPECT_EQ(" pPBk", os.str());
}

TEST(BoardSetPiece, setPiece) {
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

TEST(BoardIsCheck, whiteBishopCheck) {
	Board board("rnbqkbnr/ppppp1pp/8/5p1B/8/8/PPPPPPPP/RNBQK1NR w KQkq - 0 1");
	EXPECT_TRUE(board.isCheck(BLACK));
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, whiteBishopCheckBlocked) {
	Board board("rnbqkbnr/pppppppp/8/7B/8/8/PPPPPPPP/RNBQK1NR w KQkq - 0 1");
	EXPECT_FALSE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteBishopCheck2) {
	Board board("8/5K2/4B3/8/2k5/8/8/8 w - - 1 1");
	EXPECT_TRUE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, blackBishopCheck) {
	Board board("8/8/8/2K5/8/4b1k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackBishopCheck2) {
	Board board("8/8/8/2K5/3p4/b5k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackBishopCheckBlocked) {
	Board board("8/8/8/2K5/3p4/4b1k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, whiteKnightCheck) {
	Board board("rnbqkbnr/pppp2pp/5N2/4pp2/8/8/PPPPPPPP/RNBQKB1R w KQkq - 0 1");
	EXPECT_TRUE(board.isCheck(BLACK));
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, whiteKnightCheckBlocked) {
	Board board("rnbqkbnr/pppppppp/5N2/8/8/8/PPPPPPPP/RNBQKB1R w KQkq - 0 1");
	EXPECT_TRUE(board.isCheck(BLACK));
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, whiteKnightCheck2) {
	Board board("rnbqkbnr/pppppppp/3N4/8/8/8/PPPPPPPP/RNBQKB1R w KQkq - 0 1");
	EXPECT_TRUE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, blackKnightCheck) {
	Board board("8/8/8/2K5/3p4/1n4k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackKnightCheckBlocked) {
	Board board("8/8/8/2K5/1pBp4/1n4k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackKnightCheck2) {
	Board board("8/8/4n3/2K5/1pBp4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, whiteQueenCheckDiag) {
	Board board("8/5K2/4Q3/8/2k5/8/8/8 w - - 1 1");
	EXPECT_TRUE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteQueenCheckDiagBlocked) {
	Board board("8/5K2/4Q3/3b4/2k5/8/8/8 w - - 1 1");
	EXPECT_FALSE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteQueenCheckUp) {
	Board board("4Q3/8/2B5/8/1p1p4/2n3K1/8/4k3 w - - 0 1");
	EXPECT_TRUE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteQueenCheckUpBlocked) {
	Board board("8/2Q2K2/8/2b5/2k5/8/8/8 w - - 1 1");
	EXPECT_FALSE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteQueenCheckRight) {
	Board board("8/5K2/8/2b5/2k4Q/8/8/8 w - - 1 1");
	EXPECT_TRUE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteQueenCheckLeft) {
	Board board("8/8/2B5/8/1p1pQ2k/2n3K1/8/8 b - - 0 1");
	EXPECT_TRUE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteQueenCheckDiag2) {
	Board board("8/5K2/8/2b5/2k5/8/Q7/8 w - - 1 1");
	EXPECT_TRUE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteQueenCheckDownBlocked) {
	Board board("3k4/8/2B5/8/1p1p4/2n3K1/8/3Q4 w - - 0 1");
	EXPECT_FALSE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteQueenCheckDown) {
	Board board("8/8/2B5/5K2/1p1p4/2n3k1/8/6Q1 w - - 0 1");
	EXPECT_TRUE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, blackQueenCheckDiag) {
	Board board("5q2/8/8/2K5/1pBp4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackQueenCheckDiag2) {
	Board board("8/q7/8/2K5/1pBp4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackQueenCheckDiagBlocked) {
	Board board("8/q7/1B6/2K5/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackQueenCheckRight) {
	Board board("8/8/1B6/2K3q1/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackQueenCheckRightBlocked) {
	Board board("8/8/8/2KB2q1/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackQueenCheckLeft) {
	Board board("8/8/8/q1KB4/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackQueenCheckLeftBlocked) {
	Board board("8/3B4/8/qnK5/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackQueenCheckUp) {
	Board board("2q5/4B3/8/1nK5/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackQueenCheckUpBlocked) {
	Board board("2q5/8/2B5/1nK5/1p1p4/6k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackQueenCheckDown) {
	Board board("8/8/2B5/1nK5/1p1p4/6k1/8/2q5 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackQueenCheckDownBlocked) {
	Board board("8/8/2B5/2K5/1p1p4/2n3k1/8/2q5 w - - 0 1");
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, whiteRookCheckUpBlocked) {
	Board board("2R5/5K2/8/2B5/2kb4/8/8/8 w - - 1 1");
	EXPECT_FALSE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteRookCheckUp) {
	Board board("2R5/5K2/8/8/2kb4/8/8/8 w - - 1 1");
	EXPECT_TRUE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteRookCheckRightBlocked) {
	Board board("8/5K2/8/8/2kb3R/8/8/8 w - - 1 1");
	EXPECT_FALSE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteRookCheckRight) {
	Board board("8/5K2/8/2b5/2k4R/8/8/8 w - - 1 1");
	EXPECT_TRUE(board.isCheck(BLACK));
}

TEST(BoardIsCheck, whiteRookCheckRight2) {
	Board board("8/5k2/8/2b5/2K4r/8/8/8 w - - 1 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackRookCheckRight) {
	Board board("8/8/2B5/2K4r/1p1p4/2n3k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackRookCheckRightBlocked) {
	Board board("8/8/2B5/2Kp3r/1p6/2n3k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackRookCheckLeft) {
	Board board("8/8/2B5/r1Kp4/1p6/2n3k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackRookCheckLeftBlocked) {
	Board board("8/8/2B5/rpKp4/8/2n3k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackRookCheckDownBlocked) {
	Board board("2r5/8/2B5/1pKp4/8/2n3k1/8/8 w - - 0 1");
	EXPECT_FALSE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackRookCheckDown) {
	Board board("2r5/8/3B4/1pKp4/8/2n3k1/8/8 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackRookCheckUp) {
	Board board("8/8/3B4/1pKp4/8/1n4k1/8/2r5 w - - 0 1");
	EXPECT_TRUE(board.isCheck(WHITE));
}

TEST(BoardIsCheck, blackRookCheckUpBlocked) {
	Board board("8/8/3B4/1pKp4/8/2n3k1/8/2r5 w - - 0 1");
	EXPECT_FALSE(board.isCheck(WHITE));
}
