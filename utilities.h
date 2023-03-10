#ifndef _UTILITIES_H_
#define _UTILITIES_H_
enum class Direction{
	RIGHT1 = 68, RIGHT2 = 100, LEFT1 = 65, LEFT2 = 97, UP1 = 87, UP2 = 119, DOWN1 = 88, DOWN2 = 120
	, STOP1 = 83, STOP2 = 115
};
enum class Objects{
	BREADCRUMBS = '.', WALL = '#', PACMAN = '@', GHOST = '$', EMPTYPLACE = '%', LEGEND = '&', SPACE = ' ',
	FRUIT5 = 5, FRUIT6 = 6, FRUIT7 = 7, FRUIT8 = 8, FRUIT9 = 9
};
enum class MaxRowCol{ MAXROW = 25, MAXCOL = 80 };

#endif