#include <iostream>
#include "Board.h"
#include "Player.h"
using namespace std;
int main() {
    Pawn pawn(WHITE, {0,0});
    Pawn bPawn(BLACK, {0,1});
    Piece piece;
    King wKing(WHITE, {0,2});
    Piece* vec[] = {&pawn, &piece, &bPawn, &wKing};
    for (int i = 0; i < 4; i++) {
        cout << *vec[i];
    }

    cout << endl;
    Board board;
    cout << board;
    board.deleteBoard();
}
