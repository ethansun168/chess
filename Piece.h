#pragma once
#include <string>
#include <iostream>
//Representation of a chess piece
enum Type {
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING,
	NONE
};

enum Color {
	WHITE,
	BLACK,
	NEITHER
};

class Piece {
private:
	Color color;
	Type type;
	friend std::ostream&operator<<(std::ostream& os, Piece& piece);
public:
	//Initialize to piece with no color
	Piece();
	//Initialize to piece with type and color
	Piece(Type type, Color color);
	//returns the color of piece
	Color getColor() const;
	//Gets the type
	Type getType() const;
};

//Print the piece to the output stream in the form: pieceAbbreviation [NO SPACE] Color
std::ostream& operator<<(std::ostream& os, Piece& piece);