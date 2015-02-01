#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <assert.h>

const int DIM = 4,
          META = 2048;

const int upper_left_corner   = 218,
          upper_right_corner  = 191,
          downer_lenf_corner  = 192,
          downer_right_corner = 217,
          carfax              = 197,
          no_left_carfax      = 195,
          no_right_carfax     = 180,
          no_upper_carfax     = 194,
          no_downer_carfax    = 193,
          upright_line        = 179,
          horizontal_line     = 196;

enum tDirection {left=37,up,right,down};

struct tCoord
{
    int x; int y;
    tCoord (int i=0, int j=0): x(i), y(j) {}
    tCoord next(tDirection dir)
    {
        tCoord coor(x,y);

        if      (dir == left  && y>0)     coor.y--;
        else if (dir == up    && x>0)     coor.x--;
        else if (dir == right && y<DIM-1) coor.y++;
        else if (dir == down  && x<DIM-1) coor.x++;

        return coor;
    }

    bool operator != (tCoord coor){return x!=coor.x || y != coor.y;}
};

struct tBoard
{
    int board[DIM][DIM];

    tBoard(): board() {}

    int& operator [](const tCoord coord) {return board[coord.x][coord.y];}
    int& operator ()(const int i, const int j) {return board[i][j];}
};

class Listener;
class Drawer;
class SaveFile;
class Game2048;

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
        void cpConsoleOut(int cp);
        void fontConsole();
    void draw();
        void clearConsole();
        void backgroundTextAtt(int color);

        void draw_row(int row);
        void upper_border();
        void lower_border();
        void interior_border();
};

class SaveFile
{
private:
    std::string file;
    Game2048 *game;

public:
    SaveFile(Game2048 *g);
    ~SaveFile();

    bool save();
    bool load();
};

class Game2048
{
private:
    tBoard board;
    int score;

    Listener listener;
    Drawer drawer;
	SaveFile savefile;

