#ifndef TBOARD
#define TBOARD
#include"tCoord.h"

class tBoard
{
private:
	int** board;
	int dim;

	void create(int d);
	void destroy();

public:
	tBoard(int d = DIM);
	~tBoard();

	void reset();
	void changeDimension(const int d);

	int getDim() { return dim; }

	int& operator [](const tCoord coord) { return board[coord.x][coord.y]; }
	int& operator ()(const int i, const int j) { return board[i][j]; }
};
#endif
