#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include <regex>

enum Type {
	EMPTY,
	PAWN,
	BISHOP,
	KNIGHT,
	ROOK,
	QUEEN,
	KING,
};

enum Color {
	WHITE,
	BLACK
};

const char abbreviations[] = {
	' ',
	'P',
	'B',
	'N',
	'R',
	'Q',
	'K'
};

class Piece {
private:
	Type type;
	Color color;
	bool empty;
public:
	//initialize to empty piece
	Piece();
	//Initialize to type and color, type cannot be empty
	Piece(Type type, Color color);
	//get the type
	Type getType() const;
	//get the color
	Color getColor() const;
	//set the color
	void setColor(Color color);
	//set the color
	void setType(Type type);
	//set if empty
	void setEmpty(bool empty);

	//returns if the piece is empty
	bool isEmpty() const;
};

//turn piece to char
char pieceToChar(Piece piece);

//turn a char to piece
Piece charToPiece(char ch);

Color opposite(Color color);

//print piece to os
std::ostream& operator<< (std::ostream& os, const Piece& piece);

bool operator== (const Piece& lPiece, const Piece& rPiece);