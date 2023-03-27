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
		"Failed castle",
		"Piece is pinned",
		"King is in check"
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
	Board board;
	cout << board.getColor() << "'s turn\n";
	while (!board.isCheckMate()) {
		cout << board;
		cout << "Enter your move: first two is start, last two is end\n[FileRank FileRank]\n";
		char startFile;
		char endFile;
		int startRank;
		int endRank;
		cin >> startFile >> startRank >> endFile >> endRank;
		while (startFile < 'a' || 
			startFile > 'h' || 
			startRank < 1 || 
			startRank > 8 ||
			endFile < 'a' || 
			endFile > 'h' || 
			endRank < 1 || 
			endRank > 8) {
			cout << "Invalid input! Enter something valid:\n";
			cin.clear();
			string temp;
			getline(cin, temp);
			
			cin >> startFile >> startRank >> endFile >> endRank;
		}
		cout << board.move(convert(startFile, startRank), convert(endFile, endRank)) << endl;
		cout << board.getColor() << "'s turn\n";

	}
	return 0;
}