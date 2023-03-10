#ifndef _BOARD_H_
#define _BOARD_H_
#define _CRT_SECURE_NO_WARNINGS
#include "io.utils.h"
#include "Color.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Position.h"
#include "Menu.h"
#include "ROWCOL.h"
#include <iostream>
#include "utilities.h"
#include "FileValidation.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class FileValidation;
class Game;
class Pacman;
class Ghost;
class GameObject;
class Board
{
	Color colorOfWalls, colorOfComments, colorOfBread;
	char board[(int)MaxRowCol::MAXCOL][(int)MaxRowCol::MAXCOL];
	int countBread = 0;
	Position Legend;
	FileValidation checkFile;

public:
	Board();
	int getCountBread() const {
		return countBread;
	}
	int getROW(logicalROWCOL RandC) const;
	int getCol(logicalROWCOL RandC) const;
	void setCountBread(int count);
	void setLegend(int row, int col);
	Position getLegend() {
		return Legend;
	}
	void setROW(int col, logicalROWCOL& RandC);
	void setCOL(int col, logicalROWCOL& RandC);
	void setColorOfWalls(Color c);
	void setColorOfComments(Color c);
	void setColorOfBread(Color c);
	Color getColorOfWalls() const;
	Color getColorOfComments() const;
	Color getColorOfBread();
	void initBoard(Color colorOfWalls, Color colorOfComments, Color colorOfBread, Pacman& pacman, logicalROWCOL RandC);
	void fromFileToBoard(string fileName, Pacman& pacman, Ghost ghosts[], int& logicGHsize, logicalROWCOL& RandC, bool& inFile);
	void changeFileBoardToGameBoard(Pacman& pacman, Ghost ghosts[], int& logicGHsize, logicalROWCOL RandC);
	void countBreadOnBoard(logicalROWCOL RandC);
	void setSpaceInLegend(const Position& Legend);
	void eraseBoard();
	void manageScreenFile(string fileName, Pacman& pacman, Ghost ghosts[], int& logGHsize, logicalROWCOL& RandC, bool& inFile);
	void setColorsOfBoard(Color colorOfWalls, Color colorOfComments, Color colorOfBread);
	void printLegend(int pacLives, int pacFood);
	void printBoard(Pacman& pacman, Ghost ghosts[], int logGHsize, logicalROWCOL RandC);
    char getCharFromBoard(int row, int col) const  {
		return board[row][col];
	}
	void setCharToBoard(char symbol, int row, int col) {
		board[row][col] = symbol;
	}
	char checkAndReturnNextMove(Direction dir, int currRow, int currCol, logicalROWCOL& RandC);
	void printWall(int row, int col);
	void printBread(int row, int col);
	bool checkNumOfPacGhostAndLegend(logicalROWCOL& RandC);

	~Board();

};

#endif