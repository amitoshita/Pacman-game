#ifndef _MENU_H_
#define  _MENU_H_
#include "Color.h"
#include "io.utils.h"
#include "utilities.h"
#include <string>
#include <iostream>
#include <filesystem>
using std::string;

class Menu {

public:
	void printMenu() const;
	void ghostLevelMenu();
	int checkGhostLevelMenu();
	void printColoredMenu() const;
	void instructions(char& choice);
	void CheckUserChoice(char& choice);
	void CheckUserChoiceColoredMenu(char& choice);
	void printLossMenu();
	void printVictoryMenu();
	void printNoFile();
};
#endif
