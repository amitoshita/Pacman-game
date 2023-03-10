#include "Game.h"
using std::cout;
using std::cin;
#include <algorithm>
#include <functional>
Game::Game() {}

void Game::setLevelOfTheGhost(int level) {
	levelOfTheGhost = level;
}

int Game::getLevelOfTheGhost() const {
	return levelOfTheGhost;
}

void Game::start(int argc, char** argv) {
	insertFileOpeningOP(argc, argv);
	checkAndStartOpeningChoice();
	if (load || silent) {
		RunFromFile();
	}
	else {
		menu.printMenu();
		char choice;
		cin >> choice;
		menu.CheckUserChoice(choice);
		while (choice != '3') {
			switch (choice) {
			case '1':
				RunFromFile();
				break;
			case '2':
				menu.instructions(choice);
				break;
			}
			menu.printMenu();
			cin >> choice;
			menu.CheckUserChoice(choice);
			pacman.resetPacmanLives();
			pacman.resetPacmanFood();
		}
	}
}
void Game::insertFileOpeningOP(int argc, char** argv) {
	for (int i = 0; i < argc; ++i) {
		tokens.push_back(std::string(argv[i]));
	}
}
bool Game::CMDoptionExists(const std::string& option) {
	return std::find(tokens.begin(), tokens.end(), option) 
		!= tokens.end();
}
void Game::checkAndStartOpeningChoice() {
	if (CMDoptionExists("-save")) {
		save = true;
	}
	if (CMDoptionExists("-load")) {
		load = true;
		
	}
	if (CMDoptionExists("-silent") || CMDoptionExists("-save|-load")) {
		silent = true;
	}
	else
		return;
}

void Game::loadObjStepsAndStart(bool& loadAndSlient) { //load mode- didnt finish it!
	hideCursor();
	string tmp;
	int i = 0, numOfGhost, countSteps = 0;
	bool objFound, MovePac = false, MoveGh = false, MoveFruit = false, endOfIteration = false;
	OpenScreenStepsFileREAD();
	OpenScreenResultFileREAD();
	if (!StepsFile || !ResultFile) {
		loadAndSlient = false;
		throw  "Steps or result file doesnt exist!";
	}
	else {
		while (getline(StepsFile, tmp)) {
			objFound = false;
			while (!objFound && !endOfIteration) {
				findObjectsInSTR(tmp, objFound, endOfIteration, MovePac, MoveGh, MoveFruit,
					i, numOfGhost);
			}
			GameBoard.printLegend(pacman.getPacmanLives(), pacman.getPacFood());
			if (endOfIteration) {
				moveObjectsLoadOrSilent(MovePac, MoveGh, MoveFruit, countSteps);
				endOfIteration = false;
				countSteps++;
			}
			if (!silent) {
				Sleep(5);
			}
			i = 0;
		}

		if (silent) {
			if (pacman.PacAteAllBread(GameBoard.getCountBread())) {
				checkSilent_PacmanWinBoard(countSteps);
			}
		}
		loadAndSlient = true;
	}
	StepsFile.close();
	ResultFile.close();
}

void Game::findObjectsInSTR(string tmp, bool& objFound, bool& endOfIteration,
bool& MovePac, bool& MoveGh, bool& MoveFruit, int& i, int& numOfGhost) {
	if (tmp.find("-") != std::string::npos) {
		endOfIteration = true;
	}
	if (tmp.find("Pacman") != std::string::npos) {
		setPacDir(objFound, i, tmp);
		MovePac = true;
	}
	if (tmp.find("Ghost") != std::string::npos) {
		setGHdir(objFound, i, tmp, numOfGhost);
		MoveGh = true;
	}
	if (tmp.find("Fruit") != std::string::npos)
	{
		setFruitDirAndPos(objFound, i, tmp);
		MoveFruit = true;
	}
	if (tmp.find("fruitPos") != std::string::npos) {
		GetFruitPosFromFile(i, tmp, objFound);
	}
	if (tmp.find("RemoveFruit") != std::string::npos) {
		fruit.RemoveFruit(GameBoard, StepsFile, save);
		MoveFruit = false;
	}
}
void Game::GetFruitPosFromFile(int& i, string tmp, bool& objFound) {
	i += 9;
	int R = 0, C = 0;
	R = GetNumFromChar(tmp, ' ', i);
	i++;
	C = GetNumFromChar(tmp, ' ', i);
	fruit.setObjPos(R, C);
	objFound = true;
}
void Game::moveObjectsLoadOrSilent(bool& MovePac, bool& MoveGh, bool& moveFruit, int countSteps) {
	if (MovePac) {
		pacman.moveObj(GameBoard, RandC);
		if (GameBoard.getCharFromBoard(pacman.getObjPos().GetRowPos(), pacman.getObjPos().GetColPos()) == '.') {
			pacman.addFoodCollected();
			GameBoard.setCharToBoard(' ', pacman.getObjPos().GetRowPos(), pacman.getObjPos().GetColPos()); //+
		}
	}
	if (MoveGh) {
		for (int i = 0; i < logicGHsize; i++) {
			ghosts[i].moveGhost(GameBoard, pacman, levelOfTheGhost, RandC);
			IsPacmanMeetGhost(i, countSteps);
		}
	}
	if (moveFruit) {
		fruit.moveObj(GameBoard, RandC);
	}
	MoveGh = false;
	moveFruit = false;
	MovePac = false;
}

