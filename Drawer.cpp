#include "Drawer.h"
#include <iostream>
#include <iomanip>
#include "Game2048.h"
#include "winUtils.h"
#include "CharConstants.h"

Drawer::Drawer(Game2048 *g) :game(g)
{
	fontConsole();
	cpConsoleOut(850);
}

void Drawer::draw()
{
	//system("pause");
	clearConsole();

	std::cout << "Move: " << game->last_score << "   "
		<< "Score: " << game->score << "   "
		<< "Goal: " << std::pow(2, game->goal) << std::endl;

	upper_border();

	for (int i = 0; i < game->board.getDim(); i++)
	{
		draw_row(i);
		if (i<(game->board.getDim() - 1)) interior_border();
	}
	lower_border();
}

void Drawer::clearConsole(){ system("cls"); }

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

		if (i != (game->board.getDim() - 1))
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

		if (i != (game->board.getDim() - 1))
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
			backgroundTextAtt(log2(std::pow(2,game->board(row, k))));

			if (j == 2 && game->board(row, k) != 0) std::cout << std::setw(7) << std::pow(2,game->board(row, k));
			else std::cout << std::setw(7) << " ";

			backgroundTextAtt(0);

			std::cout << char(upright_line);
		}
		std::cout << std::endl;
	}
}
