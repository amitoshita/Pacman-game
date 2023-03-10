#ifndef _GHOST_H_
#define _GHOST_H_
#include "io.utils.h"
#include "Position.h"
#include "Board.h"
#include "GameObject.h"
#include "Pacman.h"
#include "ROWCOL.h"
#include "utilities.h"

class Board;
class Pacman;
class GameObject;
class Ghost : public GameObject {
	bool bread = true;
	int countGhostMoves = 0;
	int countRandGhostMoves = 0;
	int FiveMovesCnt = 0;
	bool randNumOfMoveToChasePacman = false;
	bool changeToRandomDir = false;
	bool randArandomNumOfMove = false;
public:
	Ghost();
	void BESTmove(Board& board, Pacman& pacman, logicalROWCOL RandC);
	void GOODmove(Board& board, Pacman& pacman, logicalROWCOL RandC);
	void NOVICEmove(Board& board, logicalROWCOL RandC);
	void moveGhost(Board& GameBoard, Pacman& pacman, int levelOfTheGhost, logicalROWCOL RandC);
	void touchTheGhostAndGoBack();
	bool isNextGhostMoveValid(int row, int col, Board& board);
	void FindPathToPacman(Board& board, Pacman& pacman, logicalROWCOL RandC);
	~Ghost();
};

#endif