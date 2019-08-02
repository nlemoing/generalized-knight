#include "board.h"
#include "bfs.h"
#include "rw.h"

using namespace cv;
int main() {
	Vec3b lo(120, 170, 170); // blue
	Vec3b hi(30, 170, 170); // yellow
	Board b = Board(640, 480);
	bfs(b, 0, 0, 3, 1);
	Mat img = b.convert(lo, hi);
	cvtColor(img, img, COLOR_HSV2BGR);
	imwrite("img.png", img);
}
