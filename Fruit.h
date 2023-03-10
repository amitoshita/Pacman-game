#ifndef _FRUIT_H_
#define _FRUIT_H_

#include "Board.h"
#include "Color.h"
#include "GameObject.h"
#include "Pacman.h"
#include "utilities.h"
#include "Ghost.h"
#include <vector>
#include "ROWCOL.h"
using std::vector;
class Board;
class Pacman;
class Positon;
class Fruit : public GameObject {
private:
	int pauseCounter = 0;
	int moveCounter = 0;
	bool putFruit = false;
	
public:
	Objects GetRandomFigure();
	void MoveFruit(Board& GameBoard, Pacman& pacman, Ghost ghosts[], int ghSIZE, logicalROWCOL& RandC, bool& move, std::fstream& StepsFile, bool save);
	void putFruitInARandPlace(Pacman& pacman, Ghost ghosts[], int ghSIZE, Board& GameBoard, logicalROWCOL& RandC, std::fstream& StepsFile, bool save);
	void setRandRowAndCol(int& currRow, int& currCol, Board& GameBoard, Pacman& pacman, Ghost ghosts[], int ghSIZE, logicalROWCOL& RandC);
	bool IsFruitMeetGhost(Ghost ghosts[], int ghSIZE);
	bool IsFruitMeetPacman(Pacman& pacman);
	void RemoveFruit(Board& GameBoard, std::fstream& StepsFile, bool save);
	void initFruit(Color color, Objects currfigure, Direction diraction);
};

#endif

