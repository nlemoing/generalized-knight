#include "next.h"

using namespace std;
vector<pair<unsigned int, unsigned int>> nextMoves(unsigned int r, unsigned int c, unsigned int a, unsigned int b) {
	vector<pair<unsigned int, unsigned int>> v;
	v.emplace_back(r + a, c + b);
	v.emplace_back(r + a, c - b);
	v.emplace_back(r - a, c + b);
	v.emplace_back(r - a, c - b);
	v.emplace_back(r + b, c + a);
	v.emplace_back(r + b, c - a);
	v.emplace_back(r - b, c + a);
	v.emplace_back(r - b, c - a);
	return v;
}
