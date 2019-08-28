#include "rw.h"
#include "next.h"
#include "image.h"
#include <algorithm> // remove_if
#include <iterator> // distance
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace cv;

bool invalid(Board &b, pair<unsigned int, unsigned int> p) {
	return b.get(p.first, p.second) == -1;
}

void rw(Board &board, StartBox &sb, Knight &k, int iterations, int steps, bool save_steps, bool trace_paths) {
	
	srand(time(NULL));

	unsigned int *walkers = new unsigned int[iterations * 2];
	for (int it = 0; it < iterations * 2; it += 2) {
		walkers[it] = sb.top + (rand() % sb.height); // start row
		walkers[it+1] = sb.left + (rand() % sb.width); // start col
	}
	
	int r, c, i, num_moves, next;
	vector<pair<unsigned int, unsigned int>> v;
	char fname[16];

	if (save_steps) {
		sprintf(fname, "%04d.png", 0);
		if (!trace_paths) board.refreshImg();
		board.toPNG(fname);
	}
	for (int step = 1; step <= steps; step++) {
		for (int it = 0; it < iterations * 2; it += 2) {
			r = walkers[it];
			c = walkers[it+1];
			
			i = board.get(r, c);
			if (i == -1) continue;
			board.set(r, c, i+1);	
			
			v = nextMoves(r, c, k.a, k.b);
			auto begin = v.begin();
			auto end = v.end();
			end = remove_if(begin, end, [&board](pair<unsigned int, unsigned int> p) { return invalid(board, p); });
			num_moves = distance(begin, end);
			next = rand() % num_moves;

			walkers[it] = v[next].first;
			walkers[it+1] = v[next].second;

			if (trace_paths) {
				board.line(r, c, walkers[it], walkers[it+1], (float)it / (2 * iterations));
			}
		}
		if (save_steps) {
			sprintf(fname, "%04d.png", step);
			if (!trace_paths) board.refreshImg();
			board.toPNG(fname);
		}
	}
	if (!trace_paths) board.refreshImg();

	delete[] walkers;
}

