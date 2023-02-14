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

Piece::Piece(Type type, Color color) {
	setType(type);
	setColor(color);
}

Color Piece::getColor() const {
	return color;
}

Type Piece::getType() const {
	return type;
}

void Piece::setColor(Color color) {
	assert(color == WHITE || color == BLACK);
	this->color = color;
}

void Piece::setType(Type type) {
	this->type = type;
}

void Piece::print(ostream& os) const {
	os << abbreviation;
}

ostream& operator<<(ostream& os, const Piece& piece) {
	piece.print(os);
	return os;
}

//PAWN IMPLEMENTATIONS
Pawn::Pawn(Color color) : Piece(PAWN, color) {

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

//bishop implementations
Bishop::Bishop(Color color) : Piece(BISHOP, color) {

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
Knight::Knight(Color color) : Piece(KNIGHT, color) {

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
Rook::Rook(Color color) : Piece(ROOK, color) {

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
Queen::Queen(Color color) : Piece(QUEEN, color) {

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
King::King(Color color) : Piece(KING, color) {

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