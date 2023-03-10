
#include "Game.h"
#include <stdlib.h>
#include <windows.h>
#include <cstdlib>
#include <random>
#include <ctime>
#include <math.h>

int main(int argc, char **argv) {
	
	srand(time(NULL));
	Game game;
	game.start(argc, argv);
	return 0;
}