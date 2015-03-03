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
	friend bool operator >> (std::istream& in, tScore score);
	friend bool operator <  (tScore s, long int i);
	friend bool operator >= (tScore s, long int i);

};

bool operator <  (tScore s, long int i){ return (s.score <  i); }
bool operator >= (tScore s, long int i){ return (s.score >= i); }

std::ostream& operator << (std::ostream& out, tScore score)
{
	out << score.name << "\t" << score.score;
	return out;
}

bool operator >> (std::istream& in, tScore score)
{
	std::string n;
	in >> n;
	if (n == "???")
	{
		score.name = n;
		in >> score.score;
		return true;
	}
	else return false;
}
#endif
