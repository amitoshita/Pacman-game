#include "Ghost.h"
#include <math.h>

Ghost::Ghost() {

}

Ghost::~Ghost() {

}

void Ghost::moveGhost(Board& GameBoard, Pacman& pacman, int levelOfTheGhost, logicalROWCOL RandC)
{
	switch (levelOfTheGhost)
	{
	case 0:
		moveObj(GameBoard, RandC);
		break;
	case 1:
		BESTmove(GameBoard, pacman, RandC);
		break;
	case 2:
		GOODmove(GameBoard, pacman, RandC);
		break;
	case 3:
		NOVICEmove(GameBoard, RandC);
		break;
	}
}


void Ghost::touchTheGhostAndGoBack() {
	Direction direction = getObjDirection();
	switch (direction) {
	case Direction::LEFT1 : // LEFT
	case Direction::LEFT2: // LEFT
		setObjDirection(Direction::LEFT1);
		break;
	case Direction::DOWN1: // DOWN
	case Direction::DOWN2: // DOWN
		setObjDirection(Direction::DOWN1);
		break;
	case Direction::UP1: // UP
	case Direction::UP2: // UP
		setObjDirection(Direction::UP1);
		break;
	case Direction::RIGHT1: // RIGHT
	case Direction::RIGHT2: // RIGHT
		setObjDirection(Direction::RIGHT1);
		break;
	}
}

bool Ghost::isNextGhostMoveValid(int row, int col, Board& board) {

	char target = board.getCharFromBoard(row, col);
	if (target == '$' || target == '#') {
		return false;
	}
	return true;
}

void Ghost::FindPathToPacman(Board& board, Pacman& pacman, logicalROWCOL RandC) { // TO SHRINK THIS FUNCTION!
	char nextMove;
	int pos = -1;
	double min = ((int)MaxRowCol::MAXCOL * (int)MaxRowCol::MAXCOL) + ((int)MaxRowCol::MAXROW * (int)MaxRowCol::MAXROW);
	double dist = -1;
	if (isNextGhostMoveValid(getObjPos().GetRowPos(), getObjPos().GetColPos() - 1, board)) {
		dist = pow(pacman.getObjPos().GetRowPos() - getObjPos().GetRowPos(), 2) + pow((pacman.getObjPos().GetColPos()) - (getObjPos().GetColPos() - 1), 2);
		if (min > dist) {
			min = dist;
			setObjDirection(Direction::LEFT1);
		}
	}
	if (isNextGhostMoveValid(getObjPos().GetRowPos(), getObjPos().GetColPos() + 1, board)) {
		dist = pow(pacman.getObjPos().GetRowPos() - getObjPos().GetRowPos(), 2) + pow(pacman.getObjPos().GetColPos() - (getObjPos().GetColPos() + 1), 2);
		if (min > dist) {
			min = dist;
			setObjDirection(Direction::RIGHT1);
		}
	}
	if (isNextGhostMoveValid(getObjPos().GetRowPos() - 1, getObjPos().GetColPos(), board)) {
		dist = pow(pacman.getObjPos().GetRowPos() - (getObjPos().GetRowPos() - 1), 2) + pow(pacman.getObjPos().GetColPos() - getObjPos().GetColPos(), 2);
		if (min > dist) {
			min = dist;
			setObjDirection(Direction::UP1);
		}
	}
	if (isNextGhostMoveValid(getObjPos().GetRowPos() + 1, getObjPos().GetColPos(), board)) {
		dist = pow((pacman.getObjPos().GetRowPos()) - (getObjPos().GetRowPos() + 1), 2)
			+ pow(pacman.getObjPos().GetColPos() - getObjPos().GetColPos(), 2);
		if (min > dist) {
			min = dist;
			setObjDirection(Direction::DOWN1);
		}
	}
}

void Ghost::BESTmove(Board& board, Pacman& pacman, logicalROWCOL RandC) {
	FindPathToPacman(board, pacman, RandC);

	moveObj(board, RandC);
}

void Ghost::GOODmove(Board& board, Pacman& pacman, logicalROWCOL RandC) {
	if (FiveMovesCnt == 5) {
		FiveMovesCnt = 0;
		countGhostMoves = 0;
		changeToRandomDir = false;
		randNumOfMoveToChasePacman = false;
	}
	if (!randNumOfMoveToChasePacman) {
		countRandGhostMoves = rand() % 20;
		randNumOfMoveToChasePacman = true;
	}
	if (countRandGhostMoves == countGhostMoves) {
		if (!changeToRandomDir) {
			ChangeToRandDir(board);
			changeToRandomDir = true;
		}
		CheckIfobjTouchsAWall(board, RandC);
		moveObj(board, RandC);
		FiveMovesCnt++;
	}
	if (countRandGhostMoves != countGhostMoves) {
		FindPathToPacman(board, pacman, RandC);
		moveObj(board, RandC);
		countGhostMoves++;
	}
}

void Ghost::NOVICEmove(Board& board, logicalROWCOL RandC) {

	if (countGhostMoves == 20 || !changeToRandomDir) {
		ChangeToRandDir(board);
		changeToRandomDir = true;
		countGhostMoves = 0;
	}
	CheckIfobjTouchsAWall(board, RandC);
	moveObj(board, RandC);
	countGhostMoves++;

}
