#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

class Board {
	std::vector<int> data;
	cv::Vec3b lo, hi;
	int scale;
	public:
	const unsigned int width, height;
	cv::Mat img;
	Board(unsigned int w, unsigned int h, int s);
	void print();
	void setColors(cv::Vec3b, cv::Vec3b);
	void refreshImg();
	void line(int r1, int c1, int r2, int c2, float f);
	void toPNG(std::string fname);
	int get(unsigned int r, unsigned int c);
	bool set(unsigned int r, unsigned int c, int i);
};

#endif
