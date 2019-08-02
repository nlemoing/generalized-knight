#include "rw.h"
#include "next.h"
#include <algorithm> // remove_if
#include <iterator> // distance
#include <stdlib.h>
#include <time.h>

using namespace std;

bool invalid(Board &b, pair<unsigned int, unsigned int> p) {
	return b.get(p.first, p.second) == -1;
}

Board &rw(Board &board, unsigned int startRow, unsigned int startCol, unsigned int a, unsigned int b, int steps, int iterations) {
	if (board.get(startRow, startCol) == -1) return board;
	int r, c, i, size, next;
	vector<pair<unsigned int, unsigned int>> v;
	
	srand(time(NULL));
	
	for (int it = 1; it <= iterations; it++) {
		r = startRow;
		c = startCol;
		for (int step = 1; step <= steps; step++) {
			i = board.get(r, c);
			if (i == -1) break;
			board.set(r, c, i+1);	
			v = nextMoves(r, c, a, b);
			auto begin = v.begin();
			auto end = v.end();
			end = remove_if(begin, end, [&board](pair<unsigned int, unsigned int> p) { return invalid(board, p); });
			size = distance(begin, end);
			next = rand() % size;
			r = v[next].first;
			c = v[next].second;
		}
	}
	return board;
}
