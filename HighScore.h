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

	bool new_highscore();
	std::string valid_username();
	void insert(tScore score, int position);

	void show(int target, int size);

	void save();
};
#endif
