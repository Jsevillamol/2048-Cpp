#include "tBoard.h"
#include "tCoord.h"

int tBoard::dim;

tBoard::tBoard(int d)
{
	create(d);
}

tBoard::~tBoard()
{
	destroy();
}

//It creates the board
void tBoard::create(int d)
{
	dim = d;
	board = new int*[dim];
	for (int i = 0; i<dim; i++)
		board[i] = new int[dim];
}

//It deletes the board
void tBoard::destroy()
{
	for (int i = 0; i < dim; i++)
	{
		delete[] board[i];
		board[i] = nullptr;
	}
	delete[] board;
	board = nullptr;
}

//It destroys the board, and creates other
//with the new dimension 
void tBoard::changeDimension(const int d)
{
	if (d != dim)
	{
		destroy();
		create(d);
	}
}

//It makes every tile in the board become 0
void tBoard::reset()
{
	for (int i = 0; i<dim; i++)
		for (int j = 0; j<dim; j++)
			board[i][j] = 0;
}

int& tBoard::operator [](const tCoord coord) { return board[coord.x][coord.y]; }