#ifndef TSCORE
#define TSCORE
#include <iostream>
#include <string>
#include <iomanip>

struct tScore
{
	std::string name;
	long int score;

	tScore(std::string n = "XXX", long int s = 0) : name(n), score(s) {}
	tScore& operator = (const tScore other) { name = other.name; score = other.score; return *this; }

	friend std::ostream& operator << (std::ostream& out, tScore score);
	friend std::istream& operator >> (std::istream& in, tScore &score);
	friend bool operator <  (tScore s, long int i);
	friend bool operator >= (tScore s, long int i);

};


#endif //TSCORE
