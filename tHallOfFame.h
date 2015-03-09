#ifndef THALLOFFAME
#define THALLOFFAME
#include "tScore.h"
#include "GlobalConstants.h"

struct tHallOfFame
{
	tScore highscores[N_HIGHSCORES];
	tScore& operator [] (const int i) { return highscores[i]; }
};
#endif
