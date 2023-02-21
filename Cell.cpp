#include "Cell.h"
#include <cassert>
using namespace std;

Cell::Cell() {
	file = 'a';
	rank = 1;
}

Cell::Cell(char file, int rank) {
	this->file = file;
	this->rank = rank;
}

char Cell::getFile() const {
	return file;
}

int Cell::getRank() const {
	return rank;
}

void Cell::setFile(char file) {
	this->file = file;
	assert(isValid());
}

void Cell::setRank(int rank) {
	this->rank = rank;
	assert(isValid());
}

bool Cell::isValid() const {
	return 1 <= rank && 8 >= rank && 'a' <= file && 'h' >= file;
}

pair<int, int> Cell::toBoard() {
	assert(isValid());
	//e5 -> [3][4]
	//cell.rank = row = 5 -> 3
	//cell.file = col = e -> 4
	pair<int, int> boardRowCol = { BOARD_SIZE - rank, file - 'a' };
	return boardRowCol;
}

int Cell::addFile(int num) {
	return file - 'a' + 1 + num;
}

int Cell::addRank(int num) {
	return rank + num;
}