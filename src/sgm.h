#ifndef  __SGM_H__
#define __SGM_H__
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
#define thead_num 6
#define thead_num2 1

void sgm(Mat lift,Mat rigit,Mat *out,Mat *out_row,int setNumDisparities);
 void thread_prepare(int thread_num);
 void Set_Sgbm(void);
#endif // !__SGM_H__