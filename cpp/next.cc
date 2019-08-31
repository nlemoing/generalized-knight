#include "next.h"
#include <algorithm> // remove_if
#include <iterator> // distance
#include <stdlib.h> // rand

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

bool invalid(Board &b, pair<unsigned int, unsigned int> p) {
	return b.get(p.first, p.second) == -1;
}

std::pair<unsigned int, unsigned int> randomNextMove(Board &board, unsigned int r, unsigned int c, unsigned int a, unsigned int b) {
	vector<pair<unsigned int, unsigned int>> v = nextMoves(r, c, a, b);
	
	auto begin = v.begin();
	auto end = v.end();
	end = remove_if(begin, end, [&board](pair<unsigned int, unsigned int> p) { return invalid(board, p); });
	int num_moves = distance(begin, end);
	int next = rand() % num_moves;
	return v[next];
}
