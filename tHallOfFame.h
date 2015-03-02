#ifndef THALLOFFAME
#define THALLOFFAME
#include "tScore.h"

const int N_HIGHSCORES = 10;

struct tHallOfFame
{
	tScore highscores[N_HIGHSCORES];
	int n;
	tHallOfFame() : n(0) {}
	tScore& operator [] (int i) { return highscores[i]; }
};
#endif
