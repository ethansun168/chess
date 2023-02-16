#include "Piece.h"
#include <cassert>
using namespace std;

Piece::Piece() {
	empty = true;
	color = WHITE;
	type = EMPTY;
}

//Initialize to type and color, type cannot be empty
Piece::Piece(Type type, Color color) {
	this->type = type;
	this->color = color;
	empty = false;
}
//get the type
Type Piece::getType() const {
	return type;
}
//get the color
Color Piece::getColor() const {
	return color;
}
//returns if the piece is empty
bool Piece::isEmpty() const {
	return empty;
}

char pieceToChar(Piece piece) {
	for (int i = EMPTY; i <= KING; i++) {
		if (i == piece.getType()) {
			if (piece.getColor() == BLACK) {
				return (char)tolower(abbreviations[i]);
			}
			else {
				return abbreviations[i];
			}
		}
	}
}

ostream& operator<< (ostream& os, Piece& piece) {
	os << pieceToChar(piece);
	return os;
}