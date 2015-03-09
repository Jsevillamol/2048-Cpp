#include <iostream>
#include <fstream>
#include <string>
#include "Game2048.h"
#include "HighScore.h"
#include "tScore.h"

//It loads the highscore file, ant put its
//contents in the array hallOfFame[]
void HighScore::load()
{
	std::string name = "HighScore_" + std::to_string(int(std::pow(2, game->goal))) + "_" + 
					   std::to_string(game->board.getDim()) + "x" +
					   std::to_string(game->board.getDim()) + ".txt";
	std::ifstream file(name);

	if (file.is_open())
	{
		for (int i = 0; i < N_HIGHSCORES; i++){
			file >> hallOfFame[i];
		}
		file.close();
	}
	else
	{
		std::cout << "File not found. A new file will be created." << std::endl;
		for (int i = 0; i < N_HIGHSCORES; i++)
		{
			hallOfFame[i] = tScore();
		}
	}
}

//It saves the highscore file
void HighScore::save()
{
	std::string name = "HighScore_" + std::to_string(int(std::pow(2, game->goal))) + "_" +
		                std::to_string(game->board.getDim()) + "x" +
		                std::to_string(game->board.getDim()) + ".txt";
	std::ofstream file(name);

	if (file.is_open())
	{
		for (int i = 0; i<N_HIGHSCORES; i++)
		{
			file << hallOfFame[i] << std::endl;
		}
		file.close();
	}
}

//It shows the array's contents 
void HighScore::show()
{
	std::cout << "Records (goal = " << int(std::pow(2, game->goal))
		<< ", size = " << game->board.getDim() << "):" << std::endl;

	for (int i = 0; i<N_HIGHSCORES; i++)
	{
		if (hallOfFame[i].name != "XXX")
		{
			std::cout << hallOfFame[i] << std::endl;
		}
	}
}

//It checks if the new score is a highscore, 
//and updates the array's contents
bool HighScore::new_highscore()
{
	load();

	int i, j;

	for (i = 0; hallOfFame[i] >= game->score && i<N_HIGHSCORES; i++){}

	if (hallOfFame[i] < game->score)
	{
		insert(i);
		save();
		return true;
	}
	else return false;
}

void HighScore::insert(int position)
{
	int j;

	for (int k = 9; k>position; k--)
	{
		hallOfFame[k] = hallOfFame[k - 1];
	}
	std::string name;
	std::cout << "Congratulations! NEW HIGHSCORE!" <<
		std::endl << "What is your name?:" << std::endl;
	std::cin.clear();
	std::cin >> name;

	hallOfFame.highscores[position] = tScore(name, game->score);

	for (j = 0; hallOfFame[j].name != "XXX"; j++){}

	if (j < 9)
	{
		hallOfFame.highscores[j + 1] = tScore("???", 0);
	}
}