    friend Drawer;
	friend SaveFile;

public:
    Game2048();
        void init();
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

int Listener::listen()
{
    int key; DWORD cNumRead; INPUT_RECORD irInBuf;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    do{
        ReadConsoleInput(hStdIn,&irInBuf,1,&cNumRead);
    } while(irInBuf.EventType != KEY_EVENT);
    if (irInBuf.Event.KeyEvent.uChar.AsciiChar == 0){
        ReadConsoleInput(hStdIn,&irInBuf,1,&cNumRead);
        key = irInBuf.Event.KeyEvent.wVirtualKeyCode;
    } else key = irInBuf.Event.KeyEvent.uChar.AsciiChar;
    return key;
}

Drawer::Drawer(Game2048 *g):
    game(g)
{

}

void Drawer::draw()
{
    //system("pause");
    clearConsole();
    for(int i=0; i<DIM; i++)
    {
        for(int j=0; j<DIM; j++)
        {
            std::cout << game->board(i,j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Drawer::cpConsoleOut(int cp)
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

void Drawer::clearConsole(){system("cls");}

void Drawer::backgroundTextAtt(int color)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, 15 | (color << 4));
}

SaveFile::SaveFile(Game2048 *g): game(g) {}

SaveFile::~SaveFile()
{
}

bool SaveFile::save()
{
	char option;
	std::cout << "Do you want to save your current game? (y/n)" << std::endl;
    std::cin >> option;

	if (option = 'y')
	{
		std::cout << "How do you want to call your save file?" << std::endl;
		getline(std::cin, file);
	}

	return false;
}

bool SaveFile::load()
{
    std::fstream in;
    std::cout << "Which save file do you want to load? (ENTER for New Game)" << std::endl;
    getline(std::cin, file);
    if (in != "")
    {
        in.open(file, std::fstream::in);
        if(in.is_open())
        {
            //Load the board
            for (int i=0; i<DIM; i++)
            for (int j=0; j<DIM; j++)
            {
                in >> game->board(i,j);
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
	else return false;
}

Game2048::Game2048():
    score(0), drawer(this), savefile(this)
    {
        if(!savefile.load()) init();
		drawer.draw();
    }

void Game2048::init()
{
    gen_tile(); gen_tile(); 
}

void Game2048::run()
{
    int key = up;

    while(max_tile() < META && key != VK_ESCAPE && moves_left())
    {
        key = listener.listen();
        update(tDirection(key));
        drawer.draw();
    }
}

void Game2048::update(tDirection dir)
{
    /*The three steps must always be executed,
          and if one changes the board, then we have to gen_tile*/
        bool change = false;
        change |= tilt(dir);
        change |= combine_tiles(dir);
        change |= tilt(dir);
        if (change) gen_tile();
}

void Game2048::gen_tile()
{
    assert(!is_full());

    int rx, ry;
    do {
    rx=rand_int(DIM); ry=rand_int(DIM);
    }while(board(rx,ry) != 0);

    board(rx, ry) = ((rand()/RAND_MAX)<0.95) ?2 :4;
}

int Game2048::max_tile()
{
    int mx_tile = 0;
    for(int i=0; i<DIM; i++)
    for(int j=0; j<DIM; j++)
    {
        if (board(i,j) > mx_tile) mx_tile = board(i,j);
    }
    return mx_tile;
}

bool Game2048::tilt(tDirection dir)
{
    bool there_has_been_movement = false;
    tCoord init, incr;

    getCoordMov(dir,init,incr);

    for(int i=init.x; 0<=i && i<DIM; i+= incr.x)
    for(int j=init.y; 0<=j && j<DIM; j+= incr.y)
    {
        while(board(i,j) != 0 && board[tCoord(i,j).next(dir)] == 0)
        {
            board[tCoord(i,j).next(dir)] = board(i,j);
            board(i,j) = 0;
            i = tCoord(i,j).next(dir).x; j = tCoord(i,j).next(dir).y;
            there_has_been_movement = true;
        }
    }
    return there_has_been_movement;
}

bool Game2048::combine_tiles(tDirection dir)
{
    tCoord init, incr; bool change = false;
    getCoordMov(dir, init, incr);
    for(int i=init.x; 0<=i && i<DIM; i+= incr.x)
    for(int j=init.y; 0<=j && j<DIM; j+= incr.y)
    {
        if(board(i,j)!=0 && (tCoord(i,j) != tCoord(i,j).next(dir))) //Check for borders
        {
            if(board[tCoord(i,j).next(dir)] == board(i,j))
            {
                board(i,j) = 0;
                board[tCoord(i,j).next(dir)] *= 2;
                score += board[tCoord(i,j).next(dir)];
                change = true;
            }
        }
    }
    return change;
}

void Game2048::getCoordMov(tDirection dir, tCoord &init, tCoord &incr)
{
    init.x = (dir == down)  ?DIM-1 :0;
    init.y = (dir == right) ?DIM-1 :0;
    incr.x = (dir == down)  ?-1    :1;
    incr.y = (dir == right) ?-1    :1;
}

bool Game2048::moves_left()
{
    if(is_full())
    {
        bool move_found = false;
        for (int i=left; i<=down && !move_found; i++)
        {
            Game2048 temp(*this);
            if(temp.combine_tiles(tDirection(i)))
                move_found = true;
        }
        return move_found;
    }
    else return true;
}

bool Game2048::is_full()
{
    bool full = true;
    for(int i=0; i<DIM && full; i++)
    for(int j=0; j<DIM && full; j++)
    {
        if (board(i,j) == 0) full = false;
    }
    return full;
}

inline int rand_int(int m)
{
    return rand()%m;
}

int log2(int x)
{
    int i;
    for (i=1; pow(2,i) < x; i++);
    return i;
}

int main()
{
    srand(time(NULL));
    Game2048 test;
    test.run();
}
