#include "board.h"
#include <iostream> 

using namespace std;
using namespace cv;

Board::Board(unsigned int w, unsigned int h): width{w}, height{h}, data(w * h, 0) {}

void Board::print() {
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			if (c) cout << ", ";
			cout << data[(r * width) + c];
		}
		cout << endl;
	}
}

Vec3b interpolate(Vec3b lo, Vec3b hi, float f) {
	Vec3b result;
	result[0] = ((1-f) * lo[0]) + (f * hi[0]);
	result[1] = ((1-f) * lo[1]) + (f * hi[1]);
	result[2] = ((1-f) * lo[2]) + (f * hi[2]);
	return result;	
}

void Board::setColors(Vec3b l, Vec3b h) {
	lo = l;
	hi = h;
}

void Board::toPNG(string fname) {
	Mat img = Mat::zeros(height, width, CV_8UC3);
	int max = 0, min = INT_MAX, val;
	Vec3b intensity;
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
			if (!val) continue;
			f = (float)(val - min) / (max - min);
			img.at<Vec3b>(r, c) = interpolate(lo, hi, f);
		}
	}

	cvtColor(img, img, COLOR_HSV2BGR);
	imwrite(fname, img);
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
