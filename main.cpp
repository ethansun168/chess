#include <iostream>
#include <sstream>
#include "Board.h"

using namespace std;

ostream& operator << (ostream& os, Move_Return move) {
	string moveTranslation[] = {
		"Move successful",
		"Castle king successful",
		"Castle queen successful",
		"Move invalid",
		"Move obstructed",
		"Failed castle"
	};
	for (int i = MOVE_SUCCESSFUL; i <= MOVE_CASTLE_FAILURE; i++) {
		if (move == i) {
			os << moveTranslation[i] << endl;
			break;
		}
	}
	return os;
}

ostream& operator << (ostream& os, Color color) {
	if (color == 0) {
		os << "White";
	}
	else{
		os << "Black";
	}
	return os;
}

int main() {	
	Board board("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
	cout << "Starting board" << endl;
	cout << board << endl;
	cout << board.getColor() << "'s turn" << endl;
	cout << board.move(convert('e', 1), convert('g', 1));
	cout << board << endl;
	//board.move({ 7,4 }, { 7,6 });
	cout << board.getColor() << "'s turn" << endl;
	cout << board.move({ 0,1 }, { 2,2 });
	cout << board;
	cout << endl;
	Board board2;
	cout << "Starting board\n" << board2;
	board2.move(convert('e', 2), convert('e', 4));
	cout << "Pawn to e4\n" << board2;
	board2.undo();
	cout << "Undo\n" << board2;

	cout << board2.getPiece(convert('a', 3)).isEmpty();
	return 0;
}