void Game::checkSilent_PacmanDied(int& countSteps) {
	string temp, num, count;
	countSteps++;
	bool error = false;
	int REALnum = 0;
	int i = 0;
	getline(ResultFile, temp, ' ');
	if(temp.find("died") != std::string::npos){
		getline(ResultFile, num, ' ');
		REALnum = GetNumFromChar(num, '\0', i);
		if (REALnum == 1|| REALnum == 2 || REALnum == 3) {
			REALnum = 0;
			getline(ResultFile, count, '\n');
			i = 0;
			REALnum = GetNumFromChar(count, '\0', i);
			if (countSteps != REALnum) {
				error = true;
			}
		}
		else {
			error = true;
		}
	}
	else {
		ResultFile.seekg(temp.length());
	}

	if (error) {
		ResultFile.close();
		throw "ERROR: Failed in Result File. Running next file.";
	}
}
int Game::GetNumFromChar(string& string, char stopChar, int& i) {
	int num = 0;
	while (string[i] != stopChar) {
		num = (10 * num) + (string[i] - '0');
		i++;
	}
	return num;
}
void Game::setPacDir(bool& objFound, int& i, string tmp)
{
	objFound = true;
	i += 7;
	pacman.setObjDirection((Direction)tmp[i]);
}

void Game::setFruitDirAndPos(bool& objFound, int& i, string tmp) {
	objFound = true;
	int R = 0, C = 0;
	i += 5;
	fruit.setObjFigure((Objects)tmp[i]);
	i += 2;
	fruit.setObjDirection((Direction)tmp[i]);
}

void Game::setGHdir(bool& objFound, int& i, string tmp, int& numOfGhost) {
	i += 5;
	objFound = true;
	numOfGhost = tmp[i] - '0';	
	i += 2;
	ghosts[numOfGhost].setObjDirection((Direction)tmp[i]);
}

void Game::RunFromFile() {
	bool inFile;
	bool loadAndSlient;
	string const path = ".";
	if (!load && !silent) {
		menu.ghostLevelMenu();
		setLevelOfTheGhost(menu.checkGhostLevelMenu());
		RunWithOrWithoutColors();
	}
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.path().extension() == ".screen") {
			inFile = true;
			system("cls");
			logicGHsize = 0;
			pacman.resetBreadCrumbs();
			GameBoard.eraseBoard();
			GameBoard.manageScreenFile(entry.path().filename().string(), pacman, ghosts, logicGHsize, RandC, inFile);
			PrintAndRunBoard(inFile, loadAndSlient);
		}
		if (pacman.getPacmanLives() == 0)
			break;
	}
	if (!silent) {
		setTextColor(WHITE);
		checkIfUserLoseOrWin(loadAndSlient);
	}
	if (numFiles == 0){
		menu.printNoFile();
	}
}
void Game::PrintAndRunBoard(bool inFile, bool& loadAndSlient) {

	if (inFile) {
		numFiles++;
		initByColorOfBoard();
		GameBoard.printBoard(pacman, ghosts, logicGHsize, RandC);
		if (silent) {
			try
			{
				loadObjStepsAndStart(loadAndSlient);
				system("cls");
				setTextColor(WHITE);
				cout << "The silent mode is OK for this file.";
				Sleep(1300);
			}
			catch (const char* msg) {
				system("cls");
				cout << msg << std::endl;
				Sleep(1300);
			}
		}
		else if (load) {
			loadObjStepsAndStart(loadAndSlient);
		}
		else
			runTheGame();
	}
}
void Game::initByColorOfBoard() {
	if (coloredOrNOT == '1') {
		initGame(LIGHTBLUE, LIGHTMAGENTA, RED, BLUE, WHITE, GREEN);
	}
	if (coloredOrNOT == '2')
	{
		initGame(WHITE, WHITE, WHITE, WHITE, WHITE, WHITE);
	}
}

