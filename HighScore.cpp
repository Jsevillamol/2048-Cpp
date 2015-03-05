#include <iostream>
#include <fstream>
#include <string>
#include "Game2048.h"
#include "HighScore.h"
#include "tScore.h"

void HighScore::load()
{
	std::string name = "HighScore_" + std::to_string(game->goal) + "_" +std::to_string(game->dim) + "x" + std::to_string(game->dim) + ".txt";
	std::ifstream file;

	file.open(name);

	if (file.is_open())
	{
		for (int i = 0; i < N_HIGHSCORES && file >> hallOfFame[i]; i++);
		file.close();
	}
	else std::cout << "File not found. A new file will be created.";
}

void HighScore::save()
{
	std::ofstream file;
	std::string name = "HighScore_" + std::to_string(game->goal) + "_" + std::to_string(game->dim) + "x" + std::to_string(game->dim) + ".txt";

	file.open(name);

	if (file.is_open())
	{
		for (int i = 0; i<N_HIGHSCORES; i++)
		{
			file << hallOfFame[i];
		}
		file.close();
	}
	else
	{
		for (int i = 0; i < N_HIGHSCORES; i++)
		{
			hallOfFame[i] = tScore();
		}
	}
}

void HighScore::show()
{
	load();
	for (int i = 0; i<N_HIGHSCORES; i++)
	{
		if (hallOfFame[i].name != "XXX")
		{
			std::cout << hallOfFame[i] << std::endl;
		}
	}
}

bool HighScore::new_highscore()
{
	load();

	int i;
	//Check if score is a highscore
	//If it is, ask for a name and place highscore in the array, moving the lower highscores to the right
	for (i = 0; hallOfFame[i] >= game->score && i<N_HIGHSCORES; i++){}

	if (hallOfFame[i] < game->score)
	{
		for (int k = 9; k>i; k--)
		{
			hallOfFame[k] = hallOfFame[k - 1];
		}
		std::string name;
		std::cout << "What is your name?:" << std::endl;
		std::cin.clear();
		std::cin >> name;

		hallOfFame.highscores[i] = tScore(name, game->score);

		if (i < 9)
		{
			hallOfFame.highscores[i+1] = tScore("???", 0);
		}
		save();
		return true;
	}
	else return false;
}
