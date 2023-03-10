#include "GameObject.h"
#include "Board.h"
#include "Position.h"
using std::cout;

GameObject::GameObject() {

}

Position GameObject::getObjPos() const {
	return obj_pos;
}

void GameObject::setObjColor(Color c) {
	color = c;
}

Color GameObject::getObjColor() const {
	return color;
}

void GameObject::setObjFigure(Objects c) {
	figure = c;
}

Objects GameObject::getObjFigure() const {
	return figure;
}

Direction GameObject::getObjDirection() const {
	return direction;
}

void GameObject::setObjDirection(Direction dir) {
	direction = dir;
}

void GameObject::setFirstPos(int row, int col) {
	obj_pos.setFirstPosition(row, col);
}

void GameObject::setObjPos(int row, int col) {
	obj_pos.setPosition(row, col);
}

void GameObject::initObject(Color color, Objects figure, Direction diraction) {
	setObjDirection(diraction);
	setObjColor(color);
	setObjFigure(figure);
}

void GameObject::printObj(int row, int col) {
	setTextColor(color);
	getObjPos().draw(figure);
	setTextColor(WHITE);
}

void GameObject::moveObj(Board& GameBoard, logicalROWCOL& RandC) {
	int prevRow = obj_pos.GetRowPos();
	int prevCol = obj_pos.GetColPos();
		obj_pos.updateMove(direction, getObjFigure(), RandC, GameBoard);
		if (prevCol != obj_pos.GetColPos() || prevRow != obj_pos.GetRowPos()) {
			gotoxy(prevCol, prevRow);
			setTextColor(GameBoard.getColorOfBread());
			cout << GameBoard.getCharFromBoard(prevRow, prevCol);
		}
		setTextColor(getObjColor());
		obj_pos.draw(figure);

}

void GameObject::ChangeToRandDir(Board& GameBoard) {
	int d = rand() % 4;
	Direction dir = diractionFromIntToChar(d);
	while (dir == getObjDirection()) {
		d = rand() % 4;
		dir = diractionFromIntToChar(d);
	}
	setObjDirection(dir);
}

Direction GameObject::diractionFromIntToChar(int d) {
	switch (d) {
	case 0: // LEFT
		return Direction::LEFT1;
	case 1: // UP
		return Direction::UP1;
	case 2: // RIGHT
		return Direction::RIGHT1;
	case 3: // DOWN
		return Direction::DOWN1;
	}
}


bool GameObject::CheckIfobjTouchsAWall(Board& GameBoard, logicalROWCOL& RandC) {
	bool res = false;
	char nextMove = GameBoard.checkAndReturnNextMove(getObjDirection(), getObjPos().GetRowPos(), getObjPos().GetColPos(), RandC);
	while (nextMove == '#' || GameBoard.checkAndReturnNextMove(getObjDirection(), getObjPos().GetRowPos(), getObjPos().GetColPos(), RandC) == -1)
	{
		res = true;
		ChangeToRandDir(GameBoard);
		nextMove = GameBoard.checkAndReturnNextMove(getObjDirection(), getObjPos().GetRowPos(), getObjPos().GetColPos(), RandC);
	}
	return res;
}