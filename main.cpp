#include <iostream>
#include "Board.h"
#include "Player.h"
using namespace std;
int main() {
    Piece pawn(PAWN, WHITE);
    Piece bPawn(PAWN, BLACK);
    Piece piece;

    Piece vec[] = {pawn, piece, bPawn};
    for (auto p : vec) {
        cout << p;
    }
    //cout << "\u0074";

    cout << endl;
    Board board;
    cout << board;
}
