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
	char abbreviation = ' ';
	friend std::ostream&operator<<(std::ostream& os, const Piece& piece);
public:
	//Initialize to piece with no color
	Piece();
	//Initialize piece and color
	Piece(Type type, Color color);
	//returns the color of piece
	Color getColor() const;
	//Gets the type
	Type getType() const;
	//set color
	void setColor(Color color);
	//set type
	void setType(Type type);
	virtual void print(std::ostream& os) const;
	virtual ~Piece() {};
};

std::ostream& operator<<(std::ostream& os, const Piece& piece);

class Pawn : public Piece {
private:
	char abbreviation = 'P';
public:
	//Initialize to Pawn and Color
	Pawn(Color color);
	//print piece to os
	void print(std::ostream& os) const;
};

class Knight : public Piece {
private:
	char abbreviation = 'N';
public:
	//initialize to knight and color
	Knight(Color color);
	//print piece to os
	void print(std::ostream& os) const;
};

class Bishop : public Piece {
private:
	char abbreviation = 'B';
public:
	//initialize to bishop and color
	Bishop(Color color);
	//print piece to os
	void print(std::ostream& os) const;
};

class Rook : public Piece {
private:
	char abbreviation = 'R';
public:
	//initialize to rook and color
	Rook(Color color);
	//print piece to os
	void print(std::ostream& os) const;
};

class Queen : public Piece {
private:
	char abbreviation = 'Q';
public:
	//initialize to queen and color
	Queen(Color color);
	//print piece to os
	void print(std::ostream& os) const;
};

class King : public Piece {
private:
	char abbreviation = 'K';
public:
	//initialize to king and color
	King(Color color);
	//print piece to os
	void print(std::ostream& os) const;
};