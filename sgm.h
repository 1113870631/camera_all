#ifndef __SGM_H__
#define __SGM_H__
#include <iostream>
#include <opencv2/opencv.hpp>
#include </usr/include/opencv2/calib3d/calib3d_c.h>
using namespace cv;
using namespace std;
void sgm(Mat lift,Mat rigit,Mat *out,int setNumDisparities,cv::Ptr<cv::StereoSGBM> sgbm) ;
#endif // !__SGM_H__