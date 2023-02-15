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

        if (start == "exit") {
            break;
        }
        else if (regex_match(start, value) && regex_match(end, value)) {
            if (whitePlayer) {
                if (board.moveWhite({ start[0] - 'a', start[1] - '0' }, { end[0] - 'a', end[1] - '0' })) {
                    cout << "Move successful\n";
                }
            }
            else {
                if(board.moveBlack({ start[0] - 'a', start[1] - '0' }, { end[0] - 'a', end[1] - '0' })) {
                   cout << "Move successful\n";
                }
            }
        }
        else {
            cout << "Please enter a valid movement\n";
        }

        whitePlayer = !whitePlayer;
    }

    board.deleteBoard();
}