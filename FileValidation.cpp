#include "FileValidation.h"
#include "Board.h"
#include "utilities.h"
#include "Position.h"
#include "ROWCOL.h"
#include "Ghost.h"
using std::endl;



bool FileValidation::isInvalidChar(char ch) {
	return ch != (char)Objects::PACMAN && ch != (char)Objects::GHOST && ch != (char)Objects::EMPTYPLACE && ch != (char)Objects::BREADCRUMBS && ch != (char)Objects::SPACE && ch != (char)Objects::WALL && ch != (char)Objects::LEGEND;
}

void FileValidation::checkAndPrintErrors(const int& numOfInvalidChars, const int& numOfPac, const int& numOfGhosts, const int& numOfLegend, bool& error) {

	if (numOfInvalidChars != 0) {
		printERROR();
		cout << " THERE ARE " << numOfInvalidChars << " INVALID CHARS!" << endl;
		Sleep(1300);
		error = true;
	}

	else {
		if (numOfPac == 0) {
			printERROR();
			cout << " NO PACMAN!" << endl;
			Sleep(1300);
			error = true;
		}
		if (numOfPac > 1) {
			printERROR();
			cout << " THERE ARE " << numOfPac << " PACMANS!" << endl;
			Sleep(1300);
			error = true;
		}
		if (numOfGhosts > 4) {
			printERROR();
			cout << " THERE ARE " << numOfGhosts << " GHOSTS!" << endl;
			Sleep(1300);
			error = true;
		}
		if (numOfLegend == 0) {
			printERROR();
			cout << " NO Legend!" << endl;
			Sleep(1300);
			error = true;
		}
		if (numOfLegend > 1) {
			printERROR();
			cout << " THERE ARE " << numOfLegend << " LEGENDS!" << endl;
			Sleep(1300);
			error = true;
		}
	}

	if (error == false) {
		clear_screen();
	}
}


void FileValidation::printERROR() {
	clear_screen();
	cout << "#######################" << endl;
	cout << "##      ERROR!!!     ##" << endl;
	cout << "#######################" << endl;

}

bool FileValidation::checkLocationOfLegend(const int& LegendR, const int& LegendC, const int& rows, const int& cols) {
	return ((cols - LegendC) >= 20) && ((rows - LegendR) >= 3);
}


bool FileValidation::checkLegendPacAndGhost(const Position& Legend, const Position& pacman, Ghost ghosts[], const int& logGHsize) {
	bool res = isObjInLegend(Legend, pacman);
	int i = 0;
	while (!res && i < logGHsize) {
		res = isObjInLegend(Legend, ghosts[i].getObjPos());
		i++;
	}
	return res;
}

bool FileValidation::isObjInLegend(const Position& Legend, const Position& obj) {
	bool col = (Legend.GetColPos() <= obj.GetColPos()) && (obj.GetColPos() <= Legend.GetColPos() + 20);
	bool row = (Legend.GetRowPos() <= obj.GetRowPos()) && (obj.GetRowPos() <= Legend.GetRowPos() + 3);
	return col && row;
}

int FileValidation::LegendInFirstLine(const string& firstRow, Position& Legend) {
	int found = firstRow.find('&');
	int res = 0;

	if (found != -1) {
		if (found <= 60 && (firstRow.length() - found) < 20) {
			res = 20 - (firstRow.length() - found);
		}
		else {
			Legend.setPosition(0, found);
		}
	}
	return res;
}


