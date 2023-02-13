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
	KING
};

enum Color {
	WHITE,
	BLACK
};

class Piece {
private:
	Type type;
	Color color;
	friend std::ostream& operator<<(std::ostream& os, Piece& piece);
public:
	//Initialize piece to type and color
	Piece(Type type, Color color);
	//returns the type of piece
	Type getType();
	//returns the color of piece
	Color getColor();

};
//Print the piece to the output stream in the form: pieceAbbreviation [NO SPACE] Color
std::ostream& operator<<(std::ostream& os, Piece& piece);