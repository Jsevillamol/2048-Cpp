#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <assert.h>
#include <iomanip>

const int DIM = 8, //default dimension
	  GOAL = 2048,
	  MAX_GOAL = 1048576,
	  //drawer constants
	  upper_left_corner  = 218,
 	  upper_right_corner = 191,
 	  lower_lenf_corner  = 192,
	  lower_right_corner = 217,
	  carfax             = 197,
	  no_left_carfax     = 195,
	  no_right_carfax    = 180,
	  no_upper_carfax    = 194,
	  no_lower_carfax    = 193,
	  upright_line       = 179,
	  horizontal_line    = 196;

enum tDirection { left = 37, up, right, down };

struct tCoord
{
	int x; int y;
	tCoord(int i = 0, int j = 0) : x(i), y(j) {}
	tCoord next(tDirection dir)
	{
		tCoord coor(x, y);

		if      (dir == left  && y>0)       coor.y--;
		else if (dir == up    && x>0)       coor.x--;
		else if (dir == right && y<DIM - 1) coor.y++;
		else if (dir == down  && x<DIM - 1) coor.x++;

		return coor;
	}

	bool operator != (tCoord coor){ return x != coor.x || y != coor.y; }
};

struct tScore
{
	std::string name;
	int score;

	tScore(std::string n="XXX", int s=0): name(n), score(s) {}
	friend std::ostream& operator << (std::ostream& out, tScore score);
	friend std::istream& operator >> (std::istream& in, tScore score);
};

std::ostream& operator << (std::ostream& out, tScore score)
{
    out << score.name << "/t" << score.score;
    return out;
}

std::istream& operator >> (std::istream& in, tScore score)
{
    in >> score.name >> score.score;
    return in;
}

class tMenu;
class tBoard;
class Listener;
class Drawer;
class SaveFile;
class HighScore;
class Game2048;

int log2(int x);
int digitoEntre(int a,int b);

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

class tBoard
{
private:
	int** board;
	int dim;

public:
	tBoard(int d=DIM);
	~tBoard();

	void create(int d);
	void destroy();

	void reset();
	void changeDimension(const int d);

	int getDim() { return dim; }

	int& operator [](const tCoord coord) { return board[coord.x][coord.y]; }
	int& operator ()(const int i, const int j) { return board[i][j]; }
};

class Listener
{
public:
	int listen();
};

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

class SaveFile
{
private:
	std::string file;
	Game2048 *game;

public:
	SaveFile(Game2048 *g): game(g) {}

	bool save();
	bool load();
};

class HighScore
{
private:
	Game2048 *game;
	tScore highScores[10];
public:
	HighScore(Game2048 *g);
	~HighScore();

	bool load();
	void save();

	void show();
	bool update();
};

class Game2048
{
private:
	tBoard board;
	int score, last_score, goal;

	Listener listener;
	Drawer drawer;
	SaveFile savefile;
	HighScore highscore;

