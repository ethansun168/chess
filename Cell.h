#pragma once
#include <string>
int const BOARD_SIZE = 8;
class Cell {
private:
	char file;
	int rank;
public:
	//initializes the cell to 'a', 1
	Cell();

	//initialize the cell to file and rank
	Cell(char file, int rank);

	//returns the file of the cell
	char getFile() const;

	//returns the rank of the cell
	int getRank() const;

	//sets the file of the cell
	void setFile(char file);

	//sets the rank of the cell
	void setRank(int rank);

	//checks if the cell is a valid cell
	//valid cell means 1 <= rank <= 8 and a <= file <= h
	bool isValid() const;

	//convert cell to row and col for the board
	//requires cell to be a valid cell
	std::pair<int, int> toBoard();

	//do not check if it is a valid cell
	//add num to file and return the number of cells starting from 'a'
	int addFile(int num);

	//do not 
	//add num to rank and return the number of cells starting from 1
	int addRank(int num);
};

