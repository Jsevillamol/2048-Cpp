#include "winUtils.h"

inline void Drawer::cpConsoleOut(int cp)
{
	SetConsoleOutputCP(cp);
}

void Drawer::fontConsole()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.FontWeight = 400;
	cfi.nFont = 1;
	cfi.dwFontSize.X = 12; cfi.dwFontSize.Y = 20;
	cfi.FontFamily = 54;
	wcscpy_s(cfi.FaceName, L"LucidaConsole");
	SetCurrentConsoleFontEx(hStdOut, false, &cfi);
}

void Drawer::backgroundTextAtt(int color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15 | (color << 4));
}