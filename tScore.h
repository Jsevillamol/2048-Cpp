#ifndef TSCORE
#define TSCORE
#include <fstream>
#include <string>

struct tScore
{
	std::string name;
	double score;

	tScore(std::string n = "XXX", double s = 0) : name(n), score(s) {}
	friend std::ostream& operator << (std::ostream& out, tScore score);
	friend std::istream& operator >> (std::istream& in, tScore score);
	friend bool operator <  (tScore s, double i);
	friend bool operator >= (tScore s, double i);

};

bool operator <  (tScore s, double i){ return (s.score <  i); }
bool operator >= (tScore s, double i){ return (s.score >= i); }

std::ostream& operator << (std::ostream& out, tScore score)
{
	out << score.name << "\t" << score.score;
	return out;
}

std::istream& operator >> (std::istream& in, tScore score)
{
	in >> score.name >> score.score;
	return in;
}
#endif
