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
	HighScore(Game2048 *g);
	~HighScore();

	bool load();
	void save();

	void show();
	void update();
};
#endif