#include "Board.h"
#include <sstream>
using namespace std;

Board::Board() {
	undoFen.push_back("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	fenCodeToBoardStore(undoFen[0]);
}

Board::Board(string fen) {
	assert(validFenCode(fen));
	fenCodeToBoardStore(fen);
	undoFen.push_back(fen);
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
	assert(start != end);
	undoFen.push_back(generateFenCode());
	if (getPiece(start) == Piece(KING, WHITE)) {
		whiteKingLocation = end;
		whiteCanCastleKingSide = false;
		whiteCanCastleQueenSide = false;
	}
	else if (getPiece(start) == Piece(KING, BLACK)) {
		blackKingLocation = end;
		blackCanCastleKingSide = false;
		blackCanCastleQueenSide = false;
	}

	//disable castling rights when rook is moved for the first time
	if (getPiece(start) == Piece(ROOK, WHITE) &&
		start.first == 7 &&
		start.second == 7){
		whiteCanCastleKingSide = false;
	}
	if (getPiece(start) == Piece(ROOK, WHITE) &&
		start.first == 7 &&
		start.second == 0) {
		whiteCanCastleQueenSide = false;
	}
	if (getPiece(start) == Piece(ROOK, BLACK) &&
		start.first == 0 &&
		start.second == 0) {
		blackCanCastleQueenSide = false;
	}
	if (getPiece(start) == Piece(ROOK, BLACK) &&
		start.first == 0 &&
		start.second == 7) {
		blackCanCastleKingSide = false;
	}
	
	
	setPiece(getPiece(start), end);
	setPiece(Piece(), start);
}

bool Board::isCheck() const {
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
	return(
		//white king
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

bool Board::isCheckMate() const {
	return false;
}

Move_Return Board::isValidMove(pair<int, int> start, pair<int, int> end) const {
	//assert(validLocation(start) && validLocation(end));
	//assert(getPiece(start).getColor() == playerTurn);
	//assert(getPiece(end).isEmpty() || opposite(getPiece(end).getColor()) == playerTurn);

	//error checking described in RME
	if (!validLocation(start) ||
		!validLocation(end) ||
		start == end || 
		getPiece(start).isEmpty() ||
		getPiece(start).getColor() != playerTurn ||
		!getPiece(end).isEmpty() && getPiece(end).getColor() == playerTurn) {
		return MOVE_INVALID;
	}

	//DEBUG
	//if (!validLocation(start)) {
	//	return MOVE_INVALID;
	//}

	//if (!validLocation(end)) {
	//	return MOVE_INVALID;
	//}

	//if ((start.first == end.first && start.second == end.second)) {
	//	return MOVE_INVALID;
	//}

	//if (getPiece(start).isEmpty()) {
	//	return MOVE_INVALID;
	//}

	//if (getPiece(start).getColor() != playerTurn) {
	//	return MOVE_INVALID;
	//}

	//if (!getPiece(end).isEmpty() && getPiece(end).getColor() == playerTurn){
	//	return MOVE_INVALID;
	//}

	switch (getPiece(start).getType()) {
	case PAWN:
		return validPawnMove(start, end);
	case ROOK:
		return validRookMove(start, end);
	case KNIGHT:
		return validKnightMove(start, end);
	case BISHOP:
		return validBishopMove(start, end);
	case QUEEN:
		return validQueenMove(start, end);
	case KING:
		return validKingMove(start, end);
	}
}

//TODO
Move_Return Board::validPawnMove(std::pair<int, int> start, std::pair<int, int> end) const {
	// Four cases ignoring En Passant
	// Diagonal to left
	// Diagonal to right
	// forward one step
	// forward two steps
	return MOVE_SUCCESSFUL;
}

Move_Return Board::validRookMove(std::pair<int, int> start, std::pair<int, int> end) const {
	if (start.first != end.first && start.second != end.second) {
		return MOVE_INVALID;
	}
	//check for obstructions
	int directionX;
	int directionY;
	
	if (start.first == end.first) {
		//moving left and right
		directionY = 0;
		directionX = (end.second - start.second) / abs(end.second - start.second);
	}
	if (start.second == end.second) {
		//moving up and down
		directionX = 0;
		directionY = (end.first - start.first) / abs(end.first - start.first);
	}

	if (directionX) {
		//moving left and right
		for (int i = 1; i < abs(end.second - start.second); i++) {
			//row is const
			if (!getPiece({ start.first, start.second + i * directionX }).isEmpty()) {
				return MOVE_OBSTRUCTION;
			}
		}
	}
	if (directionY) {
		//moving up and down
		for (int i = 1; i < abs(end.first - start.first); i++) {
			//col is const
			if (!getPiece({ start.first + i * directionY, start.second }).isEmpty()) {
				return MOVE_OBSTRUCTION;
			}
		}
	}
	return MOVE_SUCCESSFUL;
}

Move_Return Board::validKnightMove(std::pair<int, int> start, std::pair<int, int> end) const {
	//no obstructions for the knight
	if (
		!(abs(start.first - end.first) == 1 && abs(start.second - end.second) == 2) &&
		!(abs(start.first - end.first) == 2 && abs(start.second - end.second) == 1)
		) {
		return MOVE_INVALID;
	}
	return MOVE_SUCCESSFUL;
}

Move_Return Board::validBishopMove(std::pair<int, int> start, std::pair<int, int> end) const {
	if (abs(start.first - end.first) != abs(start.second - end.second)) {
		return MOVE_INVALID;
	}
	//check for obstructions
	int directionX;
	int directionY;

	if (end.second - start.second < 0) {
		directionX = -1;
	}
	else {
		directionX = 1;
	}

	if (end.first - start.first < 0) {
		directionY = -1;
	}
	else {
		directionY = 1;
	}
	//loop thru the diag in the direction
	for (int i = 1; i < abs(start.first - end.first); i++) {
		if (!getPiece({ start.first + i * directionY, start.second + i * directionX }).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}
	}
	return MOVE_SUCCESSFUL;
}

Move_Return Board::validQueenMove(std::pair<int, int> start, std::pair<int, int> end) const {
	Move_Return horizVert = validRookMove(start, end);
	Move_Return diagonal = validBishopMove(start, end);
	
	if (horizVert == MOVE_SUCCESSFUL || diagonal == MOVE_SUCCESSFUL) {
		return MOVE_SUCCESSFUL;
	}
	if (horizVert == MOVE_OBSTRUCTION || diagonal == MOVE_OBSTRUCTION) {
		return MOVE_OBSTRUCTION;
	}
	
	return MOVE_INVALID;
}

Move_Return Board::validKingMove(std::pair<int, int> start, std::pair<int, int> end) const {
	if (attemptCastleKing(start, end)) {
		return validCastleKingSide(start, end);
	}
	else if (attemptCastleQueen(start, end)) {
		return validCastleQueenSide(start, end);
	}
	//king can only move in squares adjacent to it
	if (abs(start.first - end.first) != 1 || abs(start.second - end.second) != 1) {
		return MOVE_INVALID;
	}
	return MOVE_SUCCESSFUL;
}

Move_Return Board::validCastleKingSide(std::pair<int, int> start, std::pair<int, int> end) const {
	if (playerTurn == WHITE && !whiteCanCastleKingSide) {
		return MOVE_CASTLE_FAILURE;
	}
	if (playerTurn == BLACK && !blackCanCastleKingSide) {
		return MOVE_CASTLE_FAILURE;
	}
	//king cannot castle from, through, or into check
	Board tempBoard(generateFenCode());
	
	//through check
	if (playerTurn == WHITE) {
		//no obstructions
		if (!tempBoard.getPiece(convert('f', 1)).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}
		if (!tempBoard.getPiece(convert('g', 1)).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}

		tempBoard.movePiece(convert('e', 1), convert('f', 1));
		if (tempBoard.isCheck()) {
			return MOVE_CASTLE_FAILURE;
		}
		tempBoard.undo();

		tempBoard.movePiece(convert('e', 1), convert('g', 1));
		if (tempBoard.isCheck()) {
			return MOVE_CASTLE_FAILURE;
		}
		tempBoard.undo();
	}
	else {
		//check for black
		//no obstructions
		if (!tempBoard.getPiece(convert('f', 8)).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}
		if (!tempBoard.getPiece(convert('g', 8)).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}

		tempBoard.movePiece(convert('e', 8), convert('f', 8));
		if (tempBoard.isCheck()) {
			return MOVE_CASTLE_FAILURE;
		}
		tempBoard.undo();

		tempBoard.movePiece(convert('e', 8), convert('g', 8));
		if (tempBoard.isCheck()) {
			return MOVE_CASTLE_FAILURE;
		}
		tempBoard.undo();
	}

	//from check
	if (tempBoard.isCheck()) {
		return MOVE_CASTLE_FAILURE;
	}
	
	//into check
	tempBoard.setCastleKing();
	if (tempBoard.isCheck()) {
		return MOVE_CASTLE_FAILURE;
	}
	tempBoard.undo();
	return MOVE_CASTLE_KING_SUCCESSFUL;
}

Move_Return Board::validCastleQueenSide(std::pair<int, int> start, std::pair<int, int> end) const {
	if (playerTurn == WHITE && !whiteCanCastleQueenSide) {
		return MOVE_CASTLE_FAILURE;
	}
	if (playerTurn == BLACK && !blackCanCastleQueenSide) {
		return MOVE_CASTLE_FAILURE;
	}
	//king cannot castle from, through, or into check
	Board tempBoard(generateFenCode());

	//through check
	if (playerTurn == WHITE) {
		//no obstructions
		if (!tempBoard.getPiece(convert('d', 1)).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}
		if (!tempBoard.getPiece(convert('c', 1)).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}
		if (!tempBoard.getPiece(convert('b', 1)).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}

		tempBoard.movePiece(convert('e', 1), convert('d', 1));
		if (tempBoard.isCheck()) {
			return MOVE_CASTLE_FAILURE;
		}
		tempBoard.undo();

		tempBoard.movePiece(convert('e', 1), convert('c', 1));
		if (tempBoard.isCheck()) {
			return MOVE_CASTLE_FAILURE;
		}
		tempBoard.undo();
	}
	else {
		//check for black
		//no obstructions
		if (!tempBoard.getPiece(convert('d', 8)).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}
		if (!tempBoard.getPiece(convert('c', 8)).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}
		if (!tempBoard.getPiece(convert('b', 8)).isEmpty()) {
			return MOVE_OBSTRUCTION;
		}

		tempBoard.movePiece(convert('e', 8), convert('d', 8));
		if (tempBoard.isCheck()) {
			return MOVE_CASTLE_FAILURE;
		}
		tempBoard.undo();

		tempBoard.movePiece(convert('e', 8), convert('c', 8));
		if (tempBoard.isCheck()) {
			return MOVE_CASTLE_FAILURE;
		}
		tempBoard.undo();
	}

	//from check
	if (tempBoard.isCheck()) {
		return MOVE_CASTLE_FAILURE;
	}

	//into check
	tempBoard.setCastleQueen();
	if (tempBoard.isCheck()) {
		return MOVE_CASTLE_FAILURE;
	}
	tempBoard.undo();
	
	return MOVE_CASTLE_QUEEN_SUCCESSFUL;
}

// TODO: lots of work
Move_Return Board::move(pair<int, int> start, pair<int, int> end) {
	//assert(validLocation(start) && validLocation(end));
	Move_Return returnedMoveType = isValidMove(start, end);

	switch (returnedMoveType) {
	case MOVE_SUCCESSFUL:
		movePiece(start, end);
		playerTurn = opposite(playerTurn);
		//TODO: update full moves
		//TODO: update half moves
		break;
	case MOVE_CASTLE_KING_SUCCESSFUL:
		setCastleKing();
		break;
	case MOVE_CASTLE_QUEEN_SUCCESSFUL:
		setCastleQueen();
		break;
	}

	return returnedMoveType;
}

bool Board::attemptCastleKing(pair<int, int> start, pair<int, int> end) const {
	assert(getPiece(start).getType() == KING);
	if (playerTurn == WHITE) {
		return start.first == 7 && start.second == 4 &&
			end.first == 7 && end.second == 6;
	}
	//black castle
	return start.first == 0 && start.second == 4 &&
		end.first == 0 && end.second == 6;
}

bool Board::attemptCastleQueen(pair<int, int> start, pair<int, int> end) const {
	assert(getPiece(start).getType() == KING);
	if (playerTurn == WHITE) {
		return start.first == 7 && start.second == 4 &&
			end.first == 7 && end.second == 2;
	}
	//black castle
	return start.first == 0 && start.second == 4 &&
		end.first == 0 && end.second == 2;
}

void Board::setCastleKing() {
	if (playerTurn == WHITE) {
		//move king
		pair<int, int> kingStart = { 7,4 };
		pair<int, int> kingEnd = { 7,6 };
		movePiece(kingStart, kingEnd);

		//move rook from {7,7} to {7,5}
		pair<int, int> rookStart = { 7,7 };
		pair<int, int> rookEnd = { 7,5 };
		movePiece(rookStart, rookEnd);
	}
	else if (playerTurn == BLACK) {
		//move king
		pair<int, int> kingStart = { 0,4 };
		pair<int, int> kingEnd = { 0,6 };
		movePiece(kingStart, kingEnd);

		//move rook from {0,7} to {0,5}
		pair<int, int> rookStart = { 0,7 };
		pair<int, int> rookEnd = { 0,5 };
		movePiece(rookStart, rookEnd);
	}
}

void Board::setCastleQueen() {
	if (playerTurn == WHITE) {
		//move king
		pair<int, int> kingStart = { 7,4 };
		pair<int, int> kingEnd = { 7,2 };
		movePiece(kingStart, kingEnd);

		//move rook from {7,0} to {7,3}
		pair<int, int> rookStart = { 7,0 };
		pair<int, int> rookEnd = { 7,3 };
		movePiece(rookStart, rookEnd);
	}
	else if (playerTurn == BLACK) {
		//move king
		pair<int, int> kingStart = { 0,4 };
		pair<int, int> kingEnd = { 0,2 };
		movePiece(kingStart, kingEnd);

		//move rook from {0,0} to {0,3}
		pair<int, int> rookStart = { 0,0 };
		pair<int, int> rookEnd = { 0,3 };
		movePiece(rookStart, rookEnd);
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
	//TODO: enpassant
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
	//TODO: en passant
	fenCode += " - ";
	
	fenCode += to_string(halfMoves);
	fenCode += " ";
	fenCode += to_string(fullMoves);
	return fenCode;
}

bool Board::undo() {
	if (undoFen.size() > 1) {
		fenCodeToBoardStore(undoFen[undoFen.size() - 1]);
		undoFen.pop_back();
		return true;
	}
	return false;
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
		if (castle[i] == '-' && castle.length() > 1) {
			return false;
		}
		if (castle[i] != 'K' && castle[i] != 'Q' && castle[i] != 'k' && castle[i] != 'q' && castle[i] != '-') {
			return false;
		}
	}

	//TODO: en passant, half moves, and full moves
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

pair<int, int> convert(char file, int rank) {
	assert(file >= 'a' && file <= 'h');
	assert(rank >= 1 && rank <= 8);
	pair<int, int> location;
	location.first = BOARD_SIZE - rank;
	location.second = file - 'a';
	return location;
}

ostream& operator<< (ostream& os, const Board& board) {
	board.fenCodeToBoardPrint(board.generateFenCode(), os);
	os << endl;
	return os;
}