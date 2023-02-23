#include <iostream>
#include <sstream>
#include "Board.h"

using namespace std;

int main() {
	Board board;
	cout << board << endl;
	board.move({ 7,6 }, { 5, 5 });
	cout << board << endl;
	//board.move({ 7,4 }, { 7,6 });
	board.move({ 7,4 }, { 7,2 });
	cout << board;
	return 0;
}