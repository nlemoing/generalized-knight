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

void rw(Board &board, int sbTop, int sbLeft, int sbHeight, int sbWidth, unsigned int a, unsigned int b, int iterations, int steps, bool save_steps) {
	
	srand(time(NULL));

	vector<unsigned int>walkers;
	for (int i = 0; i < iterations; i++) {
		walkers.push_back(sbTop + (rand() % sbHeight)); // start row
		walkers.push_back(sbLeft + (rand() % sbWidth)); // start col
	}
	
	int r, c, i, num_moves, next;
	vector<pair<unsigned int, unsigned int>> v;
	char fname[16];
	for (int step = 1; step <= steps; step++) {
		for (int it = 0; it < iterations * 2; it += 2) {
			r = walkers[it];
			c = walkers[it+1];
			i = board.get(r, c);
			if (i == -1) continue;
			board.set(r, c, i+1);	
			v = nextMoves(r, c, a, b);
			auto begin = v.begin();
			auto end = v.end();
			end = remove_if(begin, end, [&board](pair<unsigned int, unsigned int> p) { return invalid(board, p); });
			num_moves = distance(begin, end);
			next = rand() % num_moves;
			walkers[it] = v[next].first;
			walkers[it+1] = v[next].second;
		}
		if (save_steps) {
			sprintf(fname, "%04d.png", step);
			board.toPNG(fname);
		}
	}
}
