#ifndef GAME2048
#define GAME2048
#include "utilsWin.h"
#include "Drawer.h"
#include "SaveFile.h"
#include "HighScore.h"
#include "tBoard.h"
#include "tCoord.h"
#include "GlobalConstants.h"

class Game2048
{
private:

	long int score, last_score, goal;

	Drawer drawer;
	SaveFile savefile;
	tBoard board;
	HighScore highscore;

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

	Drawer* getDrawer(){ return &drawer; }
	SaveFile* getSavefile(){ return &savefile; }
	tBoard* getBoard(){ return &board; }
	HighScore* getHighscore(){ return &highscore; }

	long int getScore(){ return score; }
	long int getLast_score(){ return last_score; }
	long int getGoal(){ return goal; }

	void setGoal(int i){ goal = i; }
	void setScore(int i){ score = i; }

	void init();
	void run();
	void change_goal();
	void upgrade_goal();
	int choose_target();
	void change_dim();
	int choose_size();
	void inGame();
	bool reach_goal();
	bool ends();	
};

#endif
