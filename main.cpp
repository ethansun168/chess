#include <iostream>
#include "Board.h"

using namespace std;

int main() {

	Piece wPawn(PAWN, WHITE);
	Piece piece;
	Piece bPawn(PAWN, BLACK);
	Piece bBishop(BISHOP, BLACK);
	cout << wPawn << piece << bPawn << bBishop;
	return 0;
}