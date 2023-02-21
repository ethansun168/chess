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

Piece Board::getPiece(Cell cell) const {
	assert(validCell(cell));
	//e5 = board[row + BOARD_SIZE + col] = board[3][4]
	return board[cellToBoard(cell).first][cellToBoard(cell).second];
}

void Board::setPiece(Piece piece, Cell cell) {
	assert(validCell(cell));
	board[cellToBoard(cell).first][cellToBoard(cell).second] = piece;
}

bool Board::isCheck(Color playerTurn) const {
	Cell kingCell;
	if (playerTurn == WHITE) {
		//check white king
		for (int row = 0; row < BOARD_SIZE; row++) {
			for (int col = 0; col < BOARD_SIZE; col++) {
				if (board[row][col] == Piece(KING,  WHITE)) {
					kingCell = boardToCell(row, col);
				}
			}
		}
		//check knight checks
		if (knightChecks(kingCell, BLACK)) {
			return true;
		}
	}
	else {
		//check black king
		for (int row = 0; row < BOARD_SIZE; row++) {
			for (int col = 0; col < BOARD_SIZE; col++) {
				if (board[row][col] == Piece(KING, BLACK)) {
					kingCell = boardToCell(row, col);
				}
			}
		}
		//check knight checks
		if (knightChecks(kingCell, WHITE)) {
			return true;
		}
	}
	return false;
}

bool Board::knightChecks(Cell kingCell, Color color) const {
	if (kingCell.file - 'a' + 2 < BOARD_SIZE &&
		kingCell.rank + 1 <= BOARD_SIZE &&
		getPiece({ (char)(kingCell.file + 2), kingCell.rank + 1 }) == Piece(KNIGHT, color)) {
		return true;
	}
	if (kingCell.file - 'a' + 1 < BOARD_SIZE &&
		kingCell.rank + 2 <= BOARD_SIZE &&
		getPiece({ (char)(kingCell.file + 1), kingCell.rank + 2 }) == Piece(KNIGHT, color)) {
		return true;
	}
	if (kingCell.file - 'a' - 2 >= 1 &&
		kingCell.rank + 1 <= BOARD_SIZE &&
		getPiece({ (char)(kingCell.file - 2), kingCell.rank + 1 }) == Piece(KNIGHT, color)) {
		return true;
	}
	if (kingCell.file - 'a' - 1 >= 1 &&
		kingCell.rank + 2 <= BOARD_SIZE &&
		getPiece({ (char)(kingCell.file - 1), kingCell.rank + 2 }) == Piece(KNIGHT, color)) {
		return true;
	}
	if (kingCell.file - 'a' + 2 < BOARD_SIZE &&
		kingCell.rank - 1 >= 1 &&
		getPiece({ (char)(kingCell.file + 2), kingCell.rank - 1 }) == Piece(KNIGHT, color)) {
		return true;
	}
	if (kingCell.file - 'a' + 1 < BOARD_SIZE &&
		kingCell.rank - 2 >= 1 &&
		getPiece({ (char)(kingCell.file + 1), kingCell.rank - 2 }) == Piece(KNIGHT, color)) {
		return true;
	}
	if (kingCell.file - 'a' - 1 >= 1 &&
		kingCell.rank - 2 >= 1 &&
		getPiece({ (char)(kingCell.file - 1), kingCell.rank - 2 }) == Piece(KNIGHT, color)) {
		return true;
	}
	if (kingCell.file - 'a' - 2 >= 1 &&
		kingCell.rank - 1 >= 1 &&
		getPiece({ (char)(kingCell.file - 2), kingCell.rank - 1 }) == Piece(KNIGHT, color)) {
		return true;
	}
}

bool Board::isCheckMate(Color playerTurn) const {
	return false;
}

// TODO: FIX LATER
bool Board::canCastle(Color playerTurn) const {
	if (playerTurn == WHITE) {
		return (whiteCanCastleKingSide) || (whiteCanCastleQueenSide);
	}
	else {
		return (blackCanCastleKingSide || blackCanCastleQueenSide);
	}
}

bool Board::isValidMove(Color playerTurn, Cell start, Cell end) const {
	assert(validCell(start) && validCell(end));
	return false;
}

bool Board::move(Cell start, Cell end) {
	assert(validCell(start) && validCell(end));
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
				board[row][col] = piece;
				col++;
			}
		}
		else {
			board[row][col] = charToPiece(fenCode[stringIndex]);
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

void Board::castleModify(bool K, bool Q, bool k, bool q) {
	whiteCanCastleKingSide = K;
	whiteCanCastleQueenSide = Q;
	blackCanCastleKingSide = k;
	blackCanCastleQueenSide = q;
}

ostream& operator<< (ostream& os, const Board& board) {
	board.fenCodeToBoardPrint(board.generateFenCode(), os);
	return os;
}

bool validCell(Cell cell) {
	return 1 <= cell.rank && 8 >= cell.rank && 'a' <= cell.file && 'h' >= cell.file;
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

pair<int, int> cellToBoard(Cell cell) {
	assert(validCell(cell));
	//e5 -> [3][4]
	//cell.rank = row = 5 -> 3
	//cell.file = col = e -> 4
	pair<int, int> boardRowCol = {BOARD_SIZE - cell.rank, cell.file - 'a'};
	return boardRowCol;
}

Cell boardToCell(int row, int col) {
 	assert(0 <= row && row < BOARD_SIZE);
	assert(0 <= col && col < BOARD_SIZE);
	//[3][4] -> e5
	//4 = col -> cell.file
	//3 = row -> cell.rank
	Cell cell = {(char) (col + 'a'), BOARD_SIZE - row};
	return cell;
}