#ifndef THALLOFFAME
#define THALLOFFAME
#include "tScore.h"
#include "GlobalConstants.h"

struct tHallOfFame
{
	tScore highscores[N_HIGHSCORES];
	int n;
	tHallOfFame() : n(0) {}
	tScore& operator [] (int i) { return highscores[i]; }
};
#endif
