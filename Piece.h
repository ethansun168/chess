#pragma once
#include <iostream>
#include <string>
enum Type {
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

char abbreviations[] = {
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
public:
	//Initialize to type and color
	Piece(Type type, Color color);
	//get the type
	Type getType() const;
	//get the color
	Color getColor() const;
};

//print piece to os
std::ostream& operator<< (std::ostream& os, Piece& piece);