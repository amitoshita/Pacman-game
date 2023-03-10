#include "Position.h"
#include "Board.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
#include "ROWCOL.h"

void Position::draw(Objects ch) {
	gotoxy(y, x);
	cout << (char)ch << endl;
}



void Position::updateMove(Direction dir, Objects figure, logicalROWCOL& RandC, Board& board) {
	switch (dir) {
	case Direction::LEFT1: // LEFT
	case Direction::LEFT2: // LEFT
		y--;
		if (y < 0 && figure == Objects::PACMAN)
		{
			y = (RandC.getlogicC() - 1);
		}
		break;
	case Direction::DOWN1: // DOWN
	case Direction::DOWN2: // DOWN
		x++;
		if ((x > (RandC.getlogicR() - 1)) && figure == Objects::PACMAN) {
			x = 0;
		}
		break;
	case Direction::UP1: // UP
	case Direction::UP2: // UP
		x--;
		if (x < 0 && figure == Objects::PACMAN){
			x = (RandC.getlogicR() - 1);
		}
		break;
	case Direction::RIGHT1: // RIGHT
	case Direction::RIGHT2: // RIGHT
		y++;
		if ((y > (RandC.getlogicC() - 1)) && (figure == Objects::PACMAN)) {
			y = 0;
		}
		break;
	case Direction::STOP1: // PAUSE
	case Direction::STOP2: // PAUSE
		break;
	}
}