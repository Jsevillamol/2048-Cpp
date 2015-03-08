#ifndef GAME2048
#define GAME2048
#include "Listener.h"
#include "Drawer.h"
#include "SaveFile.h"
#include "HighScore.h"
#include "tBoard.h"
#include "tCoord.h"
#include "GlobalConstants.h"

class Game2048
{
private:
	tBoard board;
	long int score, last_score, goal;

	Listener listener;
	Drawer drawer;
	SaveFile savefile;
	HighScore highscore;
	//HighScore highscore;

	friend Drawer;
	friend SaveFile;
	friend HighScore;

	void update(tDirection dir);
	void gen_tile();
	int max_tile();
	bool tilt(tDirection dir);
	bool combine_tiles(tDirection dir);
	void getCoordMov(tDirection dir, tCoord &init, tCoord &incr);
	bool moves_left();
	bool is_full();

public:
	Game2048(int d=DIM, int g=GOAL);

	tBoard* getBoard(){ return &board; }
	HighScore* getHighscore(){ return &highscore; }

	void init();
	void change_goal();
	void change_dim();
	void run();
	
};
#endif
