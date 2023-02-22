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

Piece Board::getPiece(pair<int, int> location) const {
	assert(isValidLocation(location));
	return board[location.first][location.second];
}

void Board::setPiece(Piece piece, pair<int, int> location) {
	assert(isValidLocation(location));
	board[location.first][location.second] = piece;
}

bool Board::isValidLocation(pair<int, int> location) const {
	return (
		location.first >= 0 &&
		location.first < 8 &&
		location.second >= 0 &&
		location.second < 8
	);
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
	Piece empty;
	while (increment < BOARD_SIZE) {
		//check if there are bishops and no obstructions
		if (checkUpLeft && kingCheckHelper(kingLocation, increment * -1, increment, piece)) { return true; }
		if (checkUpRight && kingCheckHelper(kingLocation, increment * -1, increment * -1, piece)) { return true; }
		if (checkDownRight && kingCheckHelper(kingLocation, increment, increment, piece)) { return true; }
		if (checkDownLeft && kingCheckHelper(kingLocation, increment, increment * -1, piece)) { return true; }

		//check if there are obstructions
		if (!kingCheckHelper(kingLocation, increment * -1, increment, empty) &&
			!kingCheckHelper(kingLocation, increment * -1, increment, piece)) {
			checkUpLeft = false;
		}

		if (!kingCheckHelper(kingLocation, increment * -1, increment * -1, empty) &&
			!kingCheckHelper(kingLocation, increment * -1, increment * -1, piece)) {
			checkUpRight = false;
		}

		if (!kingCheckHelper(kingLocation, increment, increment, empty) &&
			!kingCheckHelper(kingLocation, increment, increment, piece)) {
			checkDownRight = false;
		}

		if (!kingCheckHelper(kingLocation, increment, increment * -1, empty) &&
			!kingCheckHelper(kingLocation, increment, increment * -1, piece)) {
			checkDownLeft = false;
		}

		increment++;
	}
	return false;
}

// Because A8 is 00 so pawn moves have to be inverted
bool Board::pawnChecks(Color color, pair<int, int> kingLocation) const {
	Piece pawn(PAWN, color);
	if (color == WHITE) {
		return(
			//black king
			kingCheckHelper(kingLocation, 1, -1, pawn) ||
			kingCheckHelper(kingLocation, 1, 1, pawn)
		);
	}
	return(
		//white king
		kingCheckHelper(kingLocation, -1, -1, pawn) ||
		kingCheckHelper(kingLocation, -1, 1, pawn)
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
	Piece empty;
	while (increment < BOARD_SIZE) {
		//check if there are rooks and no obstructions
		if (checkUpper && kingCheckHelper(kingLocation, increment * -1, 0, piece)) { return true; }
		if (checkUnder && kingCheckHelper(kingLocation, increment, 0, piece)) { return true; }
		if (checkRight && kingCheckHelper(kingLocation, 0, increment, piece)) { return true; }
		if (checkLeft && kingCheckHelper(kingLocation, 0, increment * -1, piece)) { return true; }

		//check if there are obstructions
		if (!kingCheckHelper(kingLocation, increment * -1, 0, empty) &&
			!kingCheckHelper(kingLocation, increment * -1, 0, piece)) {
			checkUpper = false;
		}

		if (!kingCheckHelper(kingLocation, increment, 0, empty) &&
			!kingCheckHelper(kingLocation, increment, 0, piece)) {
			checkUnder = false;
		}

		if (!kingCheckHelper(kingLocation, 0, increment, empty) &&
			!kingCheckHelper(kingLocation, 0, increment, piece)) {
			checkRight = false;
		}

		if (!kingCheckHelper(kingLocation, 0, increment * -1, empty) &&
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

bool Board::isCheckMate(Color playerTurn) const {
	return false;
}

bool Board::kingCheckHelper(pair<int, int> kingLocation, int rowAdd, int colAdd, Piece piece) const {
	return (isValidLocation({ kingLocation.first + rowAdd, kingLocation.second + colAdd }) &&
		getPiece({ kingLocation.first + rowAdd, kingLocation.second + colAdd }) == piece);
}

// TODO: FIX LATER
//this function is probably useless
bool Board::canCastle(Color playerTurn) const {
	if (playerTurn == WHITE) {
		return (whiteCanCastleKingSide) || (whiteCanCastleQueenSide);
	}
	return (blackCanCastleKingSide || blackCanCastleQueenSide);
}

bool Board::isValidMove(Color playerTurn, pair<int, int> start, pair<int, int> end) const {
	assert(isValidLocation(start) && isValidLocation(end));
	return false;
}

//TODO: update king move if it is moved
bool Board::move(pair<int, int> start, pair<int, int> end) {
	assert(isValidLocation(start) && isValidLocation(end));
	if (isValidMove(playerTurn, start, end)) {
		// Gets the piece at start, and sets that piece to end location
		setPiece(getPiece(start), end);
		Piece piece;
		// this is really bad code
		setPiece(piece, end);
		return true;
	}
	return false;
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

ostream& operator<< (ostream& os, const Board& board) {
	board.fenCodeToBoardPrint(board.generateFenCode(), os);
	return os;
}