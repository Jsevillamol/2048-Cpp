#include <iostream>
#include <fstream>
#include "SaveFile.h"
#include "Game2048.h"

//It asks you if you want to save your game, and if you want it, 
//it asks you how do you want to call the savefile
bool SaveFile::save()
{
	char option;
	std::cout << "Do you want to save your current game? (y/n)" << std::endl;
	std::cin.clear();
	std::cin >> option;

	if (option == 'y')
	{
		std::cout << "How do you want to call your save file? (ENTER for \"" << file << "\")" << std::endl;
		std::cin.sync();
		std::string s;
		getline(std::cin, s);
		std::fstream out(((s == "") ? file : s), std::ios::out);
		if (out.is_open())
		{
			for (int row = 0; row < game->board.getDim(); row++)
			{
				for (int col = 0; col < game->board.getDim(); col++)
				{
					out << game->board(row, col) << " ";
				}
				out << std::endl;
			}
			return true;
		}
		else
		{
			std::cout << "Error! The file couldn't be opened." << std::endl;
			return false;
		}
	}
	return false;
}

//It asks you what file do you want to load
bool SaveFile::load()
{
	std::fstream in;
	std::cout << "Which save file do you want to load? (ENTER for New Game)" << std::endl;
	std::cin.clear();
	getline(std::cin, file);
	if (file != "")
	{
		in.open(file, std::fstream::in);
		if (in.is_open())
		{
			//Load the board
			for (int i = 0; i < game->board.getDim(); i++)
				for (int j = 0; j < game->board.getDim(); j++)
				{
					in >> game->board(i, j);
				}
			in.close();
			return true;
		}
		else
		{
			std::cout << "File not found" << std::endl;
			return false;
		}
	}
	else
	{
		file = "savefile.txt";
		return false;
	}
}
