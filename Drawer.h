#ifndef DRAWER
#define DRAWER
#include <string>
class Game2048;
class Drawer
{
private:
	Game2048* game;
	int hlenght = 6, vlenght = 3;
public:
	Drawer(Game2048* g);
	void clearConsole();
	std::string center_number(std::string number, int size);
	void draw();
	void horizontal();
	void upper_border();
	void draw_row(int row);
	void interior_border();
	void lower_border();
	
};
#endif
