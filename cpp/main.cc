#include <iostream>
#include "params.h"
#include "board.h"
#include "rwRunner.h"
#include "bfsRunner.h"

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
	string usage = "Usage: knight [rw|bfs] [output directory]";
	if (argc != 3) {
		cerr << usage << endl;
		return 1;
	}
	string method, outputDir;
	method = argv[1];
	if (method != "rw" && method != "bfs") {
		cerr << usage << endl;
		return 2;
	}
	outputDir = argv[2];
	
	int hueLo, hueHi, satLo, satHi, valLo, valHi;
	bool save;
	imageParams(hueLo, satLo, valLo, hueHi, satHi, valHi, save);
	
	int width, height, scale, knightA, knightB;
	boardParams(width, height, scale, knightA, knightB);
	
	Vec3b lo(hueLo, satLo, valLo);
	Vec3b hi(hueHi, satHi, valHi);
	
	Board b = Board(width, height, scale, outputDir);
	b.setColors(lo, hi);
	
	if (method == "rw") {
		runRw(b, knightA, knightB, save);
	} else {
		runBfs(b, knightA, knightB, save);
	}

	if (!save) {
		b.toPNG("final.png");
	}
}
