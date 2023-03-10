#ifndef _PACMAN_H_
#define _PACMAN_H_
#include <iostream>
#include "io.utils.h"
#include "Position.h"
#include "utilities.h"
#include "Color.h"
#include "GameObject.h"
using std::cout;
class GameObject;

class Pacman : public GameObject {
private:
	int lives = 3;
	int food_collected = 0;
	int breadCollected = 0;
	char arrowKeys[10];
public:
	Pacman();
	void setArrowKeys(const char* keys); // Sets the arrowkeys the player can play with.
	void initPacman(Color pacColor, Objects pacFigure, Direction diraction);
	void addFoodCollected() {
		food_collected++;
		breadCollected++;
	}
	int getBreadCollecter() const {
		return breadCollected;
	}
	int getPacFood() const {
		return food_collected;
	}
	char getDirection(char key) const;
	int getPacmanLives() const {
		return lives;
	}
	void setPacmanLives() {
		lives--;
	}
	void resetPacmanLives() {
		lives = 3;
	}
	void addFruitCollected(char fruit) {
		int fruity = fruit - '0';
		food_collected += fruity;
	}
	void resetPacmanFood() {
		food_collected = 0;
	}
	void resetBreadCrumbs()
	{
		breadCollected = 0;
	}
	void printPacLives() const {
		cout << "PACMAN'S LIVES: " << lives;
	}
	void printPacFood() const {
		cout << "YOU COLLECTED " << food_collected << " BREADCRUMBS";
	}

	bool PacAteAllBread(int countBread) {
		if (breadCollected == countBread)
			return true;
		else {
			return false;
		}
	}
	~Pacman();

};

#endif