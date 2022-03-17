#ifndef __SGM_H__
#define __SGM_H__
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void sgm(Mat lift,Mat rigit,Mat *out,Mat *row_pic,int setNumDisparities,cv::Ptr<cv::StereoSGBM> sgbm) ;
#endif // !__SGM_H__