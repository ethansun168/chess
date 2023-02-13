#include "Piece.h"
#include <cassert>
using namespace std;

const string typeAbbreviations[] = {
	"P",
	"N",
	"B",
	"R",
	"Q",
	"K"
};

string pieceToString(Piece piece) {
	for (int i = PAWN; i < KING; i++) {
		if (i == piece.getType()) {
			return typeAbbreviations[i];
		}
	}
	assert(false);
}

string pieceColorToString(Piece piece) {
	if (piece.getColor() == 0) {
		return "w";
	}
	else if (piece.getColor() == 1) {
		return "b";
	}
	else {
		assert(false);
	}
}

Piece::Piece(Type type, Color color) {
	this->type = type;
	this->color = color;
}

Type Piece::getType() {
	return type;
}

Color Piece::getColor() {
	return color;
}

ostream& operator<<(ostream& os, Piece& piece) {
	os << pieceToString(piece) << pieceColorToString(piece);
	return os;
}