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
	std::string name = "HighScore_" + std::to_string(int(std::pow(2, game->getGoal()))) + "_" +
		std::to_string(tBoard::getDim()) + "x" + std::to_string(tBoard::getDim()) + ".txt";
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
void HighScore::show(int target, int size)
{
	std::cout << "Records (goal = " << target
		<< ", size = " << size << "):" << std::endl;

	int i;

	for (i = 0; i<N_HIGHSCORES && hallOfFame[i].name != "???"; i++)
	{
		std::cout << std::right << std::setw(2) << 
		(i + 1) << ": " << hallOfFame[i] << std::endl;
	}
	if (i<N_HIGHSCORES) std::cout << "    ???: 0" << std::endl;
	
	std::cout << std::endl;
}

//It checks if the new score is a highscore, 
//and updates the array's contents
bool HighScore::new_highscore()
{
	load(int(std::pow(2, game->getGoal())), tBoard::getDim());

	int i;

	for (i = 0; hallOfFame[i] >= game->getScore() && i<N_HIGHSCORES; i++){}

	if (hallOfFame[i] < game->getScore())
	{
		std::string name;
		std::cout << "Congratulations! NEW HIGHSCORE!" << std::endl;
		name = valid_username();

		tScore score(name, game->getScore());

		insert(score, i);

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
void HighScore::insert(tScore score, int position)
{

	for (int k = 9; k>position; k--)
	{
		hallOfFame[k] = hallOfFame[k - 1];
	}
	
	hallOfFame.highscores[position] = score;
}