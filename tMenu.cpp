#include "tMenu.h"

#include <iostream>

#include "Game2048.h"
#include "Utils.h"

int tMenu::menuIni()
{
	std::cout << "1- Play" << std::endl
		<< "2- Records" << std::endl
		<< "0- Exit" << std::endl;

	return digitoEntre(0,2);
}

//int tMenu::menuGoal()
//{
//	std::cout << "You've reached the goal, what do you want to do?: " << std::endl
//		<< "1- Continue " << std::endl
//		<< "2- Replay " << std::endl
//		<< "0- Exit " << std::endl;
//
//	return digitoEntre(0,2);
//}

void tMenu::start()
{
	int seleccion = menuIni();

	do
	{
		if (seleccion == 1)
		{
			game.change_dim();
		}
		else if (seleccion == 2)
		{
			//game.getHighscore()->show();
		}
	} while (seleccion != 0);
}
