#include "tMenu.h"

#include <iostream>

#include "Game2048.h"
#include "Utils.h"

void tMenu::menuDim()
{
	std::cout << "4- Dimension 4x4" << std::endl
		<< "5- Dimension 5x5" << std::endl
		<< "6- Dimension 6x6" << std::endl
		<< "7- Dimension 7x7" << std::endl
		<< "8- Dimension 8x8" << std::endl;

	game.getBoard()->changeDimension(digitoEntre(4, 8));

	game.run();
}

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
			menuDim();
		}
		else if (seleccion == 2)
		{
			game.getHighscore()->show();
		}
	} while (seleccion != 0);
}
