#include "board.h"
#include "bfs.h"
#include "params.h"

using namespace std;
using namespace cv;

void bfsParams(int &startR, int &startC) {
	cout << "Start row, start column" << endl;
	cin >> startR >> startC;
}

int main() {
	int hueLo, hueHi, sat, bright;
	bool save;
	imageParams(hueLo, hueHi, sat, bright, save);
	
	int width, height, scale, knightA, knightB;
	boardParams(width, height, scale, knightA, knightB);
	
	int startR, startC;
	bfsParams(startR, startC);

	Vec3b lo(hueLo, sat, bright);
	Vec3b hi(hueHi, sat, bright);

	Board b = Board(width, height, scale);
	b.setColors(lo, hi);

	bfs(b, startR, startC, knightA, knightB, save);
	if (!save) b.toPNG("final.png");
}
