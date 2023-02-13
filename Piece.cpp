#include "Piece.h"
#include <cassert>
using namespace std;

const char typeAbbreviations[] = {
	'P',
	'N',
	'B',
	'R',
	'Q',
	'K',
	' '
};

char pieceToChar(Piece piece) {
	for (int i = PAWN; i <= NONE; i++) {
		if (i == piece.getType()) {
			if (piece.getColor() == WHITE) {
				return typeAbbreviations[i];
			}
			else if(piece.getColor() == BLACK) {
				return (char)tolower(typeAbbreviations[i]);
			}
			else if(piece.getColor() == NEITHER) {
				return ' ';
			}
			else {
				assert(false);
			}
		}
	}
	assert(false);
}

Piece::Piece() {
	color = NEITHER;
	type = NONE;
}

Piece::Piece(Type type, Color color) {
	assert(color == WHITE || color == BLACK);
	this->type = type;
	this->color = color;
}

Color Piece::getColor() const {
	return color;
}

Type Piece::getType() const {
	return type;
}

ostream& operator<<(ostream& os, Piece& piece) {
	os << pieceToChar(piece);
	return os;
}