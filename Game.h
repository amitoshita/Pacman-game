#ifndef _GAME_H_
#define _GAME_H_
#include <stdbool.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include "io.utils.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Position.h"
#include "Board.h"
#include "utilities.h"
#include "Menu.h"
#include "Fruit.h"
#include "ROWCOL.h"

class Game {
	Menu menu;
	Pacman pacman;
	Ghost ghosts[4];
	std::fstream StepsFile, ResultFile;
	int logicGHsize = 0;
	int levelOfTheGhost = 0;
	int coloredOrNOT = '1';
	Fruit fruit;
	Board GameBoard;
	logicalROWCOL RandC;
	int numFiles = 0;
	std::vector <std::string> tokens; //File opening options
	bool silent = false, save = false, load = false; //Game opening mode

public:
	Game();
	void setLevelOfTheGhost(int level);
	int getLevelOfTheGhost() const;
	void start(int argc, char** argv);
	void checkAndStartOpeningChoice();
	void insertFileOpeningOP(int argc, char** argv);
	void checkSilent_PacmanWinBoard(int& countSteps);
	bool CMDoptionExists(const std::string& option);
	void RunFromFile();
	void initByColorOfBoard();
	void runTheGame();
	void ManageGhostMove(int countSteps, bool& move);
	bool IsPacmanMeetFruit();
	void checkIfGhostMeetFruit(bool& FruitMove);
	void OpenScreenStepsFileWRITE();
	void moveObjectsLoadOrSilent(bool& MovePac, bool& MoveGh, bool& moveFruit, int countSteps);
	char ReturnNextGhostChar(int i);
	string CreateStepsFileName();
	void loadObjStepsAndStart(bool& loadAndSlient);
	void OpenScreenResultFileWRITE();
	void OpenScreenResultFileREAD();
	void OpenScreenStepsFileREAD();
	void setPacDir(bool& objFound, int& i, string tmp);
	void setFruitDirAndPos(bool& objFound, int& i, string tmp);
	void setGHdir(bool& objFound, int& i, string tmp, int& numOfGhost);
	char ReturnNextPacmanChar(char key);
	void PrintAndRunBoard(bool inFile, bool& loadAndSlient);
	int GetNumFromChar(string& string, char stopChar, int& i);
	void checkSilent_PacmanDied(int& countSteps);
	void ManagePacMove(char key, int countSteps, bool& FruitMove);
	void initGame(Color pacColor, Color ghostColor, Color fruitColor, Color colorOfWalls, Color colorOfComments, Color colorOfBread);
	void pauseAllGame(char& key, int rowLegend, int colLegend);
	void IsGhostmeetGhost();
	void IsPacmanMeetGhost(int i, int countSteps);
	void RunWithOrWithoutColors();
	void checkIfUserLoseOrWin(bool& loadAndSlient);
	void resetPacAfterMetGhost();
	void ManageFruitMove(bool& move);
	void findObjectsInSTR(string tmp, bool& objFound, bool& endOfIteration,
		bool& MovePac, bool& MoveGh, bool& MoveFruit, int& i, int& numOfGhost);
	string CreateResultFileName();
	void GetFruitPosFromFile(int& i, string tmp, bool& objFound);
};

#endif