#include "Piece.h"
#include <cassert>
using namespace std;

//PIECE IMPLEMENTATIONS
Piece::Piece() {
	color = NEITHER;
	type = NONE;
}

Piece::Piece(Type type, Color color, pair<int, int> location) {
	setType(type);
	setColor(color);
	setLocation(location);
}

Color Piece::getColor() const {
	return color;
}

Type Piece::getType() const {
	return type;
}

pair<int, int> Piece::getLocation() {
	return location;
}

void Piece::setColor(Color color) {
	assert(color == WHITE || color == BLACK);
	this->color = color;
}

void Piece::setType(Type type) {
	this->type = type;
}

void Piece::setLocation(pair<int, int> location) {
	this->location = location;
}

void Piece::print(ostream& os) const {
	os << abbreviation;
}

ostream& operator<<(ostream& os, const Piece& piece) {
	piece.print(os);
	return os;
}

//PAWN IMPLEMENTATIONS
Pawn::Pawn(Color color, pair<int, int> location) : Piece(PAWN, color, location) {

}

void Pawn::print(ostream& os) const {
	Color color = getColor();
	if (color == WHITE) {
		os << abbreviation;
	}
	else if (color == BLACK) {
		os << (char)tolower(abbreviation);
	}
	else {
		assert(false);
	}
}

Bishop::Bishop(Color color, pair<int, int> location) : Piece(BISHOP, color, location) {

}

void Bishop::print(ostream& os) const {
	Color color = getColor();
	if (color == WHITE) {
		os << abbreviation;
	}
	else if (color == BLACK) {
		os << (char)tolower(abbreviation);
	}
	else {
		assert(false);
	}
}

//knight implementations
Knight::Knight(Color color, pair<int, int> location) : Piece(KNIGHT, color, location) {

}

void Knight::print(ostream& os) const {
	Color color = getColor();
	if (color == WHITE) {
		os << abbreviation;
	}
	else if (color == BLACK) {
		os << (char)tolower(abbreviation);
	}
	else {
		assert(false);
	}
}

//rook implementations
Rook::Rook(Color color, pair<int, int> location) : Piece(ROOK, color, location) {

}

void Rook::print(ostream& os) const {
	Color color = getColor();
	if (color == WHITE) {
		os << abbreviation;
	}
	else if (color == BLACK) {
		os << (char)tolower(abbreviation);
	}
	else {
		assert(false);
	}
}

//queen implementationscd 
Queen::Queen(Color color, pair<int, int> location) : Piece(QUEEN, color, location) {

}

void Queen::print(ostream& os) const {
	Color color = getColor();
	if (color == WHITE) {
		os << abbreviation;
	}
	else if (color == BLACK) {
		os << (char)tolower(abbreviation);
	}
	else {
		assert(false);
	}
}

//king implementations
King::King(Color color, pair<int, int> location) : Piece(KING, color, location) {

}

void King::print(ostream& os) const {
	Color color = getColor();
	if (color == WHITE) {
		os << abbreviation;
	}
	else if (color == BLACK) {
		os << (char)tolower(abbreviation);
	}
	else {
		assert(false);
	}
}

//ostream& operator<<(ostream& os, Piece& piece) {
//	os << pieceToChar(piece);
//	return os;
//}