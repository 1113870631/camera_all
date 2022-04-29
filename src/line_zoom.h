#ifndef __LINE_ZOOM_H__
#define __LINE_ZOOM_H__
#include <iostream>
#include <opencv2/opencv.hpp>
#include "line_zoom.h"
#include <vector>
#include <math.h>

using namespace cv;
using namespace std;

//相同斜率的 类
class one_k_clss_line
{
    public:
    double dis_preset;
    double  k_present;  
    vector<cv::Vec4f>line_point_data;
};
//直线聚合类
class    lines_zoom
{
    public:
    vector<one_k_clss_line>k_class;
}; 

//直线检测
 lines_zoom *  MethodOne(Mat img);
//直线聚合
 lines_zoom *  line_zoom(vector<Vec4f>plines,double k_dis,double d_dis);
 
#endif // !_LINE_ZOOM_H_
