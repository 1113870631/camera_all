#ifndef _U_V_H_
#define _U_V_H_
#include  "U_V.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void computeUDisparity(cv::Mat UdispMap,cv::Mat disp);
void computeVDisparity(cv::Mat &VdispMap,cv::Mat disp);



#endif // !_U_V_H_


