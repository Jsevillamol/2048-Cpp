#include "tMenu.h"
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(NULL));
	tMenu test;
	test.start();
}

