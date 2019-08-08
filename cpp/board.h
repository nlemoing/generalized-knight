#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

class Board {
	const unsigned int width, height;
	std::vector<int> data;
	cv::Vec3b lo, hi;
	public:
	Board(unsigned int w, unsigned int h);
	void print();
	void setColors(cv::Vec3b, cv::Vec3b);
	void toPNG(std::string fname);
	int get(unsigned int r, unsigned int c);
	bool set(unsigned int r, unsigned int c, int i);
};

#endif
