#include "Fruit.h"
#include "ROWCOL.h"
using std::cout;

Objects Fruit::GetRandomFigure() {
	int RandomFruit;
	int range = 9 - 5 + 1;
	RandomFruit = rand() % range + 5;
	return (Objects)(RandomFruit + '0');
}

void Fruit::MoveFruit(Board& GameBoard, Pacman& pacman, Ghost ghosts[], int ghSIZE, logicalROWCOL& RandC, bool& move, std::fstream& StepsFile, bool save) {
	pauseCounter++;
	if (pauseCounter >= 40)
	{
		if (!putFruit) {
			putFruitInARandPlace(pacman, ghosts, ghSIZE, GameBoard, RandC, StepsFile, save);
			putFruit = true;
		}
		CheckIfobjTouchsAWall(GameBoard, RandC);
		moveObj(GameBoard, RandC);
		move = true;
		moveCounter++;
		if (moveCounter == 40) {
			RemoveFruit(GameBoard, StepsFile, save);
			move = false;
		}
	}
}

void Fruit::RemoveFruit(Board& GameBoard, std::fstream& StepsFile, bool save) {
	gotoxy(getObjPos().GetColPos(), getObjPos().GetRowPos());
	setTextColor(WHITE);
	cout << GameBoard.getCharFromBoard(getObjPos().GetRowPos(), getObjPos().GetColPos());
	if (save) {
		StepsFile << "RemoveFruit" << std::endl;
	}
	putFruit = false;
	moveCounter = 0;
	pauseCounter = 0;
}

void Fruit::putFruitInARandPlace(Pacman& pacman, Ghost ghosts[], int ghSIZE, Board& GameBoard, logicalROWCOL& RandC, std::fstream& StepsFile, bool save) {
	int currRow, currCol;
	setRandRowAndCol(currRow, currCol, GameBoard, pacman, ghosts, ghSIZE, RandC);
	setObjPos(currRow, currCol);
	if (save) {
		StepsFile << "fruitPos" << " " << getObjPos().GetRowPos() << " " << getObjPos().GetColPos() << " " << std::endl;
	}
	initFruit(this->getObjColor(), GetRandomFigure(), Direction::UP1);
	setTextColor(WHITE);
	ChangeToRandDir(GameBoard);
}
void Fruit::initFruit(Color color, Objects currfigure, Direction diraction) {
	setObjDirection(diraction);
	setObjColor(color);
	setObjFigure(currfigure);
}
void Fruit::setRandRowAndCol(int& currRow, int& currCol, Board& GameBoard, Pacman& pacman, Ghost ghosts[], int ghSIZE, logicalROWCOL& RandC) {
	currRow = rand() % (RandC.getlogicR() - 2);
	currCol = rand() % (RandC.getlogicC() - 2);
	while (GameBoard.getCharFromBoard(currRow, currCol) == '#' || IsFruitMeetGhost(ghosts, ghSIZE) || IsFruitMeetPacman(pacman))
	{
		currRow = rand() % (RandC.getlogicR() - 2);
		currCol = rand() % (RandC.getlogicC() - 2);
	}
}

bool Fruit::IsFruitMeetGhost(Ghost ghosts[], int ghSIZE) {
	for (int i = 0; i < ghSIZE; i++) {
		if (getObjPos().GetRowPos() == ghosts[i].getObjPos().GetRowPos() &&
			getObjPos().GetColPos() == ghosts[i].getObjPos().GetColPos())
			return true;
	}
	return false;
}

bool Fruit::IsFruitMeetPacman(Pacman& pacman) {
	if (getObjPos().GetRowPos() == pacman.getObjPos().GetRowPos() &&
		getObjPos().GetColPos() == pacman.getObjPos().GetColPos())
		return true;
	return false;
}