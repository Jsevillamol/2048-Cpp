#ifndef GAME2048
#define GAME2048
#include "Listener.h"
#include "Drawer.h"
#include "SaveFile.h"
#include "HighScore.h"
#include "tBoard.h"
#include "tCoord.h"

class Game2048
{
private:
	tBoard board;
	double score, last_score, goal;
	int dim = board.getDim();

	Listener listener;
	Drawer drawer;
	SaveFile savefile;
	HighScore highscore;

	friend Drawer;
	friend SaveFile;
	friend HighScore;

public:
	Game2048();

	tBoard* getBoard(){ return &board; }
	HighScore* getHighscore(){ return &highscore; }

	void init();
	void change_goal();
	void change_dim();
	void run();
	void update(tDirection dir);
	void gen_tile();
	int max_tile();
	bool tilt(tDirection dir);
	bool combine_tiles(tDirection dir);
	void getCoordMov(tDirection dir, tCoord &init, tCoord &incr);
	bool moves_left();
	bool is_full();
};
#endif