	friend Drawer;
	friend SaveFile;
	friend HighScore;

public:
	Game2048();
	void init();
	void change_goal();
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

inline int rand_int(int m);

//////////////////////////////////////////////////////////////

void tMenu::menuDim()
{
	int otherdim;

	std::cout << "4- Dimension 4x4" << std::endl
		  << "5- Dimension 5x5" << std::endl
		  << "6- Dimension 6x6" << std::endl
		  << "7- Dimension 7x7" << std::endl
		  << "8- Dimension 8x8" << std::endl;

	otherdim = digitoEntre(4,8);

	game.board.changeDimension(otherdim);

	game.run();
}

int tMenu::menuIni()
{
	std::cout << "1- Jugar"   << std::endl
		  << "2- Records" << std::endl
		  << "0- Salir"   << std::endl;

	return digitoEntre(0,2);
}

int tMenu::menuGoal()
{
	std::cout << "Has alcanzado la meta, que quieres hacer?: " << std::endl
	          << "1- Continuar "                               << std::endl
	          << "2- Reiniciar "                               << std::endl
	          << "0- Salir "                                   << std::endl;
	
	return digitoEntre(0,2);
}

void tMenu::start()
{
	int seleccion = menuIni();
	
	do
	{
		if      (seleccion == 1)
		{
			menuDim();
		}
		else if (seleccion == 2)
		{
			game.highscore.show();
		}
	}while (seleccion != 0);
}

tBoard::tBoard(int d):
	dim(d)
{
	create(d);
}

tBoard::~tBoard()
{
	destroy();
}

void tBoard::create(int d)
{
	board = new int*[dim];
	for (int i=0; i<dim; i++)
		board[i] = new int[dim]();
}

void tBoard::destroy()
{
	for (int i=0; i<dim; i++)
		delete[] board[i];
	delete[] board;
	board = nullptr;
}

void tBoard::changeDimension(const int d)
{
	if (d != dim)
	{
		destroy();
		create(d);
		dim=d;
	}
}

void tBoard::reset()
{
	for (int i=0; i<dim; i++)
	for (int j=0; j<dim; j++)
		board[i][j] = 0;
}

/////////////////////////////////

int Listener::listen()
{
	int key; DWORD cNumRead; INPUT_RECORD irInBuf;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	do{
		do{
			ReadConsoleInput(hStdIn, &irInBuf, 1, &cNumRead);
		} while (irInBuf.EventType != KEY_EVENT);
		if (irInBuf.Event.KeyEvent.uChar.AsciiChar == 0){
			ReadConsoleInput(hStdIn, &irInBuf, 1, &cNumRead);
			key = irInBuf.Event.KeyEvent.wVirtualKeyCode;
		}
		else key = irInBuf.Event.KeyEvent.uChar.AsciiChar;
	}while(key != VK_ESCAPE && key != VK_LEFT && key != VK_UP
		&& key != VK_RIGHT  && key != VK_DOWN);
		  //loop until game key is pressed
	return key;
}

/////////////////////////////////////////////////////////////

Drawer::Drawer(Game2048 *g) :
game(g)
{
	fontConsole();
	cpConsoleOut(850);
}

inline void Drawer::cpConsoleOut(int cp)
{
	SetConsoleOutputCP(cp);
}

void Drawer::fontConsole()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.FontWeight = 400;
	cfi.nFont = 1;
	cfi.dwFontSize.X = 12; cfi.dwFontSize.Y = 20;
	cfi.FontFamily = 54;
	wcscpy_s(cfi.FaceName, L"LucidaConsole");
	SetCurrentConsoleFontEx(hStdOut, false, &cfi);
}

void Drawer::draw()
{
	//system("pause");
	clearConsole();
	
	std::cout << "Move: "  << game->last_score << setw(3)
	          << "Score: " << game->score      << setw(3) 
	          << "Goal: "  << GOAL          << std::endl;

	upper_border();

	for (int i = 0; i < game->board.getDim(); i++)
	{
		draw_row(i);
		if (i<(game->board.getDim()-1)) interior_border();
		else
		{
			lower_border();
			
		}
	}
}

void Drawer::clearConsole(){ system("cls"); }

void Drawer::backgroundTextAtt(int color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15 | (color << 4));
}

void Drawer::horizontal()
{
	for (int i = 0; i < 7; i++)
	{
		std::cout << char(horizontal_line);
	}
}

void Drawer::upper_border()
{
	std::cout << char(upper_left_corner);

	for (int i = 0; i < game->board.getDim(); i++)
	{
		horizontal();

		if (i != (game->board.getDim()-1))
		{
			std::cout << char(no_upper_carfax);
		}
		else
		{
			std::cout << char(upper_right_corner) << std::endl;
		}
	}
}

void Drawer::lower_border()
{
	std::cout << char(lower_lenf_corner);

	for (int i = 0; i < game->board.getDim(); i++)
	{
		horizontal();

		if (i != (game->board.getDim() - 1))	std::cout << char(no_lower_carfax);
		else std::cout << char(lower_right_corner) << std::endl;
	}
}

void Drawer::interior_border()
{
	std::cout << char(no_left_carfax);

	for (int i = 0; i < game->board.getDim(); i++)
	{
		horizontal();

		if (i != (game->board.getDim()-1))
		{
			std::cout << char(carfax);
		}
		else
		{
			std::cout << char(no_right_carfax) << std::endl;
		}
	}
}

void Drawer::draw_row(int row)
{
	for (int j = 0; j < 5; j++)
	{
		std::cout << char(upright_line);

		for (int k = 0; k < game->board.getDim(); k++)
		{
			backgroundTextAtt(log2(game->board(row,k)));

			if (j==2 && game->board(row,k)!=0) std::cout << std::setw(7) << game->board(row,k);
			else std::cout << std::setw(7) << " ";

			backgroundTextAtt(0);

			std::cout << char(upright_line);
		}
		std::cout << std::endl;
	}
}

