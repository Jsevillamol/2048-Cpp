#ifndef TCOORD
#define TCOORD
#include "GlobalConstants.h"

enum tDirection { left = 37, up, right, down };

struct tCoord
{
	int x; int y;
	tCoord(int i = 0, int j = 0) : x(i), y(j) {}
	tCoord next(tDirection dir)
	{
		tCoord coor(x, y);

		if (dir == left  && y>0)       coor.y--;
		else if (dir == up    && x>0)       coor.x--;
		else if (dir == right && y<DIM - 1) coor.y++;
		else if (dir == down  && x<DIM - 1) coor.x++;

		return coor;
	}

	bool operator != (tCoord coor){ return x != coor.x || y != coor.y; }
};
#endif
