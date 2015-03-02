#ifndef TMENU
#define TMENU
class Game2048;
class tMenu
{
private:
	Game2048 game;
public:
	void menuDim();
	int menuIni();
	int menuGoal();
	void start();
};
#endif
