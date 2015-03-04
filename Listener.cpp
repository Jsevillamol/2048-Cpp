#include "Listener.h"
#include <Windows.h>

int Listener::listen()
{
	int key; DWORD cNumRead; INPUT_RECORD irInBuf;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	do{
		do{
			ReadConsoleInput(hStdIn, &irInBuf, 1, &cNumRead);
		} while (irInBuf.EventType != KEY_EVENT);
		if (irInBuf.Event.KeyEvent.uChar.AsciiChar == 0){
			ReadConsoleInput(hStdIn, &irInBuf, 1, &cNumRead);
			key = irInBuf.Event.KeyEvent.wVirtualKeyCode;
		}
		else key = irInBuf.Event.KeyEvent.uChar.AsciiChar;
	} while (key != VK_ESCAPE && key != VK_LEFT && key != VK_UP
		&& key != VK_RIGHT  && key != VK_DOWN);
	//loop until game key is pressed
	return key;
}
