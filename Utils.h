#ifndef UTILS
#define UTILS

inline int rand_int(int m);
int digitoEntre(int a, int b);
void linea();

#include <cstdlib>
inline int rand_int(int m)
{
	return std::rand() % m;
}

#endif //UTILS
