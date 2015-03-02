#include <iostream>
#include <fstream>
#include <string>
#include "Game2048.h"
#include "HighScore.h"
#include "tScore.h"

HighScore::HighScore(Game2048 *g) : game(g)
{
	if (!load()) std::cout << "File not found";
}

bool HighScore::load()
{
	std::string name = "score.txt";
	std::ifstream file;

	file.open(name);

	if (file.is_open())
	{
		for (int i = 0; i<10; i++) //Problem: If there are not yet ten highscores, it crashes
		{
			file >> hallOfFame[i];
		}
		file.close();
		return true;
	}
	else return false;
}

void HighScore::save()
{
	std::ofstream file;
	std::string name = "score.txt";

	file.open(name);

	if (file.is_open())
	{
		for (int i = 0; i<10; i++) //Same as in load
		{
			file << hallOfFame[i];
		}
		file.close();
	}
	else std::cout << "Error, file " << name << " not found" << std::endl;
}

void HighScore::show()
{
	for (int i = 0; i<10; i++)
	{
		std::cout << hallOfFame[i] << std::endl;
	}
}

void HighScore::update()
{
	int i;
	std::string name;
	//Check if score is a highscore
	//If it is, ask for a name and place highscore in the array, moving the lower highscores to the right
	for (i = 0; hallOfFame[i] >= game->score && i<10; i++){}

	if (hallOfFame[i] < game->score)
	{
		for (int k = 9; k>i; k--)
		{
			hallOfFame[k] = hallOfFame[k - 1];
		}
		std::cout << "What is your name?:" << std::endl;
		std::cin.clear();
		std::cin >> name;

		hallOfFame.highscores[i] = tScore(name, game->score);
	}
}
