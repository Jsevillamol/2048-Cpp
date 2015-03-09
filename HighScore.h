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

	void load();
	void save();

	void show();
	bool new_highscore();
	void insert(int position);
};
#endif
