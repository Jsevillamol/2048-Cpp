#include "tScore.h"

//Just some operators
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