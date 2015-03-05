#include <iostream>
#include <fstream>
#include <string>
#include "Game2048.h"
#include "HighScore.h"
#include "tScore.h"

void HighScore::load()
{
	std::string name = "HighScore_" + std::to_string(game->goal) + "_" + 
					   std::to_string(game->board.getDim()) + "x" +
					   std::to_string(game->board.getDim()) + ".txt";
	std::ifstream file(name);

	if (file.is_open())
	{
		for (int i = 0; i < N_HIGHSCORES && file >> hallOfFame[i]; i++);
		file.close();
	}
	else
	{
		std::cout << "File not found. A new file will be created.";
		for (int i = 0; i < N_HIGHSCORES; i++)
		{
			hallOfFame[i] = tScore();
		}
	}
}

void HighScore::save()
{
	std::string name = "HighScore_" + std::to_string(game->goal) + "_" +
		std::to_string(game->board.getDim()) + "x" +
		std::to_string(game->board.getDim()) + ".txt";
	std::ofstream file(name);

	if (file.is_open())
	{
		for (int i = 0; i<N_HIGHSCORES; i++)
		{
			file << hallOfFame[i];
		}
		file.close();
	}
}

void HighScore::show()
{
	load();
	for (int i = 0; i<N_HIGHSCORES; i++)
	{
		std::cout << hallOfFame[i] << std::endl;
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
		save();
		return true;
	}
	else return false;
}
