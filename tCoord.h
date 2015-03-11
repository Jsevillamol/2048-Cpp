#ifndef TCOORD
#define TCOORD
#include "GlobalConstants.h"

enum tDirection { left = 37, up, right, down };

struct tCoord
{
	int x; int y;
	tCoord(int i = 0, int j = 0) : x(i), y(j) {}
	tCoord next(tDirection dir);

	bool operator != (tCoord coor){ return x != coor.x || y != coor.y; }
};

#endif//TCOORD
