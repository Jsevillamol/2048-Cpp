#include "Utils.h"
#include <iostream>
#include <iomanip>

//It asks you for a digit, and makes sure that digit
//is between the other two that it has as arguments
int digitoEntre(int a, int b)
{
	int digito = -1;

	do
	{
		std::cin.sync(); //Por si quedan datos basura en el buffer
		std::cin >> digito;

		if (std::cin.fail())
		{
			std::cout << "Error, enter a digit" << std::endl;
			std::cin.clear();
		}

		else if (digito < a || digito > b)
		{
			std::cout << "Error, enter a digit between " << a << " and " << b << std::endl;
			digito = -1;
		}

	} while (digito == -1);

	return digito;
}

//It adds a script line
void linea()
{
	std::cout << std::setfill('-') << std::setw(79) << '-' << std::endl << std::setfill(' ');
}
