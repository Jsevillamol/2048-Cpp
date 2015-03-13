#include "tMenu.h"

#include <iostream>

#include "Game2048.h"
#include "Utils.h"

//It asks you what do you want to do
int tMenu::menuIni()
{
	std::cout << "Goal: " << std::pow(2, game.getGoal()) << "   "<< "Size: " 
		<< tBoard::getDim() << "x" << tBoard::getDim() << std::endl
		<< "1- Play" << std::endl
		<< "2- Change Dimension" <<std::endl
		<< "3- Change goal" <<std::endl
		<< "4- Records" << std::endl
		<< "0- Exit" << std::endl;

	return digitoEntre(0,4);
}

//Internal part of "menuIni()"
void tMenu::start()
{
	int seleccion;

	do
	{
		seleccion = menuIni();

		if (seleccion == 1)
		{
			game.run();
		}
		else if (seleccion == 2)
		{
			game.change_dim();
		}
		else if (seleccion == 3)
		{
			game.change_goal();
		}
		else if (seleccion == 4)
		{
			int target = game.choose_target(),
				size   = game.choose_size();
			game.getHighscore()->load(target, size);
			game.getHighscore()->show(target, size);
		}

	} while (seleccion != 0);
}
