#ifndef WINUTILS
#define WINUTILS
inline void cpConsoleOut(int cp);
void fontConsole();
void backgroundTextAtt(int color);

#include <Windows.h>

inline void cpConsoleOut(int cp)
{
	SetConsoleOutputCP(cp);
}

#endif //WINUTILS