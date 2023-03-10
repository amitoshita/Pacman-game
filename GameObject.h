#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <iostream>
#include "io.utils.h"
#include "Position.h"
#include "Color.h"
#include "utilities.h"
#include "ROWCOL.h"

class Board;
class Position;

class GameObject {
	Position obj_pos;
	Color color;
	Direction direction = Direction::RIGHT1;
	Objects figure;
public:
	GameObject();
	Position getObjPos() const;
	void setFirstPos(int row, int col);
	void setObjPos(int row, int col);
	void setObjColor(Color c);
	Color getObjColor() const;
	void setObjFigure(Objects c);
	Objects getObjFigure() const;
	Direction getObjDirection() const;
	void setObjDirection(Direction dir);
	void initObject(Color color, Objects figure, Direction diraction);
	void printObj(int row, int col);
	void moveObj(Board& GameBoard, logicalROWCOL& RandC);
	Direction diractionFromIntToChar(int d);
	void ChangeToRandDir(Board& GameBoard);
	bool CheckIfobjTouchsAWall(Board& GameBoard, logicalROWCOL& RandC);
};


#endif
