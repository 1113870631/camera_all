#ifndef __JIBIAN_H__
#define __JIBIAN_H__
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>
#include <opencv2/imgproc/imgproc_c.h>
using namespace cv;
using namespace std;

void jibian_zhuanhuan(Mat * mat11,Mat *mat12,Mat * mat21,Mat *mat22,Mat* Q_my,Size size,Rect *validPixROI1 ,Rect* validPixROI2 );
void jibian_correct(Mat * mat_l,Mat *mat_r,Mat * mat_l_o,Mat *mat_r_o,Mat * mat11,Mat *mat12,Mat * mat21,Mat *mat22,Rect validPixROI1 ,Rect validPixROI2);
#endif // !__JIBIAN_H__