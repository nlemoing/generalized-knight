#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <opencv2/opencv.hpp>

cv::Vec3b interpolate(cv::Vec3b lo, cv::Vec3b hi, float f);
void drawPoint(cv::Mat &img, int r, int c, cv::Vec3b color, int scale);
void drawLine (cv::Mat &img, int r1, int c1, int r2, int c2, cv::Vec3b color, int scale);
void write(cv::Mat &img, std::string fname); 

#endif
