#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <opencv2/opencv.hpp>

class Board {
	const unsigned int width, height;
	std::vector<int> data;
	public:
	Board(unsigned int w, unsigned int h);
	void print();
	cv::Mat convert(cv::Vec3b, cv::Vec3b);
	int get(unsigned int r, unsigned int c);
	bool set(unsigned int r, unsigned int c, int i);
};

#endif