void Game::RunWithOrWithoutColors() {
	menu.printColoredMenu();
	char choice;
	cin >> choice;
	menu.CheckUserChoiceColoredMenu(choice);
	coloredOrNOT = choice;
}

void Game::initGame(Color pacColor, Color ghostColor, Color fruitColor, Color colorOfWalls, Color colorOfComments, Color colorOfBread) {
	system("cls");
	pacman.initPacman(pacColor, Objects::PACMAN, Direction::RIGHT1);
	for (int i = 0; i < logicGHsize; i++) {
		ghosts[i].initObject(ghostColor, Objects::GHOST, Direction::RIGHT1);
	}
	fruit.setObjColor(fruitColor);
	GameBoard.initBoard(colorOfWalls, colorOfComments, colorOfBread, pacman, RandC);
}


void Game::runTheGame() {
	hideCursor();
	char key = 0, dir = -1;
	int countSteps = 0;
	bool PacMove = false, GhostMove = true, FruitMove = false;
	if (save) {
		OpenScreenStepsFileWRITE();
		OpenScreenResultFileWRITE();
	}
	while (pacman.getPacmanLives() > 0 && !pacman.PacAteAllBread(GameBoard.getCountBread())) {
		countSteps++;
		if (_kbhit()) {
			key = _getch();
			if (key == ESC) {
				pauseAllGame(key, GameBoard.getLegend().GetRowPos(), GameBoard.getLegend().GetColPos());
			}
			else if ((dir = pacman.getDirection(key)) != -1) {
				pacman.setObjDirection((Direction)dir);
			}
		}
		if (dir != -1) {
			ManagePacMove(dir, countSteps, FruitMove);
		}
		if (GhostMove) {
			ManageGhostMove(countSteps, FruitMove);
			ManageFruitMove(FruitMove);
			GhostMove = false;
			setTextColor(GameBoard.getColorOfComments());
		}
		else {
			GhostMove = true;
		}
		Sleep(160);
		GameBoard.printLegend(pacman.getPacmanLives(), pacman.getPacFood());
		StepsFile << "-" << std::endl;
	
	}
	if (pacman.PacAteAllBread(GameBoard.getCountBread()) && save) {
		ResultFile << "win: " << countSteps << std::endl;
		StepsFile.flush();
	}
	if (save) {
		StepsFile.close();
		ResultFile.close();
	}
}
void Game::OpenScreenResultFileWRITE() {
	string name = CreateResultFileName();
	ResultFile.open(name, std::ios_base::out, std::ios_base::trunc);
}
void Game::OpenScreenStepsFileWRITE() {
	string name = CreateStepsFileName();
	StepsFile.open(name, std::ios_base::out, std::ios_base::trunc);
}
void Game::OpenScreenResultFileREAD() {
	string name = CreateResultFileName();
	ResultFile.open(name, std::ios_base::in);
}
void Game::OpenScreenStepsFileREAD() {
	string name = CreateStepsFileName();
	StepsFile.open(name, std::ios_base::in);
}
string Game::CreateStepsFileName() {
	string name = "Steps";
	char num = numFiles + '0';
	name.push_back(num);
	name += ".txt";
	return name;
}
string Game::CreateResultFileName() {
	string name = "Result";
	char num = numFiles + '0';
	name.push_back(num);
	name += ".txt";
	return name;
}
void Game::resetPacAfterMetGhost() {
	pacman.setPacmanLives();
	pacman.setObjPos(pacman.getObjPos().GetStartRowPos(), pacman.getObjPos().GetStartColPos());
	pacman.getObjPos().draw(pacman.getObjFigure());
	pacman.setObjDirection(Direction::STOP1);
}

void Game::IsPacmanMeetGhost(int i, int countSteps) {
	if (pacman.getObjPos().GetRowPos() == ghosts[i].getObjPos().GetRowPos() &&
		pacman.getObjPos().GetColPos() == ghosts[i].getObjPos().GetColPos())
	{
		resetPacAfterMetGhost();
		if (save) {
			ResultFile << "died " << 3 - pacman.getPacmanLives() << " " << countSteps << std::endl;
		}
		if (silent) {
			checkSilent_PacmanDied(countSteps);
		}
	}
}

