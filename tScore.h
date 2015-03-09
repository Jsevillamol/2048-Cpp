#ifndef TSCORE
#define TSCORE
#include <iostream>
#include <string>

struct tScore
{
	std::string name;
	double score;

	tScore(std::string n = "XXX", double s = 0) : name(n), score(s) {}
	friend std::ostream& operator << (std::ostream& out, tScore score);
	friend std::istream& operator >> (std::istream& in, tScore score);
	friend bool operator <  (tScore s, long int i);
	friend bool operator >= (tScore s, long int i);

};


#endif //TSCORE
