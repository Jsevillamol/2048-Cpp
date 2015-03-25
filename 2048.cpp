/*-------------------------------
2048:

Authors:
Jaime Sevilla Molina.
Victor Gonzalez del Hierro.

Date:
2015/3

Version:
4.0

Features:
Apart from the order in the title of the practice, we have implemented:
1. Detection and correction of errors in data entry console.
2. Board size change option, between the dimensions 4, 5, 6, 8.
3. Goal change option, between 16, and 65536.
4. Records show option, depending the goal and size, from the main menu.
5. Once you reach the goal, you can replay, conntinue the game (choosing 
   a higher goal), or exit to the main menu.

Warning:
The way the program is implemented makes it work with exponents of 2, so that
you do not have problems when you chose the goal. Because of that, the savefiles
saves those exponents, not the powers.
---------------------------------*/

#include "tMenu.h"

int main()
{
	tMenu game;
	game.start();	
}

