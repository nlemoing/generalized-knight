#include "rwRunner.h"
#include "rw.h"

using namespace std;

void runRw(Board &board, int a, int b, bool save) {
	StartBox sb;
	Knight k = { a, b };
	int iterations, steps;
	bool tracePaths;
	
	cerr << "Start box: top, left, width, height" << endl;
	cin >> sb.top >> sb.left >> sb.width >> sb.height;
	cerr << "Iterations (number of random walkers)" << endl;
	cin >> iterations;
	cerr << "Steps (number of steps per walker)" << endl;
	cin >> steps;
	cerr << "Trace paths? [y/n]" << endl;
	char c;
	cin >> c;
	tracePaths = (c == 'y' || c == 'Y');

	rw(board, sb, k, iterations, steps, save, tracePaths);
}
