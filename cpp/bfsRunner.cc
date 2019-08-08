#include "board.h"
#include "bfs.h"

using namespace cv;
int main() {
	Vec3b lo(120, 170, 170); // blue
	Vec3b hi(30, 170, 170); // yellow
	Board b = Board(640, 480);
	b.setColors(lo, hi);
	bfs(b, 100, 100, 14, 27, true);
	b.toPNG("final.png");
}
