#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <string.h>
#ifndef  __PICTURE_EX_H__
#define __PICTURE_EX_H__

using namespace cv;
using namespace std;
/**
 * @brief 
 * 将左右两张图像分开
 * 
 * @param mat    总图像
 * @param LIFT    左图像
 * @param RIGHT  右图像
 */
void picture_ex(Mat*  mat,Mat * LIFT,Mat * RIGHT);



#endif // ! __PICTURE_EX_H__