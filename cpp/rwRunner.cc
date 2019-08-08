#include "board.h"
#include "rw.h"
#include "params.h"

using namespace std;
using namespace cv;

void rwParams(int &sbTop, int &sbLeft, int &sbWidth, int &sbHeight, int &iterations, int &steps) {
	cout << "Start box: top, left, width, height" << endl;
	cin >> sbTop >> sbLeft >> sbWidth >> sbHeight;
	cout << "Iterations (number of random walkers)" << endl;
	cin >> iterations;
	cout << "Steps (number of steps per walker)" << endl;
	cin >> steps;
}

int main() {
	int hueLo, hueHi, sat, bright;
	bool save;
	imageParams(hueLo, hueHi, sat, bright, save);
	
	int width, height, knightA, knightB;
	boardParams(width, height, knightA, knightB);
	
	int sbTop, sbLeft, sbWidth, sbHeight, iterations, steps;
	rwParams(sbTop, sbLeft, sbWidth, sbHeight, iterations, steps);

	Vec3b lo(hueLo, sat, bright);
	Vec3b hi(hueHi, sat, bright);
	
	Board b = Board(width, height);
	b.setColors(lo, hi);

	rw(b, sbTop, sbLeft, sbWidth, sbHeight, knightA, knightB, iterations, steps, save);
	if (!save) b.toPNG("final.png");
}
