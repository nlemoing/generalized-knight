#include "image.h"

using namespace std;
using namespace cv;

Vec3b interpolate(Vec3b lo, Vec3b hi, float f) {
	Vec3b result;
	result[0] = ((1-f) * lo[0]) + (f * hi[0]);
	result[1] = ((1-f) * lo[1]) + (f * hi[1]);
	result[2] = ((1-f) * lo[2]) + (f * hi[2]);
	return result;	
}

void drawPoint(Mat &img, int r, int c, Vec3b color, int scale) {
	Scalar s(color[0], color[1], color[2]);
	img(cv::Rect(c * scale, r * scale, scale, scale)).setTo(s);
}

void drawLine(Mat &img, int r1, int c1, int r2, int c2, Vec3b color, int scale) {
	Point p1(c1, r1);
	Point p2(c2, r2);
	Scalar s(color[0], color[1], color[2]);
	line(img, p1, p2, s);
}

void write(Mat &img, string fname) {
	Mat dest(img.rows, img.cols, img.type());
	cvtColor(img, dest, COLOR_HSV2BGR);
	imwrite(fname, dest);
}