///////////////////////////////////

bool SaveFile::save()
{
	char option;
	std::cout << "Do you want to save your current game? (y/n)" << std::endl;
	std::cin.clear();
	std::cin >> option;

	if (option == 'y')
	{
		std::cout << "How do you want to call your save file? (ENTER for \"" << file << "\")" << std::endl;
		std::cin.sync();
		std::string s;
		getline(std::cin, s);
		std::fstream out(((s == "") ?file :s), std::ios::out);
		if(out.is_open())
		{
			for(int row=0; row < game->board.getDim(); row++)
			{
				for(int col=0; col < game->board.getDim(); col++)
				{
					out << game->board(row, col) << " ";
				}
				out << std::endl;
			}
			return true;
		}
		else
		{
			std::cout << "Error! The file couldn't be opened." << std::endl;
			return false;
		}
	}
	return false;
}

bool SaveFile::load()
{
	std::fstream in;
	std::cout << "Which save file do you want to load? (ENTER for New Game)" << std::endl;
	getline(std::cin, file);
	if (file != "")
	{
		in.open(file, std::fstream::in);
		if (in.is_open())
		{
			//Load the board
			for (int i = 0; i < game->board.getDim(); i++)
				for (int j = 0; j < game->board.getDim(); j++)
				{
					in >> game->board(i, j);
				}
			in.close();
			return true;
		}
		else
		{
			std::cout << "File not found" << std::endl;
			return false;
		}
	}
	else
	{
		file = "savefile.txt";
		return false;
	}
}

///////////////////////////////////////////

HighScore::HighScore(game2048 *g): game(g)
{
    if(!load()) std::cout<<"File not found";
}

bool HighScore::load()
{
	string name = "score.txt";
	ifstream file;

	file.open(name);

	if (file.is_open())
	{
		for (int i=0; i<10; i++)
		{
			file >> highScore[i];
		}
		file.close();
		return true;
	}
	else return false;
}

void HighScore::save()
{
	ofstream file;
	string name = "score.txt";
	
	file.open(name);
	
	if (file.is_open())
	{
		for (int i=0; i<10; i++)
		{
			file << highScore[i];
		}
		file.close();
	}
	else std::cout << "Error, archivo " << name << " no encontrado" << std::endl;
}

void HighScore::show()
{
	for (int i=0; i<10; i++)
	{
		std::cout << highScore[i] << std::endl;
	}
}

void HighScore::update()
{
	int i;
	string name;
    //Check if score is a highscore
    //If it is, ask for a name and place highscore in the array, moving the lower highscores to the right
	for (i=0; highScore[i]>=game.score && i<10; i++){}
	
	if (highScore[i] < game.score)
	{
		for (int k=9; k>i; k--)
		{
			highScore[k] = highScore[k-1];
		}
		std::cout << "What is your name?:" << std::endl;
		std::cin.clear;
		std::cin >> name;
		
		highScore[i] = tScore(name, score);
	}
}

////////////////////////////////////////////

Game2048::Game2048() :
	score(0), drawer(this), savefile(this)
{
	srand(time(NULL));
}

void Game2048::init()
{
	board.reset();
	gen_tile(); gen_tile();
}

void Game2048::change_goal()
{
	int newGoal;
	goal = GOAL; //defult goal
	
	std::cout << "What goal do you choose? (ENTER for 2048)" << std::endl;
	std::cin  >> newGoal;
	
	if (newGoal == "") goal = GOAL;
	else
	{
		if () std::cout << "Error, the goal must be a two-exponential" << std::endl;
		else if (goal > MAX_GOAL) std::cout << "Error, the goal cannot be over " << MAX_GOAL << std::endl;
		else goal = newGoal;
	}
}

void Game2048::run()
{
	if (!savefile.load()) init();
	drawer.draw();

	int key = up, what_to_do;
	
	change_goal();

	while (key != VK_ESCAPE && moves_left())
	{
		if (max_tile() == goal)
		{
			if (goal < MAX_GOAL)
			{
				what_to_do = menuGoal();
				
				if (what_to_do == 1)
				{
					key = listener.listen();
					update(tDirection(key));
					drawer.draw();	
				}
				else if (what_to_do == 2)
				{
					menuDim();
				}
				else
			}
			else std::cout << "Error, you have already reached the maximun goal" << std::endl;
		}
		else
		{
			key = listener.listen();
			update(tDirection(key));
			drawer.draw();
		}
	}

	if (key == VK_ESCAPE) savefile.save();
}

