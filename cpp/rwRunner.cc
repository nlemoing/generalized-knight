#include "board.h"
#include "rw.h"
#include "params.h"

using namespace std;
using namespace cv;

void rwParams(int &sbTop, int &sbLeft, int &sbWidth, int &sbHeight, int &iterations, int &steps, bool &tracePaths) {
	cout << "Start box: top, left, width, height" << endl;
	cin >> sbTop >> sbLeft >> sbWidth >> sbHeight;
	cout << "Iterations (number of random walkers)" << endl;
	cin >> iterations;
	cout << "Steps (number of steps per walker)" << endl;
	cin >> steps;
	cout << "Trace paths? [y/n]" << endl;
	char c;
	cin >> c;
	tracePaths = (c == 'y' || c == 'Y');
}

int main() {
	int hueLo, hueHi, sat, bright;
	bool save;
	imageParams(hueLo, hueHi, sat, bright, save);
	
	int width, height, scale, knightA, knightB;
	boardParams(width, height, scale, knightA, knightB);
	
	int sbTop, sbLeft, sbWidth, sbHeight, iterations, steps;
	bool tracePaths;
	rwParams(sbTop, sbLeft, sbWidth, sbHeight, iterations, steps, tracePaths);

	Vec3b lo(hueLo, sat, bright);
	Vec3b hi(hueHi, sat, bright);
	
	Board b = Board(width, height, scale);
	b.setColors(lo, hi);
	
	if (tracePaths) rwPath(b, sbTop, sbLeft, sbWidth, sbHeight, knightA, knightB, iterations, steps, save);
	else rw(b, sbTop, sbLeft, sbWidth, sbHeight, knightA, knightB, iterations, steps, save);
	if (!save) b.toPNG("final.png");
}
