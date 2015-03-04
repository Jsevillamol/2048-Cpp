#include <iostream>
#include <fstream>
#include <string>
#include "Game2048.h"
#include "HighScore.h"
#include "tScore.h"

HighScore::HighScore(Game2048 *g) : game(g)
{
	load();
}

void HighScore::load()
{
	std::string name = "HighScore_" + std::to_string(game->goal) + "_" +std::to_string(game->dim) + "x" + std::to_string(game->dim) + ".txt";
	std::ifstream file;

	file.open(name);

	if (file.is_open())
	{
		for (int i = 0; i < N_HIGHSCORES && file >> hallOfFame[i]; i++) //Problem: If there are not yet ten highscores, it crashes
		{
			hallOfFame.n++;
		}
		if (hallOfFame.n < N_HIGHSCORES) hallOfFame[hallOfFame.n] = tScore("???", 0);
		file.close();
	}
	else
	{
		for (int i = 0; i < N_HIGHSCORES; i++)
		{
			hallOfFame[i] = tScore("???", 0);
		}
	}
}

void HighScore::save()
{
	std::ofstream file;
	std::string name = "HighScore_" + std::to_string(game->goal) + "_" + std::to_string(game->dim) + "x" + std::to_string(game->dim) + ".txt";

	file.open(name);

	if (file.is_open())
	{
		for (int i = 0; i<hallOfFame.n; i++) //Same as in load
		{
			file << hallOfFame[i];
		}
		file.close();
	}
	else std::cout << "Error, file " << name << " not found" << std::endl;
}

void HighScore::show()
{
	for (int i = 0; i<hallOfFame.n; i++)
	{
		std::cout << hallOfFame[i] << std::endl;
	}
}

bool HighScore::new_highscore()
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

		return true;
	}
	else return false;
}
