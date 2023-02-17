#include "Piece.h"
using namespace std;

Piece::Piece() {
	empty = true;
	color = WHITE;
	type = EMPTY;
}

//Initialize to type and color, type cannot be empty
Piece::Piece(Type type, Color color) {
	assert(color == WHITE || color == BLACK);
	assert(type >= EMPTY && type <= KING);
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
	return (piece.getColor() == BLACK) ?
		tolower(abbreviations[piece.getType()]) :
		abbreviations[piece.getType()];
}

Piece charToPiece(char ch) {
	for (int i = EMPTY; i <= KING; i++) {
		if ((char) toupper(ch) == abbreviations[i]) {
			if (i == 0) {
				//empty piece
				Piece piece;
				return piece;
			}
			//matches
			Type type = (Type)i;
			if (isupper(ch)) {
				//white
				Piece piece(type, WHITE);
				return piece;
			}
			else {
				//black
				Piece piece(type, BLACK);
				return piece;
			}
		}
	}
	//not a valid char
	assert(false);
}

ostream& operator<< (ostream& os, const Piece& piece) {
	os << pieceToChar(piece);
	return os;
}