#include "Game2048.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <assert.h>

#include "GlobalConstants.h"
#include "Utils.h"
#include "utilsWin.h"

Game2048::Game2048(int d, int g):
	board(d),		goal(g),
	drawer(this),	savefile(this), 
	highscore(this)
{
	std::srand(std::time(NULL));
}


void Game2048::init()
{
	board.reset();
	gen_tile(); gen_tile();
	last_score = 0; score = 0;
}

//It asks for an exponent of 2 
//to make the goal
void Game2048::change_goal()
{
	std::cout << "What exponent of 2 do you choose as goal?" << std::endl;

	goal = digitoEntre(LOW_EXP_GOAL, MAX_EXP_GOAL);
}

void Game2048::upgrade_goal()
{
	int newGoal;

	do
	{
		std::cout << "What exponent of 2 do you choose as goal?" << std::endl;

		std::cin.sync(); //Por si quedan datos basura en el buffer
		std::cin >> newGoal;

		if (std::cin.fail())
		{
			std::cout << "Error, enter a digit" << std::endl;
			std::cin.clear();
		}
		else if (newGoal < goal)
		{
			std::cout << "Error, you cannot reach a lower goal than you already reached" << std::endl;
		}
		else if (newGoal == goal)
		{
			std::cout << "Error, you've just reached this goal" << std::endl;
		}
		else if (newGoal > MAX_EXP_GOAL)
		{
			std::cout << "Error, the goal cannot be over " << int(std::pow(2, MAX_EXP_GOAL)) << std::endl;
		}
	} while (newGoal <= goal || newGoal > MAX_EXP_GOAL);
}

int Game2048::choose_target()
{
	std::cout << "What exponent of 2 do you choose as goal?" << std::endl;

	return std::pow(2, digitoEntre(LOW_EXP_GOAL, MAX_EXP_GOAL));
}

//It asks for the board dimension 
//you want to play with
void Game2048::change_dim()
{
	int newDim;

	std::cout << "What size of the board do you choose? (4, 5, 6, 8)" << std::endl;

	newDim = digitoEntre(4, 8);
	
	while (newDim == 7)
	{
		std::cout << "Error, the size of the board cannot be seven" << std::endl
			<< "What size of the board do you choose? (4, 5, 6, 8)" << std::endl;

		newDim = digitoEntre(4, 8);
	}

	board.changeDimension(newDim);
}

int Game2048::choose_size()
{
	int newDim;

	std::cout << "What size of the board do you choose? (4, 5, 6, 8)" << std::endl;

	newDim = digitoEntre(4, 8);

	while (newDim == 7)
	{
		std::cout << "Error, the size of the board cannot be seven" << std::endl
		    << "What size of the board do you choose? (4, 5, 6, 8)" << std::endl;

		newDim = digitoEntre(4, 8);
	}

	return newDim;
}

//It starts the game
void Game2048::run()
{
	if (!savefile.load()) init();
	drawer.draw();

	int key = UP;

	inGame(key);
}

void Game2048::inGame(int key)
{
	while (key != ESCAPE && moves_left() && max_tile() < goal)
	{
		key = getKey();
		update(tDirection(key));
		drawer.draw();
	} 

	if (max_tile() == goal)
	{
		reach_goal(key);
	}
	else end(key);
}

void Game2048::reach_goal(int key)
{
	int choose;

	std::cout << "What do you yant to do?:" << std::endl
		<< "1- Continue (Choose a higher goal)" << std::endl
		<< "2- Replay (You cannot change the goal or size)" << std::endl
		<< "0- Exit to main menu" << std::endl << std::endl;

	choose = digitoEntre(0, 2);

	if (choose == 1)
	{
		if (goal == MAX_EXP_GOAL)
		{
			std::cout << "Error, you cannot reach a higher goal" << std::endl;
		}
		else
		{
			upgrade_goal();
			inGame(key);
		}
	}
	else if (choose == 2)
	{
		run();
	}
}

//updates the board with your movement
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

//It generates the random numbers 
//which appear at the begining, and
//every time you make a movement
void Game2048::gen_tile()
{
	assert(!is_full());

	int rx, ry;
	do {
		rx = rand_int(board.getDim()); ry = rand_int(board.getDim());
	} while (board(rx, ry) != 0);

	board(rx, ry) = ((rand() / RAND_MAX)<0.95) ? 1 : 2;
}

//It detects which of the board numbers
//is the maximum
int Game2048::max_tile()
{
	int mx_tile = 0;
	for (int i = 0; i<board.getDim(); i++)
		for (int j = 0; j<board.getDim(); j++)
		{
			if (board(i, j) > mx_tile) mx_tile = board(i, j);
		}
	return mx_tile;
}

//It moves the tiles and returns if a change has been made
bool Game2048::tilt(tDirection dir)
{
	bool there_has_been_movement = false;
	tCoord init, incr;

	getCoordMov(dir, init, incr);

	for (int i = init.x; 0 <= i && i<tBoard::getDim(); i += incr.x)
		for (int j = init.y; 0 <= j && j<tBoard::getDim(); j += incr.y)
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

//It combines the board numbers which are put together
//when you make a movement (just if both numbers are the same)
bool Game2048::combine_tiles(tDirection dir)
{
	tCoord init, incr; bool change = false;
	getCoordMov(dir, init, incr);
	for (int i = init.x; 0 <= i && i < tBoard::getDim(); i += incr.x)
	{
		for (int j = init.y; 0 <= j && j < tBoard::getDim(); j += incr.y)
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
	init.x = (dir == down) ? tBoard::getDim() - 1 : 0;
	init.y = (dir == right) ? tBoard::getDim() - 1 : 0;
	incr.x = (dir == down) ? -1 : 1;
	incr.y = (dir == right) ? -1 : 1;
}

//It detects if you have any movement left 
//when the board is full
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

//It detects if the board is full
bool Game2048::is_full()
{
	bool full = true;
	for (int i = 0; i<tBoard::getDim() && full; i++)
		for (int j = 0; j<tBoard::getDim() && full; j++)
		{
			if (board(i, j) == 0) full = false;
		}
	return full;
}

void Game2048::end(int key)
{
	if (key == ESCAPE) savefile.save();

	else if (max_tile() == goal)
	{
		if (highscore.new_highscore())
		{
			highscore.show(std::pow(2, getGoal()), tBoard::getDim());
		}
		else
		{
			std::cout << "congratulations, you've reached the goal, but sorry, you are not among the elite." << std::endl;
		}
	}
	else
	{
		std::cout << "You loose... GAME OVER" << std::endl;
	}
	std::cout << std::endl;
}
