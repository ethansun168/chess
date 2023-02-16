#include <iostream>
<<<<<<< HEAD
#include "Board.h";
=======
#include "Board.h"
>>>>>>> 7b0f6273d60c031c92606ad6b73ec947ad80e290

using namespace std;

int main() {

	Piece wPawn(PAWN, WHITE);
	Piece piece;
	Piece bPawn(PAWN, BLACK);
	Piece bBishop(BISHOP, BLACK);
	cout << wPawn << piece << bPawn << bBishop;
	return 0;
}