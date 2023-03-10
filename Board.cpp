#include "Board.h"

using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::fstream;
#include <cstring>
using std::strcpy;
using std::strlen;

Board::Board() {

}

Board::~Board() {

}

int Board::getROW(logicalROWCOL RandC) const {
	return RandC.getlogicR();
}

int Board::getCol(logicalROWCOL RandC) const {
	return RandC.getlogicC();
}

void Board::setCountBread(int count) {
	countBread = count;
}

void Board::setROW(int row, logicalROWCOL& RandC) {
	RandC.setlogicR(row);
}

void Board::setCOL(int col, logicalROWCOL& RandC) {
	RandC.setlogicC(col);
}

void Board::setColorOfWalls(Color c) {
	colorOfWalls = c;
}

void Board::setColorOfComments(Color c) {
	colorOfComments = c;
}

void Board::setColorOfBread(Color c) {
	colorOfBread = c;
}

Color Board::getColorOfWalls() const {
	return colorOfWalls;
}

Color Board::getColorOfComments() const {
	return colorOfComments;
}

Color Board::getColorOfBread() {
	return colorOfBread;
}

void Board::setLegend(int row, int col) {
	Legend.setPosition(row, col);
}

void Board::fromFileToBoard(string fileName, Pacman& pacman, Ghost ghosts[], int& logGHsize, logicalROWCOL& RandC, bool& inFile) {
	int rows = 1;
	ifstream file;
	string tmp;
	file.open(fileName);
	if (!file) {
		cout << "Error open this file" << endl;
	}

	getline(file, tmp);
	if ((int)tmp.length() != 0) { // check if not 1 becuse /0
		strcpy(board[0], tmp.c_str());
		int add = checkFile.LegendInFirstLine(board[0], Legend);
		setCOL((int)tmp.length() + add, RandC);
		// Read all lines 
		while (!file.eof() && rows < (int)MaxRowCol::MAXROW) {
			getline(file, tmp);
			strcpy(board[rows], tmp.c_str());
			rows++;
		}
		setROW(rows, RandC);
		file.close();
		if (!checkNumOfPacGhostAndLegend(RandC)) {// evreything is OK
			changeFileBoardToGameBoard(pacman, ghosts, logGHsize, RandC);
			bool leg1 = checkFile.checkLocationOfLegend(Legend.GetRowPos(), Legend.GetColPos(), RandC.getlogicR(), RandC.getlogicC());
			bool leg2 = checkFile.checkLegendPacAndGhost(Legend, pacman.getObjPos(), ghosts, logGHsize);
			if (!leg1 || leg2) {
				throw "ERROR: Failed in legend propriety position. Running next file.";
			}
		}
		else
			inFile = false;
	}
	else {
		/*checkFile.thereIsNothingToRead();*/
		throw "ERROR: File is empty. Running next file.";
	}
}

bool Board::checkNumOfPacGhostAndLegend(logicalROWCOL& RandC) {
	bool error = false;
	int numOfPac = 0;
	int numOfGhosts = 0;
	int numOfLegend = 0;
	int numOfInvalidChars = 0;

	for (int i = 0; i < getROW(RandC); i++) {
		for (int j = 0; j < getCol(RandC); j++) {
			if (getCharFromBoard(i, j) == (char)Objects::PACMAN) {
				numOfPac++;
			}
			else if (getCharFromBoard(i, j) == (char)Objects::GHOST) {
				numOfGhosts++;
			}
			else if (getCharFromBoard(i, j) == (char)Objects::LEGEND) {
				numOfLegend++;
			}
			else if (checkFile.isInvalidChar(getCharFromBoard(i, j))) {
				numOfInvalidChars++;
			}
		}
	}
	checkFile.checkAndPrintErrors(numOfInvalidChars, numOfPac, numOfGhosts, numOfLegend, error);
	return error;
}

void Board::eraseBoard() {
	for (int i = 0; i < (int)MaxRowCol::MAXROW; i++) {
		for (int j = 0; j < (int)MaxRowCol::MAXCOL; j++) {
			board[i][j] = ' ';
		}
	}
}

void Board::manageScreenFile(string fileName, Pacman& pacman, Ghost ghosts[], int& logGHsize, logicalROWCOL& RandC, bool& inFile) {
	try {
		fromFileToBoard(fileName, pacman, ghosts, logGHsize, RandC, inFile);
	}
	catch (const char* msg) {
		cout << msg << endl;
		inFile = false;
		Sleep(1300);
	}
}

