#include "Pacman.h"


Pacman::Pacman() {

}

Pacman::~Pacman() {

}

void Pacman::initPacman(Color pacColor, Objects pacFigure, Direction diraction) {
	setArrowKeys("awdxsAWDXS");
	initObject(pacColor, pacFigure, diraction);
}

char Pacman::getDirection(char key) const {
	for (int i = 0; i < 10; i++)
	{
		if (key == arrowKeys[i])
			return arrowKeys[i];
	}
	return -1;
}

void Pacman::setArrowKeys(const char* keys) { // "awdxsAWDXS"
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
	arrowKeys[4] = keys[4];
	arrowKeys[5] = keys[5];
	arrowKeys[6] = keys[6];
	arrowKeys[7] = keys[7];
	arrowKeys[8] = keys[8];
	arrowKeys[9] = keys[9];
}