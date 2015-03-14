#ifndef SAVEFILE
#define SAVEFILE
#include <string>
class Game2048;
class SaveFile
{
private:
	std::string file;
	Game2048 *game;

public:
	SaveFile(Game2048 *g) : game(g) {}

	bool load();
	bool save();
};
#endif
