#ifndef TBOARD
#define TBOARD
#include "GlobalConstants.h"
struct tCoord;

class tBoard
{
private:
	int** board;
	static int dim;

	void create(int d);
	void destroy();

public:
	tBoard(int d = DIM);
	tBoard(const tBoard &oldBoard);
	~tBoard();

	void reset();
	void changeDimension(const int d);

	static int getDim() { return dim; }

	int& operator [](const tCoord coord);
	int& operator ()(const int i, const int j) { return board[i][j]; }
};
#endif
