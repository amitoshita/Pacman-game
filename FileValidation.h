#ifndef _FILEVALIDATION_H_
#define _FILEVALIDATION_H_
#include "ROWCOL.h"
#include <string>
class Board;
class Ghost;
class Position;
using std::string;
class FileValidation {

public:
	bool isInvalidChar(char ch);
	void checkAndPrintErrors(const int& numOfInvalidChars, const int& numOfPac, const int& numOfGhosts, const int& numOfLegend, bool& error);
	bool checkLocationOfLegend(const int& LegendR, const int& LegendC, const int& rows, const int& cols);
	bool checkLegendPacAndGhost(const Position& Legend, const Position& pacman, Ghost ghosts[], const int& logGHsize);
	bool isObjInLegend(const Position& Legend, const Position& obj);
	int LegendInFirstLine(const string& firstRow, Position& Legend);
	void printERROR();

};

#endif

