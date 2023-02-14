#include "Piece.h"
#include <cassert>
using namespace std;

//const char typeAbbreviations[] = {
//	'P',
//	'N',
//	'B',
//	'R',
//	'Q',
//	'K',
//	' '
//};
//
//char pieceToChar(Piece piece) {
//	for (int i = PAWN; i <= NONE; i++) {
//		if (i == piece.getType()) {
//			if (piece.getColor() == WHITE) {
//				return typeAbbreviations[i];
//			}
//			else if(piece.getColor() == BLACK) {
//				return (char)tolower(typeAbbreviations[i]);
//			}
//			else if(piece.getColor() == NEITHER) {
//				return ' ';
//			}
//			else {
//				assert(false);
//			}
//		}
//	}
//	assert(false);
//}

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

<<<<<<< HEAD
//BISHOP implementations
Bishop::Bishop(Color color) : Piece(BISHOP, color) {
=======
//bishop implementations
Bishop::Bishop(Color color, pair<int, int> location) : Piece(BISHOP, color, location) {
>>>>>>> f7d4bb2a1dc49c36f1c9f1ddf30a4a7fb8f7f745

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