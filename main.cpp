#include <iostream>
#include <regex>
#include <sstream>

#include "Board.h"
#include "Player.h"

using namespace std;

int main() {
    Board board;
    regex value("[a-h][1-8]");
    bool whitePlayer = true;

    while (1) {
        string start, end;
        cout << board;
        cin >> start >> end;

        PieceMovement move;

        if (start == "exit") {
            break;
        }
        else if (regex_match(start, value) && regex_match(end, value)) {
            if (whitePlayer) {
                move = board.moveWhite({ start[1] - '1', start[0] - 'a' }, { end[1] - '1', end[0] - 'a' });
            } else {
                move = board.moveBlack({ start[1] - '1', start[0] - 'a' }, { end[1] - '1', end[0] - 'a' });
            }

            switch (move) {
            case INVALID_MOVEMENT:
                cout << "This piece cannot do this move\n";
                break;
            case PIECE_IN_WAY:
                cout << "There is a piece in the way of this move\n";
                break;
            case MOVE_SUCCESS:
                cout << "Move completed successfully\n";
                break;
            }
        }
        else {
            cout << "Please enter a valid movement\n";
        }

        

        whitePlayer = !whitePlayer;
    }

    board.deleteBoard();
}