#ifndef _POSITION_H_
#define _POSITION_H_

#include <iostream>
#include "io.utils.h"
#include "ROWCOL.h"
#include "utilities.h"
enum { ESC = 27 };
class Board;
class Position {
	int x;
	int y;
	int firstROW;
	int firstCOL;
public:

	void draw(Objects ch);
	void updateMove(Direction dir, Objects figure, logicalROWCOL& RandC, Board& board);
	void setFirstPosition(int x, int y) {
		firstROW = x;
		firstCOL = y;
	}
	void setPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int GetRowPos() const {
		return x;
	}
	int GetColPos() const {
		return y;
	}
	int GetStartRowPos() const {
		return firstROW;
	}
	int GetStartColPos() const {
		return firstCOL;
	}
};

#endif
