#pragma once
#include <string>
#include <iostream>
#include <vector>
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

enum Move {
	VALID,
	ERROR
};

class Piece {
private:
	Color color;
	Type type;
	char abbreviation = ' ';
	std::pair<int, int> location;
	friend std::ostream&operator<<(std::ostream& os, const Piece& piece);
public:
	//Initialize to piece with no color
	Piece();
	//Initialize piece and color and location
	Piece(Type type, Color color, std::pair<int, int> location);
	//returns the color of piece
	Color getColor() const;
	//Gets the type
	Type getType() const;
	//gets the location of the piece
	std::pair<int, int> getLocation();
	//set color
	void setColor(Color color);
	//set type
	void setType(Type type);
	//sets the location
	void setLocation(std::pair<int, int> location);
	//print the piece
	virtual void print(std::ostream& os) const;
<<<<<<< HEAD
	virtual Move move();
	//~Piece();
=======
	//virtual destructor
	virtual ~Piece() {};
>>>>>>> f7d4bb2a1dc49c36f1c9f1ddf30a4a7fb8f7f745
};

std::ostream& operator<<(std::ostream& os, const Piece& piece);

class Pawn : public Piece {
private:
	char abbreviation = 'P';
public:
	//Initialize to Pawn and Color
	Pawn(Color color, std::pair<int, int> location);
	//print piece to os
	void print(std::ostream& os) const;

	Move move();
};

class Knight : public Piece {
private:
	char abbreviation = 'N';
public:
	//initialize to knight and color
	Knight(Color color, std::pair<int, int> location);
	//print piece to os
	void print(std::ostream& os) const;
};

class Bishop : public Piece {
private:
	char abbreviation = 'B';
public:
	//initialize to bishop and color
	Bishop(Color color, std::pair<int, int> location);
	//print piece to os
	void print(std::ostream& os) const;
};

class Rook : public Piece {
private:
	char abbreviation = 'R';
public:
	//initialize to rook and color
	Rook(Color color, std::pair<int, int> location);
	//print piece to os
	void print(std::ostream& os) const;
};

class Queen : public Piece {
private:
	char abbreviation = 'Q';
public:
	//initialize to queen and color
	Queen(Color color, std::pair<int, int> location);
	//print piece to os
	void print(std::ostream& os) const;
};

class King : public Piece {
private:
	char abbreviation = 'K';
public:
	//initialize to king and color
	King(Color color, std::pair<int, int> location);
	//print piece to os
	void print(std::ostream& os) const;
};