void Board::changeFileBoardToGameBoard(Pacman& pacman, Ghost ghosts[], int& logicGHsize, logicalROWCOL RandC) {

	for (int i = 0; i < getROW(RandC); i++) {
		for (int j = 0; j < getCol(RandC); j++) {
			if (board[i][j] == (char)Objects::PACMAN) {
				pacman.setFirstPos(i, j);
				pacman.setObjPos(i, j);
				board[i][j] = (char)Objects::SPACE;
			}
			else if (board[i][j] == (char)Objects::GHOST) {
				ghosts[logicGHsize].setFirstPos(i, j);
				ghosts[logicGHsize].setObjPos(i, j);
				board[i][j] = (char)Objects::SPACE;
				logicGHsize++;
			}

			else if (board[i][j] == (char)Objects::EMPTYPLACE) {
				board[i][j] = (char)Objects::SPACE;
			}

			else if (board[i][j] == (char)Objects::LEGEND) {
				setLegend(i, j);
			}
			else if (board[i][j] == (char)Objects::SPACE) {
				board[i][j] = (char)Objects::BREADCRUMBS;
			}
		}
	}
	setSpaceInLegend(Legend);
	countBreadOnBoard(RandC);
}

void Board::countBreadOnBoard(logicalROWCOL RandC) {
	countBread = 0;
	int rows = getROW(RandC);
	int cols = getCol(RandC);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (board[i][j] == (char)Objects::BREADCRUMBS) {
				countBread++;
			}
		}
	}
}

void Board::setSpaceInLegend(const Position& Legend) {
	int row = Legend.GetRowPos();
	int col = Legend.GetColPos();

	for (int i = row; i < row + 3; i++) {
		for (int j = col; j < col + 19; j++) {
			setCharToBoard((char)Objects::SPACE, i, j);
		}
	}
}

void Board::initBoard(Color colorOfWalls, Color colorOfComments, Color colorOfBread, Pacman& pacman, logicalROWCOL RandC) {
	setColorsOfBoard(colorOfWalls, colorOfComments, colorOfBread);
}

void Board::setColorsOfBoard(Color colorOfWalls, Color colorOfComments, Color colorOfBread) {
	setColorOfWalls(colorOfWalls);
	setColorOfComments(colorOfComments);
	setColorOfBread(colorOfBread);
}

void Board::printLegend(int pacLives, int pacFood) {
	int rowLegend = Legend.GetRowPos(), colLegend = Legend.GetColPos();
	setTextColor(colorOfComments);
	gotoxy(colLegend + 1, rowLegend);
	cout << "PACMAN'S LIVES: " << pacLives << endl;
	gotoxy(colLegend + 6, rowLegend + 1);
	cout << "FOOD: " << pacFood;
	setTextColor(WHITE);
}

void Board::printBoard(Pacman& pacman, Ghost ghosts[], int logGHsize, logicalROWCOL RandC) {
	int i, j;
	int colN = RandC.getlogicC(), rowN = RandC.getlogicR();
	int num = 0;
	for (i = 0; i < RandC.getlogicR(); i++) {
		for (j = 0; j < RandC.getlogicC(); j++) {
			if (board[i][j] == (char)Objects::WALL) {
				printWall(i, j);
			}
			else if (board[i][j] == (char)Objects::BREADCRUMBS) {
				printBread(i, j);
			}
			else {
				cout << board[i][j];
			}
		}
		cout << "\n";
	}
	pacman.printObj(pacman.getObjPos().GetRowPos(), pacman.getObjPos().GetColPos());
	for (i = 0; i < logGHsize; i++) {
		ghosts[i].printObj(ghosts[i].getObjPos().GetRowPos(), ghosts[i].getObjPos().GetColPos());
	}
	printLegend(pacman.getPacmanLives(), pacman.getPacFood());
}

void Board::printWall(int row, int col) {
	setTextColor(colorOfWalls);
	gotoxy(col, row);
	cout << static_cast<char>(Objects::WALL) << endl;
	setTextColor(WHITE);
}

void Board::printBread(int row, int col) {
	setTextColor(colorOfBread);
	gotoxy(col, row);
	cout << static_cast<char>(Objects::BREADCRUMBS) << endl;
	setTextColor(WHITE);
}

char Board::checkAndReturnNextMove(Direction dir, int currRow, int currCol, logicalROWCOL& RandC) {

	if (dir == Direction::LEFT1 || dir == Direction::LEFT2) {//When the object goes left
		if (currCol > 0) {
			return(getCharFromBoard(currRow, currCol - 1));
		}
		else
			return -1;
	}
	if (dir == Direction::RIGHT1 || dir == Direction::RIGHT2) { //When the object goes right
		if (currCol < (getCol(RandC) - 1)) {
			return(getCharFromBoard(currRow, currCol + 1));
		}
		else
			return -1;
	}
	if (dir == Direction::UP1 || dir == Direction::UP2) { //when the object goes up
		if (currRow > 0) {
			return(getCharFromBoard(currRow - 1, currCol));
		}
		else
			return -1;
	}
	if (dir == Direction::DOWN1 || dir == Direction::DOWN2) { //When the object goes down
		if (currRow < (getROW(RandC) - 1)) {
			return(getCharFromBoard(currRow + 1, currCol));
		}
		else
			return -1;
	}
	return 0;
}


