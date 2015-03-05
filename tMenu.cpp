#include "tMenu.h"

#include <iostream>

#include "Game2048.h"
#include "Utils.h"

int tMenu::menuIni()
{
	std::cout << "1- Play" << std::endl
		<< "2- Change Dimension" <<std::endl
		<< "3- Change goal" <<std::endl
		<< "4- Records" << std::endl
		<< "0- Exit" << std::endl;

	return digitoEntre(0,4);
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
			std::cout << "Not implemented" << std::endl;
		}

	} while (seleccion != 0);
}
