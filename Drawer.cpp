#include "Drawer.h"
#include <iostream>
#include <iomanip>
#include "Game2048.h"
#include "utilsWin.h"
#include "CharConstants.h"

Drawer::Drawer(Game2048 *g) :game(g)
{
	fontConsole();
	cpConsoleOut(850);
}

void Drawer::clearConsole(){ system("cls"); }

//It makes the tile number be centered
std::string Drawer::center_number(std::string number, int lenght)
{
	if (number.size() == lenght) return number;

	else
	{
		for (int i = number.size(); i < lenght; i++)
		{
			if (number.size() % 2 == 0)
			{
				number = number + " ";
			}
			else if (number.size() % 2 == 1)
			{
				number = " " + number;
			}
		}
		return number;
	}
}

//It draws the game board
void Drawer::draw()
{
	clearConsole();

	std::cout << "Move: " << game->getLast_score() << "   "
		<< "Score: " << game->getScore() << "   "
		<< "Goal: " << std::pow(2, game->getGoal()) << std::endl;

	upper_border();

	for (int i = 0; i < tBoard::getDim(); i++)
	{
		draw_row(i);
		if (i<(tBoard::getDim()) - 1) interior_border();
	}
	lower_border();

	std::cout << "Use the arrows (ESC for exit)" << std::endl;
}

//It draws the horizontal 
//line which forms each box
void Drawer::horizontal()
{
	for (int i = 0; i < hlenght; i++)
	{
		std::cout << char(horizontal_line);
	}
}

//It draws the upper border 
//of the board
void Drawer::upper_border()
{
	std::cout << char(upper_left_corner);

	for (int i = 0; i < tBoard::getDim(); i++)
	{
		horizontal();

		if (i != (tBoard::getDim() - 1))
		{
			std::cout << char(no_upper_carfax);
		}
		else
		{
			std::cout << char(upper_right_corner) << std::endl;
		}
	}
}

//It draws a row
void Drawer::draw_row(int row)
{
	for (int j = 0; j < vlenght; j++)
	{
		std::cout << char(upright_line);

		for (int k = 0; k < tBoard::getDim(); k++)
		{
			backgroundTextAtt((*game->getBoard())(row, k));

			if (j == 1 && (*game->getBoard())(row, k) != 0) std::cout << std::setw(hlenght) << center_number(std::to_string(int(std::pow(2, (*game->getBoard())(row, k)))), hlenght);
			else std::cout << std::setw(hlenght) << " ";

			backgroundTextAtt(0);

			std::cout << char(upright_line);
		}
		std::cout << std::endl;
	}
}

//It draws the border between rows
void Drawer::interior_border()
{
	std::cout << char(no_left_carfax);

	for (int i = 0; i < tBoard::getDim(); i++)
	{
		horizontal();

		if (i != (tBoard::getDim() - 1))
		{
			std::cout << char(carfax);
		}
		else
		{
			std::cout << char(no_right_carfax) << std::endl;
		}
	}
}

//It draws the lower border
//of the board
void Drawer::lower_border()
{
	std::cout << char(lower_lenf_corner);

	for (int i = 0; i < tBoard::getDim(); i++)
	{
		horizontal();

		if (i != (tBoard::getDim() - 1))	std::cout << char(no_lower_carfax);
		else std::cout << char(lower_right_corner) << std::endl;
	}
}