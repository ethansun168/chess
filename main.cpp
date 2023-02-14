#include <iostream>
#include "Board.h"
#include "Player.h"
using namespace std;
int main() {
    Pawn pawn(WHITE);
    Pawn bPawn(BLACK);
    Piece piece;
    King wKing(WHITE);
    Piece* vec[] = {&pawn, &piece, &bPawn, &wKing};
    for (int i = 0; i < 4; i++) {
        cout << *vec[i];
    }

    cout << endl;
    Board board;
    cout << board;
    //board.deleteBoard();
}
