#include "tCoord.h"
#include "tBoard.h"
tCoord tCoord::next(tDirection dir)
{
	tCoord coor(x, y);

	if (dir == left  && y>0)       coor.y--;
	else if (dir == up    && x>0)       coor.x--;
	else if (dir == right && y < tBoard::getDim() - 1) coor.y++;
	else if (dir == down  && x < tBoard::getDim() - 1) coor.x++;

	return coor;
}