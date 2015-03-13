#ifndef HIGHSCORE
#define HIGHSCORE
#include "tHallOfFame.h"
class Game2048;
class HighScore
{
private:
	Game2048 *game;
	tHallOfFame hallOfFame;

public:
	HighScore(Game2048 *g) : game(g) {}

	void load(int target, int size);
	void save();

	void show(int target, int size);
	bool new_highscore();
	std::string valid_username();
	void insert(int position);
};
#endif
