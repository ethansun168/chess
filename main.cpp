#include <iostream>
#include <sstream>
#include "Board.h"

using namespace std;

int main() {
	Board board("8/8/2B5/2K5/1p1p4/2n3k1/8/2q5 w - - 0 1");
	cout << board << endl;

	board.isCheck(WHITE);
	cout << validFenCode("2R5/5K2/8/8/2kb4/8/8/8 w - - 1 1");
	return 0;
}