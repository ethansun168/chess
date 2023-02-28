#include <iostream>
#include <sstream>
#include "Board.h"

using namespace std;

int main() {
	Board board;
	cout << board << endl;
	cout << board.getColor() << "'s turn" << endl;
	board.move({ 7,5 }, { 5, 5 });
	cout << board << endl;
	//board.move({ 7,4 }, { 7,6 });
	cout << board.getColor() << "'s turn" << endl;
	board.move({ 0,1 }, { 2,2 });
	cout << board;
	return 0;
}