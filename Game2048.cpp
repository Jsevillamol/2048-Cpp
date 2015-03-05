#include "Game2048.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <assert.h>

#include "GlobalConstants.h"
#include "Utils.h"
#include "keys.h"

Game2048::Game2048(int d, int g):
	board(d),		goal(g),
	score(0),		last_score(0), 
	drawer(this),	savefile(this)//, highscore(this)
{
	std::srand(std::time(NULL));
}

void Game2048::init()
{
	board.reset();
	gen_tile(); gen_tile();
}

void Game2048::change_goal()
{
	std::cout << "What exponent of 2 do you choose as goal?" << std::endl;

	goal = digitoEntre(LOW_EXP_GOAL, MAX_EXP_GOAL);
}

void Game2048::change_dim()
{
	int newDim;

	std::cout << "What size of the board do you choose? (4-8)" << std::endl;

	newDim = digitoEntre(4, 8);

	getBoard()->changeDimension(newDim);

}

void Game2048::run()
{
	if (!savefile.load()) init();
	drawer.draw();

	int key = UP;
	//do
	//{

		while (key != ESCAPE && moves_left() && max_tile() < std::pow(2, goal))
		{
			key = listener.listen();
			update(tDirection(key));
			drawer.draw();
		}
		//if (highscore.new_highscore())
		//{
		//	highscore.show();
		////}
		//if keep playing
		//change_goal();
		//key == UP
	//} while (key != ESCAPE);

	if (key == ESCAPE) savefile.save();
}

void Game2048::update(tDirection dir)
{
	/*The two steps must always be executed,
	and if one changes the board, then we have to gen_tile*/
	bool change = false;
	change |= tilt(dir);
	change |= combine_tiles(dir);

	if (change)
	{
		tilt(dir);
		gen_tile();
	}
}

void Game2048::gen_tile()
{
	assert(!is_full());

	int rx, ry;
	do {
		rx = rand_int(board.getDim()); ry = rand_int(board.getDim());
	} while (board(rx, ry) != 0);

	board(rx, ry) = ((rand() / RAND_MAX)<0.95) ? 1 : 2;
}

int Game2048::max_tile()
{
	int mx_tile = 0;
	for (int i = 0; i<board.getDim(); i++)
		for (int j = 0; j<board.getDim(); j++)
		{
			if (std::pow(2,board(i, j)) > mx_tile) mx_tile = std::pow(2, board(i, j));
		}
	return mx_tile;
}

bool Game2048::tilt(tDirection dir)
{
	bool there_has_been_movement = false;
	tCoord init, incr;

	getCoordMov(dir, init, incr);

	for (int i = init.x; 0 <= i && i<board.getDim(); i += incr.x)
		for (int j = init.y; 0 <= j && j<board.getDim(); j += incr.y)
		{
			while (board(i, j) != 0 && board[tCoord(i, j).next(dir)] == 0)
			{
				board[tCoord(i, j).next(dir)] = board(i, j);
				board(i, j) = 0;
				i = tCoord(i, j).next(dir).x; j = tCoord(i, j).next(dir).y;
				there_has_been_movement = true;
			}
		}
	return there_has_been_movement;
}

bool Game2048::combine_tiles(tDirection dir)
{
	tCoord init, incr; bool change = false;
	getCoordMov(dir, init, incr);
	for (int i = init.x; 0 <= i && i < board.getDim(); i += incr.x)
	{
		for (int j = init.y; 0 <= j && j < board.getDim(); j += incr.y)
		{
			if (board(i, j) != 0 && (tCoord(i, j) != tCoord(i, j).next(dir))) //Check for borders
			{
				if (board[tCoord(i, j).next(dir)] == board(i, j))
				{
					board(i, j) = 0;
					board[tCoord(i, j).next(dir)] += 1;
					last_score = (std::pow(2, board[tCoord(i, j).next(dir)])/2);
					score += last_score;
					change = true;
				}
			}
		}
	}
	return change;
}

void Game2048::getCoordMov(tDirection dir, tCoord &init, tCoord &incr)
{
	init.x = (dir == down) ? board.getDim() - 1 : 0;
	init.y = (dir == right) ? board.getDim() - 1 : 0;
	incr.x = (dir == down) ? -1 : 1;
	incr.y = (dir == right) ? -1 : 1;
}

bool Game2048::moves_left()
{
	if (is_full())
	{
		bool move_found = false;
		for (int i = left; i <= down && !move_found; i++)
		{
			Game2048 temp(*this);
			if (temp.combine_tiles(tDirection(i)))
				move_found = true;
		}
		return move_found;
	}
	else return true;
}

bool Game2048::is_full()
{
	bool full = true;
	for (int i = 0; i<board.getDim() && full; i++)
		for (int j = 0; j<board.getDim() && full; j++)
		{
			if (board(i, j) == 0) full = false;
		}
	return full;
}
