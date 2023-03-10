#include "Piece.h"
using namespace std;

Piece::Piece() {
	empty = true;
	color = WHITE;
	type = EMPTY;
}

Piece::Piece(Type type, Color color) {
	assert(color == WHITE || color == BLACK);
	assert(type >= EMPTY && type <= KING);
	this->type = type;
	this->color = color;
	this->empty = false;
}

Type Piece::getType() const {
	return type;
}

Color Piece::getColor() const {
	return color;
}

void Piece::setColor(Color color) {
	this->color = color;
}

void Piece::setType(Type type) {
	this->type = type;
}

void Piece::setEmpty(bool empty) {
	this->empty = empty;
}

bool Piece::isEmpty() const {
	return empty;
}

Color opposite(Color color) {
	return (color == WHITE) ? BLACK : WHITE;
}

char pieceToChar(Piece piece) {
	return (piece.getColor() == BLACK) ?
		tolower(abbreviations[piece.getType()]) :
		abbreviations[piece.getType()];
}

Piece charToPiece(char charPiece) {
	Piece newPiece;
	for (uint8_t loopPiece = PAWN; loopPiece <= KING; loopPiece++) {
		if (toupper(charPiece) == abbreviations[loopPiece]) {
			isupper(charPiece) ? newPiece.setColor(WHITE) : newPiece.setColor(BLACK);
			newPiece.setType( (Type) loopPiece);
			newPiece.setEmpty(false);
		}
	}
	return newPiece;
}

ostream& operator<< (ostream& os, const Piece& piece) {
	os << pieceToChar(piece);
	return os;
}

bool operator== (const Piece& lPiece, const Piece& rPiece) {
	return lPiece.getType() == rPiece.getType() && lPiece.getColor() == rPiece.getColor();
}