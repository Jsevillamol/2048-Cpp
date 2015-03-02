#ifndef DRAWER
#define DRAWER
class Game2048;
class Drawer
{
private:
	Game2048 *game;
public:
	Drawer(Game2048 *g);
	void draw();
	void clearConsole();
	void draw_row(int row);
	void upper_border();
	void lower_border();
	void interior_border();
	void horizontal();
};
#endif
