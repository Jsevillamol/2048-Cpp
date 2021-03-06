#include "tScore.h"

//Just some operators
bool operator <  (tScore s, long int i){ return (s.score <  i); }
bool operator >= (tScore s, long int i){ return (s.score >= i); }

std::ostream& operator << (std::ostream& out, tScore score)
{
	out << std::setw(10) << std::left << score.name << score.score;
	return out;
}

std::istream& operator >> (std::istream& in, tScore &score)
{
	in >> score.name >> score.score;
	return in;
}