#include "rwRunner.h"
#include "rw.h"

using namespace std;

void runRw(Board &board, int a, int b, bool save) {
	int sbTop, sbLeft, sbWidth, sbHeight, iterations, steps;
	bool tracePaths;
	
	cerr << "Start box: top, left, width, height" << endl;
	cin >> sbTop >> sbLeft >> sbWidth >> sbHeight;
	cerr << "Iterations (number of random walkers)" << endl;
	cin >> iterations;
	cerr << "Steps (number of steps per walker)" << endl;
	cin >> steps;
	cerr << "Trace paths? [y/n]" << endl;
	char c;
	cin >> c;
	tracePaths = (c == 'y' || c == 'Y');

	if (tracePaths) rwPath(board, sbTop, sbLeft, sbWidth, sbHeight, a, b, iterations, steps, save);
	else rw(board, sbTop, sbLeft, sbWidth, sbHeight, a, b, iterations, steps, save);
}
