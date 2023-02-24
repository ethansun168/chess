#include <iostream>
#include <sstream>
#include "Board.h"

using namespace std;

int main() {
	Board board;
	cout << board << endl;
	board.move({ 7,6 }, { 5, 5 }, PAWN_MOVE);
	cout << board << endl;
	//board.move({ 7,4 }, { 7,6 });
	board.move({ 7,4 }, { 7,2 }, CASTLE_KING_SIDE);
	cout << board;
	return 0;
}