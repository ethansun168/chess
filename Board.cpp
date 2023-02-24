#include "Board.h"
#include <sstream>
using namespace std;

Board::Board() {
	fenCodeToBoardStore("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board::Board(string fen) {
	assert(validFenCode(fen));
	fenCodeToBoardStore(fen);
}

Color Board::getColor() const {
	return playerTurn;
}

Piece Board::getPiece(pair<int, int> location) const {
	assert(validLocation(location));
	return board[location.first][location.second];
}

void Board::setPiece(Piece piece, pair<int, int> location) {
	assert(validLocation(location));
	board[location.first][location.second] = piece;
}

void Board::movePiece(pair<int, int> start, pair<int, int> end) {
	setPiece(getPiece(start), end);
	setPiece(Piece(), start);
}

bool Board::isCheck(Color playerTurn) const {
	if (playerTurn == WHITE) {
		return (knightChecks(BLACK, whiteKingLocation) || 
				bishopChecks(BLACK, whiteKingLocation) ||
				pawnChecks(BLACK, whiteKingLocation) ||
				rookChecks(BLACK, whiteKingLocation) ||
				queenChecks(BLACK, whiteKingLocation));
	}
	// Otherwise Black Piece
	return (knightChecks(WHITE, blackKingLocation) ||
			bishopChecks(WHITE, blackKingLocation) ||
			pawnChecks(WHITE, blackKingLocation) ||
			rookChecks(WHITE, blackKingLocation) ||
			queenChecks(WHITE, blackKingLocation));
}

bool Board::knightChecks(Color color, pair<int, int> kingLocation) const {
	Piece knight(KNIGHT, color);
	return (kingCheckHelper(kingLocation, 2, 1, knight) ||
		kingCheckHelper(kingLocation, 1, 2, knight) ||
		kingCheckHelper(kingLocation, -2, 1, knight) ||
		kingCheckHelper(kingLocation, -1, 2, knight) ||
		kingCheckHelper(kingLocation, 2, -1, knight) ||
		kingCheckHelper(kingLocation, 1, -2, knight) ||
		kingCheckHelper(kingLocation, -1, -2, knight) ||
		kingCheckHelper(kingLocation, -2, -1, knight)
	);
}

bool Board::bishopChecks(Color color, pair<int, int> kingLocation) const {
	return diagonalChecks(Piece(BISHOP, color), kingLocation);
}

bool Board::diagonalChecks(Piece piece, pair<int, int> kingLocation) const {
	int row = kingLocation.first;
	int col = kingLocation.second;
	int increment = 1;
	//true if there is no obstruction in the given direction
	bool checkUpLeft = true, checkUpRight = true, checkDownRight = true, checkDownLeft = true;
	while (increment < BOARD_SIZE) {
		//check if there are bishops and no obstructions
		//makes use of short circuit
		if (checkUpLeft && kingCheckHelper(kingLocation, increment * -1, increment, piece)) { return true; }
		if (checkUpRight && kingCheckHelper(kingLocation, increment * -1, increment * -1, piece)) { return true; }
		if (checkDownRight && kingCheckHelper(kingLocation, increment, increment, piece)) { return true; }
		if (checkDownLeft && kingCheckHelper(kingLocation, increment, increment * -1, piece)) { return true; }

		//check if there are obstructions
		if (!kingCheckHelper(kingLocation, increment * -1, increment, Piece()) &&
			!kingCheckHelper(kingLocation, increment * -1, increment, piece)) {
			checkUpLeft = false;
		}

		if (!kingCheckHelper(kingLocation, increment * -1, increment * -1, Piece()) &&
			!kingCheckHelper(kingLocation, increment * -1, increment * -1, piece)) {
			checkUpRight = false;
		}

		if (!kingCheckHelper(kingLocation, increment, increment, Piece()) &&
			!kingCheckHelper(kingLocation, increment, increment, piece)) {
			checkDownRight = false;
		}

		if (!kingCheckHelper(kingLocation, increment, increment * -1, Piece()) &&
			!kingCheckHelper(kingLocation, increment, increment * -1, piece)) {
			checkDownLeft = false;
		}
		increment++;
	}
	return false;
}

// Because A8 is 00 so pawn moves have to be inverted
bool Board::pawnChecks(Color color, pair<int, int> kingLocation) const {
	//black king
	if (color == WHITE) {
		return(
			kingCheckHelper(kingLocation, 1, -1, Piece(PAWN, color)) ||
			kingCheckHelper(kingLocation, 1, 1, Piece(PAWN, color))
		);
	}
	return( //white king
		kingCheckHelper(kingLocation, -1, -1, Piece(PAWN, color)) ||
		kingCheckHelper(kingLocation, -1, 1, Piece(PAWN, color))
	);
}

bool Board::rookChecks(Color color, pair<int, int> kingLocation) const {
	return horizontalChecks(Piece(ROOK, color), kingLocation);
}

bool Board::horizontalChecks(Piece piece, pair<int, int> kingLocation) const {
	int rowKing = kingLocation.first;
	int colKing = kingLocation.second;
	int increment = 1;
	//true if there is no obstruction in the given direction
	bool checkUpper = true, checkUnder = true, checkRight = true, checkLeft = true;
	while (increment < BOARD_SIZE) {
		//check if there are rooks and no obstructions
		//makes use of short circuit
		if (checkUpper && kingCheckHelper(kingLocation, increment * -1, 0, piece)) { return true; }
		if (checkUnder && kingCheckHelper(kingLocation, increment, 0, piece)) { return true; }
		if (checkRight && kingCheckHelper(kingLocation, 0, increment, piece)) { return true; }
		if (checkLeft && kingCheckHelper(kingLocation, 0, increment * -1, piece)) { return true; }
		//check if there are obstructions
		if (!kingCheckHelper(kingLocation, increment * -1, 0, Piece()) &&
			!kingCheckHelper(kingLocation, increment * -1, 0, piece)) {
			checkUpper = false;
		}

		if (!kingCheckHelper(kingLocation, increment, 0, Piece()) &&
			!kingCheckHelper(kingLocation, increment, 0, piece)) {
			checkUnder = false;
		}

		if (!kingCheckHelper(kingLocation, 0, increment, Piece()) &&
			!kingCheckHelper(kingLocation, 0, increment, piece)) {
			checkRight = false;
		}

		if (!kingCheckHelper(kingLocation, 0, increment * -1, Piece()) &&
			!kingCheckHelper(kingLocation, 0, increment * -1, piece)) {
			checkLeft = false;
		}
		increment++;
	}
	return false;
}

bool Board::queenChecks(Color color, pair<int, int> kingLocation) const {
	return horizontalChecks(Piece(QUEEN, color), kingLocation) || diagonalChecks(Piece(QUEEN, color), kingLocation);
}

bool Board::kingCheckHelper(pair<int, int> kingLocation, int rowAdd, int colAdd, Piece piece) const {
	return (validLocation({ kingLocation.first + rowAdd, kingLocation.second + colAdd }) &&
		getPiece({ kingLocation.first + rowAdd, kingLocation.second + colAdd }) == piece);
}

bool Board::isCheckMate(Color playerTurn) const {
	return false;
}

Error_Return Board::isValidMove(pair<int, int> start, pair<int, int> end, Move_Type moveType) const {
	assert(validLocation(start) && validLocation(end));
	assert(getPiece(start).getColor() == playerTurn);
	assert(getPiece(end).isEmpty());
	assert(opposite(getPiece(end).getColor()) == playerTurn);

	switch (moveType) {
	case PAWN_MOVE:
		return validPawnMove(start, end);
	case ROOK_MOVE:
		return validRookMove(start, end);
	case KNIGHT_MOVE:
		return validKnightMove(start, end);
	case BISHOP_MOVE:
		return validBishopMove(start, end);
	case QUEEN_MOVE:
		return validQueenMove(start, end);
	case KING_MOVE:
		return validKingMove(start, end);
	case CASTLE_KING_SIDE:
		return validCastleKingSide(start, end);
	case CASTLE_QUEEN_SIDE:
		return validCastleQueenSide(start, end);
	}
}

Error_Return Board::validPawnMove(std::pair<int, int> start, std::pair<int, int> end) const {
	return MOVE_SUCCESSFUL;
}

Error_Return Board::validRookMove(std::pair<int, int> start, std::pair<int, int> end) const {
	return MOVE_SUCCESSFUL;
}

Error_Return Board::validKnightMove(std::pair<int, int> start, std::pair<int, int> end) const {
	return MOVE_SUCCESSFUL;
}

Error_Return Board::validBishopMove(std::pair<int, int> start, std::pair<int, int> end) const {
	return MOVE_SUCCESSFUL;
}

Error_Return Board::validQueenMove(std::pair<int, int> start, std::pair<int, int> end) const {
	return MOVE_SUCCESSFUL;
}

Error_Return Board::validKingMove(std::pair<int, int> start, std::pair<int, int> end) const {
	return MOVE_SUCCESSFUL;
}

Error_Return Board::validCastleKingSide(std::pair<int, int> start, std::pair<int, int> end) const {
	return MOVE_SUCCESSFUL;
}

Error_Return Board::validCastleQueenSide(std::pair<int, int> start, std::pair<int, int> end) const {
	return MOVE_SUCCESSFUL;
}

// TODO lots of work
Error_Return Board::move(pair<int, int> start, pair<int, int> end, Move_Type moveType) {
	assert(validLocation(start) && validLocation(end));
	Error_Return returnedMoveType = isValidMove(start, end, moveType);

	switch (returnedMoveType) {
	case MOVE_SUCCESSFUL:
		movePiece(start, end);
		break;
	case MOVE_CASTLE_KING_SUCCESSFUL:
		setCastleKing(playerTurn);
		break;
	case MOVE_CASTLE_QUEEN_SUCCESSFUL:
		setCastleQueen(playerTurn);
		break;
	}
	playerTurn = opposite(playerTurn);
	return returnedMoveType;
}

//values are hard coded..
bool Board::attemptCastleKing(Piece piece, Color color, pair<int, int> start, pair<int, int> end) const {
	if (color == WHITE) {
		return start.first == 7 && start.second == 4 && 
			end.first == 7 && end.second == 6 && 
			piece == Piece(KING, color);
	}
	//black castle
	return start.first == 0 && start.second == 4 && 
		end.first == 0 && end.second == 6 &&
		piece == Piece(KING, color);
}

//values are hard coded..
bool Board::attemptCastleQueen(Piece piece, Color color, pair<int, int> start, pair<int, int> end) const {
	if (color == WHITE) {
		return start.first == 7 && start.second == 4 && 
			end.first == 7 && end.second == 2 &&
			piece == Piece(KING, color);
	}
	//black castle
	return start.first == 0 && start.second == 4 && 
		end.first == 0 && end.second == 2 &&
		piece == Piece(KING, color);
}

//values are hard coded..
void Board::setCastleKing(Color color) {
	if (color == WHITE) {
		pair<int, int> start = { 7,4 };
		pair<int, int> end = { 7,6 };
		whiteKingLocation = end;
		//move king
		movePiece(start, end);
		//move rook from {7,7} to {7,5}
		movePiece({ 7,7 }, { 7,5 });
		whiteCanCastleKingSide = false;
		whiteCanCastleQueenSide = false;
	}
	else if (color == BLACK) {
		pair<int, int> start = { 0,4 };
		pair<int, int> end = { 0,6 };
		blackKingLocation = end;
		//move king
		movePiece(start, end);
		//move rook from {0,7} to {0,5}
		movePiece({ 0,7 }, { 0,5 });
		blackCanCastleKingSide = false;
		blackCanCastleQueenSide = false;
	}
}

//values are hard coded..
void Board::setCastleQueen(Color color) {
	if (color == WHITE) {
		pair<int, int> start = { 7,4 };
		pair<int, int> end = { 7,2 };
		whiteKingLocation = end;
		//move king
		movePiece(start, end);
		//move rook from {7,0} to {7,3}
		movePiece({ 7,0 }, { 7,3 });
		whiteCanCastleKingSide = false;
		whiteCanCastleQueenSide = false;
	}
	else if (color == BLACK) {
		pair<int, int> start = { 0,4 };
		pair<int, int> end = { 0,2 };
		blackKingLocation = end;
		//move king
		movePiece(start, end);
		//move rook from {0,0} to {0,3}
		movePiece({ 0,0 }, { 0,3 });
		blackCanCastleKingSide = false;
		blackCanCastleQueenSide = false;
	}
}

// TODO redo
void Board::fenCodeToBoardPrint(string fenCode, ostream& os) const {
	int rowNumber = 0, charNumber = 0, stringIndex = 0;
	os << "   _________________\n" << BOARD_SIZE << " | ";
	while (fenCode[stringIndex] != ' ') {
		int numberOfBlanks = fenCode[stringIndex] - '0';
		if (fenCode[stringIndex] == '/') {
			rowNumber++;
			charNumber = 0;
			os << "|\n" << BOARD_SIZE - rowNumber << " | ";
		}
		else if (numberOfBlanks > 0 && numberOfBlanks < 9) {
			for (int i = 0; i < numberOfBlanks; ++i) {
				os << ". ";
			}
			charNumber += numberOfBlanks;
		} else {
			os << fenCode[stringIndex] << " ";
			charNumber++;
		}
		stringIndex++;
	}
	os << "|\n  |_________________|\n    ";
	for (char ch = 'a'; ch <= 'h'; ch++) {
		os << ch << " ";
	}
}

void Board::fenCodeToBoardStore(string fenCode) {
	
	int row = 0;
	int col = 0;
	int stringIndex = 0;
	stringstream os;
	os << fenCode;
	string parse;
	os >> parse;
	while (stringIndex != parse.length()) {
		int numberOfBlanks = fenCode[stringIndex] - '0';
		if (fenCode[stringIndex] == '/') {
			col = 0;
			row++;
		}
		else if (numberOfBlanks > 0 && numberOfBlanks < 9) {
			for (int i = 0; i < numberOfBlanks; ++i) {
				Piece piece;
				setPiece(piece, { row, col });
				//board[row][col] = piece;
				col++;
			}
		}
		else {
			setPiece(charToPiece(fenCode[stringIndex]), { row, col });
			if (fenCode[stringIndex] == 'K') {
				whiteKingLocation = { row, col };
			}
			if (fenCode[stringIndex] == 'k') {
				blackKingLocation = { row, col };
			}
			//board[row][col] = charToPiece(fenCode[stringIndex]);
			col++;
		}
		stringIndex++;
	}

	os >> parse;
	if (parse == "w") {
		playerTurn = WHITE;
	}
	else if (parse == "b") {
		playerTurn = BLACK;
	}
	
	//-: 45
	//K: 75 + 1
	//Q: 81
	//k: 107
	//q: 113
	string castleRight;
	int sumOfCastleRightChar = 0;
	os >> castleRight;
	
	for (int i = 0; i < castleRight.length(); i++) {
		sumOfCastleRightChar += castleRight[i];
		if (castleRight[i] == 'K') {
			sumOfCastleRightChar += 1;
		}
	}

	switch (sumOfCastleRightChar) {
	case('-'):
		//all false
		castleModify(false, false, false, false);
		break;
	case('K' + 1):
		//white king is true
		castleModify(true, false, false, false);
		break;
	case('Q'):
		//white queen is true
		castleModify(false, true, false, false);
		break;
	case('k'):
		//black king is true
		castleModify(false, false, true, false);
		break;
	case('q'):
		//black queen is true
		castleModify(false, false, false, true);
		break;
	case('K' + 'Q' + 1):
		//white king and queen is true
		castleModify(true, true, false, false);
		break;
	case('K' + 'k' + 1):
		//white and black king is true
		castleModify(true, false, true, false);
		break;
	case('K' + 'q' + 1):
		//white king and black queen is true
		castleModify(true, false, false, true);
		break;
		break;
	case('Q' + 'q'):
		//white and black queen is true
		castleModify(false, true, false, true);
		break;
	case('K' + 'Q' + 'k' + 1):
		//white king, queen, and black king is true
		castleModify(true, true, true, false);
		break;
	case('Q' + 'k' + 'q'):
		//white queen, black king and queen is true
		castleModify(false, true, true, true);
		break;
	case('K' + 'Q' + 'k' + 'q' + 1):
		//all are true
		castleModify(true, true, true, true);
		break;
	}
	//FIX THIS - enpassant
	string enPassant;
	os >> enPassant;
	int moves;
	os >> moves;
	halfMoves = moves;
	os >> moves;
	fullMoves = moves;
}

void Board::castleModify(bool K, bool Q, bool k, bool q) {
	whiteCanCastleKingSide = K;
	whiteCanCastleQueenSide = Q;
	blackCanCastleKingSide = k;
	blackCanCastleQueenSide = q;
}

string Board::generateFenCode() const {
	string fenCode;
	for (int row = 0; row < BOARD_SIZE; row++) {
		int blank = 0;
		for (int col = 0; col < BOARD_SIZE; col++) {
			//update the blanks
			if (board[row][col].isEmpty()) {
				blank++;
			}
			else {
				//add to row string
				if (blank != 0) {
					fenCode += to_string(blank);
					blank = 0;
				}
				fenCode += pieceToChar(board[row][col]);
			}
		}
		//if the last one in row is empty
		if (board[row][BOARD_SIZE - 1].isEmpty()) {
			fenCode += to_string(blank);
		}
		if (row != BOARD_SIZE - 1) {
			fenCode += "/";
		}
	}
	fenCode += " ";
	if (playerTurn == WHITE) {
		fenCode += "w";
	}
	else if (playerTurn == BLACK) {
		fenCode += "b";
	}
	fenCode += " ";
	if (whiteCanCastleKingSide) {
		fenCode += "K";
	}
	if (whiteCanCastleQueenSide) {
		fenCode += "Q";
	}
	if (blackCanCastleKingSide) {
		fenCode += "k";
	}
	if (blackCanCastleQueenSide) {
		fenCode += "q";
	}
	if (!whiteCanCastleKingSide && !whiteCanCastleQueenSide && !blackCanCastleKingSide && !blackCanCastleQueenSide) {
		fenCode += "-";
	}
	//FIX THIS LATER en passant
	fenCode += " - ";
	
	fenCode += to_string(halfMoves);
	fenCode += " ";
	fenCode += to_string(fullMoves);
	return fenCode;
}

bool validFenCode(string fen) {

	stringstream ss;
	ss << fen;
	string in;
	int numSlash = 0;
	int rowNumPieces = 0;
	ss >> in;
	for (int i = 0; i < in.length(); i++) {
		if (in[i] == '/') {
			numSlash++;
			//check if rowNumPieces == 8
			if (rowNumPieces != 8) {
				return false;
			}
			rowNumPieces = 0;
		}
		else if (validFenChar(in[i])) {
			rowNumPieces++;
		}
		else if (in[i] <= '8' || in[i] >= '1') {
			rowNumPieces += (int)(in[i] - '0');
		}
		else {
			return false;
		}
	}
	//check for slashes
	if (numSlash != 7) {
		return false;
	}

	string playerTurn;
	ss >> playerTurn;

	if (playerTurn != "w" && playerTurn != "b") {
		return false;
	}

	string castle;
	ss >> castle;
	for (int i = 0; i < castle.length(); i++) {
		if (castle[i] != 'K' && castle[i] != 'Q' && castle[i] != 'k' && castle[i] != 'q' && castle[i] != '-') {
			return false;
		}
	}

	//FIX THIS - en passant, half moves, and full moves
	string enPassant;
	ss >> enPassant;

	int halfMoves, fullMoves;
	ss >> halfMoves;
	ss >> fullMoves;
	return true;

}

bool validFenChar(char ch) {
	//abbreviations[1] to abbreviations[6]
	for (int i = PAWN; i <= KING; i++) {
		if (ch == abbreviations[i] || ch == (char)tolower(abbreviations[i])) {
			return true;
		}
	}
	return false;
}

bool validLocation(pair<int, int> location) {
	return (
		location.first >= 0 &&
		location.first < 8 &&
		location.second >= 0 &&
		location.second < 8
		);
}

ostream& operator<< (ostream& os, const Board& board) {
	board.fenCodeToBoardPrint(board.generateFenCode(), os);
	return os;
}