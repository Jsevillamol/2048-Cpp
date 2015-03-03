#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

inline int rand_int(int m)
{
	return std::rand() % m;
}

int log2(int x)
{
	int i;
	for (i = 0; std::pow(2, i) < x; i++);
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

//Añade una linea de guion
void linea()
{
	std::cout << std::setfill('-') << std::setw(79) << '-' << std::endl << std::setfill(' ');
}
