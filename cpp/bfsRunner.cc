#include "bfsRunner.h"
#include "bfs.h"

using namespace std;

void runBfs(Board &board, int a, int b, bool save) {
	int r, c;
	cerr << "Start row, start column" << endl;
	cin >> r >> c;
	
	bfs(board, r, c, a, b, save);	
}
