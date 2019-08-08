#include "bfs.h"
#include "next.h"
#include <deque>
#include <utility>

using namespace std;

void bfs(Board &board, unsigned int startRow, unsigned int startCol, unsigned int a, unsigned int b, bool save_steps) {
	if (board.set(startRow, startCol, 1)) return;
	deque<pair<unsigned int, unsigned int>> q(1, make_pair(startRow, startCol));
	pair<unsigned int, unsigned int> p;
	int r, c, i;
	int iterations = 0;
	char fname[16];
	while (q.size()) {
		p = q.front();
		q.pop_front();
		r = p.first;
		c = p.second;
		i = board.get(r, c);
		if (i == -1) continue;
		if (save_steps && i > iterations) {
			iterations += 1;
			sprintf(fname, "%04d.png", iterations);
			board.toPNG(fname);
		}
		for (auto next : nextMoves(r, c, a, b)) {
			// if it has already been visited or it is invalid, skip
			if (board.get(next.first, next.second)) continue;
			board.set(next.first, next.second, i + 1);
			q.push_back(next);
		}
	}
}
