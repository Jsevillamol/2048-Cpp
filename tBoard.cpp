#include "tBoard.h"

tBoard::tBoard(int d) :
dim(d)
{
	create(d);
}

tBoard::~tBoard()
{
	destroy();
}

void tBoard::create(int d)
{
	board = new int*[dim];
	for (int i = 0; i<dim; i++)
		board[i] = new int[dim]();
}

void tBoard::destroy()
{
	for (int i = 0; i<dim; i++)
		delete[] board[i];
	delete[] board;
	board = nullptr;
}

void tBoard::changeDimension(const int d)
{
	if (d != dim)
	{
		destroy();
		create(d);
		dim = d;
	}
}

void tBoard::reset()
{
	for (int i = 0; i<dim; i++)
		for (int j = 0; j<dim; j++)
			board[i][j] = 0;
}