void Game::ManagePacMove(char key, int countSteps, bool& FruitMove) {

	char NextKey = ReturnNextPacmanChar(key);
	bool PacMove = true;
	if (NextKey == '#') {
		PacMove = false;
	}
	if (GameBoard.getCharFromBoard(pacman.getObjPos().GetRowPos(), pacman.getObjPos().GetColPos()) == '.') {
		pacman.addFoodCollected();
		GameBoard.setCharToBoard(' ', pacman.getObjPos().GetRowPos(), pacman.getObjPos().GetColPos()); //+
	}
	if (PacMove && !pacman.PacAteAllBread(GameBoard.getCountBread())) {
		pacman.moveObj(GameBoard, RandC);
		if (IsPacmanMeetFruit()) {
			pacman.addFruitCollected((char)fruit.getObjFigure());
			fruit.RemoveFruit(GameBoard, StepsFile, save);
			FruitMove = false;
		}
		if (save)
		{
			StepsFile << "Pacman:" << (char)pacman.getObjDirection() << std::endl;
			StepsFile.flush();
		}
		setTextColor(GameBoard.getColorOfComments());
	}
}


bool Game::IsPacmanMeetFruit() {
	if (pacman.getObjPos().GetRowPos() == fruit.getObjPos().GetRowPos() &&
		pacman.getObjPos().GetColPos() == fruit.getObjPos().GetColPos())
		return true;
	return false;
}

char Game::ReturnNextPacmanChar(char key) {
	char res;
	Position currPos = pacman.getObjPos();
	res = GameBoard.checkAndReturnNextMove((Direction)pacman.getDirection(key), currPos.GetRowPos(), currPos.GetColPos(), RandC);
	return res;
}

char Game::ReturnNextGhostChar(int i) {
	char res;
	Position currPos = ghosts[i].getObjPos();
	res = GameBoard.checkAndReturnNextMove(ghosts[i].getObjDirection(), currPos.GetRowPos(), currPos.GetColPos(), RandC);
	return res;
}

void Game::ManageGhostMove(int countSteps, bool& FruitMove) {
	for (int i = 0; i < logicGHsize; i++) {
		ghosts[i].moveGhost(GameBoard, pacman, levelOfTheGhost, RandC);
		IsPacmanMeetGhost(i, countSteps);
		if (save)
		{
			StepsFile << "Ghost" <<  i << ":" << (char)ghosts[i].getObjDirection() << std::endl;
			StepsFile.flush();
		}
	}
	IsGhostmeetGhost();
	checkIfGhostMeetFruit(FruitMove);
}

void Game::IsGhostmeetGhost() {
	for (int i = 0; i < logicGHsize; i++) {
		for (int j = i + 1; j < logicGHsize; j++) {
			if ((ghosts[i].getObjPos().GetRowPos() == ghosts[j].getObjPos().GetRowPos()) &&
				(ghosts[i].getObjPos().GetColPos() == ghosts[j].getObjPos().GetColPos()))
				ghosts[i].ChangeToRandDir(GameBoard);
		}
	}
}

void Game::checkIfGhostMeetFruit(bool& FruitMove) {
	for (int i = 0; i < logicGHsize; i++) {
		if ((ghosts[i].getObjPos().GetColPos() == fruit.getObjPos().GetColPos())
			&& (ghosts[i].getObjPos().GetRowPos() == fruit.getObjPos().GetRowPos())) {
			fruit.RemoveFruit(GameBoard, StepsFile, save);
			FruitMove = false;
		}
	}
}

void Game::ManageFruitMove(bool& move) {
	
	fruit.MoveFruit(GameBoard, pacman, ghosts, logicGHsize, RandC, move, StepsFile, save);
	if (save && move) {
		StepsFile << "Fruit" << (char)fruit.getObjFigure() << ":" << (char)fruit.getObjDirection() << std::endl;
		StepsFile.flush();
	}
}

void Game::pauseAllGame(char& key, int rowLegend, int colLegend) {
	key = ' ';
	gotoxy(16, 10);
	gotoxy(colLegend + 1, rowLegend + 2);
	setTextColor(GameBoard.getColorOfComments());
	cout << "PAUSED! Press ESC";
	while (key != ESC)
	{
		key = _getch();
	}
	gotoxy(colLegend + 1, rowLegend + 2);
	cout << "                 ";
	setTextColor(WHITE);
}

void Game::checkIfUserLoseOrWin(bool& loadAndSlient) {
	if (pacman.getPacmanLives() == 0) {
		menu.printLossMenu();
		Sleep(1000);
	}
	else {
		if (loadAndSlient) {
			menu.printVictoryMenu();
			Sleep(1000);
		}
	}
}

void Game::checkSilent_PacmanWinBoard(int& countSteps) {
	string temp, count;
	bool error = false;
	int i = 0;
	int num = 0;
	getline(ResultFile, temp, ' ');
	if (temp.compare("win")) {
		getline(ResultFile, count, ' ');
		num = GetNumFromChar(count, '\n', i);
		if (num != countSteps) { 
			error = true;
		}
	}
	else {
		error = true;
	}

	if (error) {
		ResultFile.close();
		throw "ERROR: Failed in Result File. Running next file.";
	}
}