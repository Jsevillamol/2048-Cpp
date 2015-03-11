#include <iostream>
#include <fstream>
#include <string>
#include "Game2048.h"
#include "HighScore.h"
#include "tScore.h"

//It loads the highscore file, ant put its
//contents in the array hallOfFame[]
void HighScore::load(int target, int size)
{
	std::string name = "HighScore_" + std::to_string(target) + "_" + 
					   std::to_string(size) + "x" +
					   std::to_string(size) + ".txt";
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
	std::string name = "HighScore_" + std::to_string(int(std::pow(2, *(game->getGoal())))) + "_" +
		                std::to_string(game->getBoard()->getDim()) + "x" +
						std::to_string(game->getBoard()->getDim()) + ".txt";
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
	std::cout << "Records (goal = " << int(std::pow(2, *(game->getGoal())))
		<< ", size = " << game->getBoard()->getDim() << "):" << std::endl;

	for (int i = 0; i<N_HIGHSCORES; i++)
	{
		if (hallOfFame[i].name != "XXX")
		{
			if (hallOfFame[i].name != "???")
			{
				if (i < 9)
				{
					std::cout << " " << (i + 1) << ": ";
				}
				else
				{
					std::cout << (i + 1) << ": ";
				}
			}
			else
			{
				std::cout << "    ";
			}
			std::cout << hallOfFame[i] << std::endl;
		}
	}
	std::cout << std::endl;
}

//It checks if the new score is a highscore, 
//and updates the array's contents
bool HighScore::new_highscore()
{
	load(int(std::pow(2, *(game->getGoal()))), game->getBoard()->getDim());

	int i;

	for (i = 0; hallOfFame[i] >= *(game->getScore()) && i<N_HIGHSCORES; i++){}

	if (hallOfFame[i] < *(game->getScore()))
	{
		insert(i);
		save();
		return true;
	}
	else return false;
}

//It prevens the name spans more than seven characters
std::string HighScore::valid_username()
{
	std::string name;
	int i = 9, j = 4;

	std::cout << "What is your name?:" << std::endl;
	std::cin  >> name;
	std::cin.clear();

	while ((name.size() > i) || (name.size() < j))
	{
		std::cout << "Error, your name cannot have";

		if (name.size() > i)
		{
			std::cout << " more than " << i;
		}
		else if (name.size() < j)
		{
			std::cout << " less than " << j;
		}
		std::cout << " characters" << std::endl
		  << "What is your name?:" << std::endl;
		std::cin  >> name;
		std::cin.clear();
	}
	return name;
}

//It updates the array's contents
void HighScore::insert(int position)
{
	int j;

	for (int k = 9; k>position; k--)
	{
		hallOfFame[k] = hallOfFame[k - 1];
	}
	std::string name;
	std::cout << "Congratulations! NEW HIGHSCORE!" << std::endl;
	name = valid_username();

	hallOfFame.highscores[position] = tScore(name, *(game->getScore()));

	for (j = 0; hallOfFame[j].name != "XXX"; j++){}

	if ((j < 9) && (hallOfFame[j - 1].name != "???"))
	{
		hallOfFame[j] = tScore("???", 0);
	}
}