void Game2048::update(tDirection dir)
{
	/*The two steps must always be executed,
	and if one changes the board, then we have to gen_tile*/
	bool change = false;
	change |= tilt(dir);
	change |= combine_tiles(dir);

	if (change)
	{
		tilt(dir);
		gen_tile();
	}
}

void Game2048::gen_tile()
{
	assert(!is_full());

	int rx, ry;
	do {
		rx = rand_int(board.getDim()); ry = rand_int(board.getDim());
	} while (board(rx, ry) != 0);

	board(rx, ry) = ((rand() / RAND_MAX)<0.95) ? 2 : 4;
}

int Game2048::max_tile()
{
	int mx_tile = 0;
	for (int i = 0; i<DIM; i++)
		for (int j = 0; j<DIM; j++)
		{
			if (board(i, j) > mx_tile) mx_tile = board(i, j);
		}
	return mx_tile;
}

bool Game2048::tilt(tDirection dir)
{
	bool there_has_been_movement = false;
	tCoord init, incr;

	getCoordMov(dir, init, incr);

	for (int i = init.x; 0 <= i && i<board.getDim(); i += incr.x)
		for (int j = init.y; 0 <= j && j<board.getDim(); j += incr.y)
		{
			while (board(i, j) != 0 && board[tCoord(i, j).next(dir)] == 0)
			{
				board[tCoord(i, j).next(dir)] = board(i, j);
				board(i, j) = 0;
				i = tCoord(i, j).next(dir).x; j = tCoord(i, j).next(dir).y;
				there_has_been_movement = true;
			}
		}
	return there_has_been_movement;
}

bool Game2048::combine_tiles(tDirection dir)
{
	tCoord init, incr; bool change = false;
	getCoordMov(dir, init, incr);
	for (int i = init.x; 0 <= i && i<board.getDim(); i += incr.x)
		for (int j = init.y; 0 <= j && j<board.getDim(); j += incr.y)
		{
			if (board(i, j) != 0 && (tCoord(i, j) != tCoord(i, j).next(dir))) //Check for borders
			{
				if (board[tCoord(i, j).next(dir)] == board(i, j))
				{
					board(i, j) = 0;
					board[tCoord(i, j).next(dir)] *= 2;
					last_score = board[tCoord(i, j).next(dir)];
					score += last_score;
					change = true;
				}
			}
		}
	return change;
}

void Game2048::getCoordMov(tDirection dir, tCoord &init, tCoord &incr)
{
	init.x = (dir == down) ? board.getDim() - 1 : 0;
	init.y = (dir == right) ? board.getDim() - 1 : 0;
	incr.x = (dir == down) ? -1 : 1;
	incr.y = (dir == right) ? -1 : 1;
}

bool Game2048::moves_left()
{
	if (is_full())
	{
		bool move_found = false;
		for (int i = left; i <= down && !move_found; i++)
		{
			Game2048 temp(*this);
			if (temp.combine_tiles(tDirection(i)))
				move_found = true;
		}
		return move_found;
	}
	else return true;
}

bool Game2048::is_full()
{
	bool full = true;
	for (int i = 0; i<board.getDim() && full; i++)
		for (int j = 0; j<board.getDim() && full; j++)
		{
			if (board(i, j) == 0) full = false;
		}
	return full;
}

inline int rand_int(int m)
{
	return rand() % m;
}

int log2(int x)
{
	int i;
	for (i = 0; pow(2, i) < x; i++);
	return i;
}

int digitoEntre(int a, int b)
{
	int digito = -1;

	do
	{
		std::cin.sync(); //Por si quedan datos basura en el buffer
		std::cin >> digito;

		if (std::cin.fail())
		{
			std::cout << "Error! Introduce un digito" << std::endl;
			std::cin.clear();
		}

		else if (digito < a || digito > b)
		{
			std::cout << "Error! Introduce un digito entre " << a << " y " << b << std::endl;
			digito = -1;
		}

	} while (digito == -1);

	return digito;
}

int main()
{
	Game2048 test;
	test.run();
}
