#include "board.h"
#include "image.h"
#include <iostream> 

using namespace std;
using namespace cv;

Board::Board(unsigned int w, unsigned int h, int s, string d): 
	width{w}, height{h}, scale{s}, dir{d}, data(w * h, 0), img(h * s, w * s, CV_8UC3, Scalar(0, 0, 0)) 
{
	if (dir.back() != '/') dir.push_back('/');
}

void Board::print() {
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			if (c) cout << ", ";
			cout << data[(r * width) + c];
		}
		cout << endl;
	}
}

void Board::setColors(Vec3b l, Vec3b h) {
	lo = l;
	hi = h;
}

void Board::refreshImg() {
	int max = 0, min = INT_MAX, val;
	float f;
	
	for (unsigned int r = 0; r < height; r++) {
		for (unsigned int c = 0; c < width; c++) {
			val = get(r, c);
			if (val and val > max) max = val;
			if (val and val < min) min = val;
		}
	}

	for (unsigned int r = 0; r < height; r++) {
		for (unsigned int c = 0; c < width; c++) {
			val = get(r, c);
			if (!val) {
				drawPoint(img, r, c, Vec3b(0, 0, 0), scale);
			} else {	
				f = (float)(val - min) / (max - min);
				drawPoint(img, r, c, interpolate(lo, hi, f), scale);
			}
		}
	}
}

void Board::line(int r1, int c1, int r2, int c2, float f) {
	drawLine(img, r1, c1, r2, c2, interpolate(lo, hi, f), scale);
}

void Board::toPNG(string fname) {
	write(img, dir + fname);
}

int Board::get(unsigned int r, unsigned int c) {
	if (r < 0 or r >= height or c < 0 or c >= width) return -1;
	return data[(r * width) + c];
}

bool Board::set(unsigned int r, unsigned int c, int i) {
	if (get(r, c) == -1) return true;
	data[(r * width) + c] = i;
	return false;
}
