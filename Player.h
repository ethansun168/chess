#pragma once
#include "Piece.h"

class Player {
private:
	bool canCastle;
public:
	/* Initialized a player, requires a color input */
	Player(Color color);
	/* Returns whether player can castle */
	bool getCanCastle() const;
	/* Sets bool canCastle to the inputted value */
	void setCanCastle(bool canCastleArgument);
};
