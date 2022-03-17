#include <opencv2/opencv.hpp>
#include <iostream>
#include "distance.h"

/**
 * @brief 
 * 1/4"    cmos   对角线 1/4 英寸     3x1280=3840   720x3=2160     6x640=3840   一个像素6um
 * b 镜头中心距离
 * f  焦距  3.6  mm   
 * z 深度
 * z=b*f/(xl-xr)
 * 
 *     dis   要测量距离点的时差值
 * @return double 
 */
double distance(double dis)
{
            double distance=6/1000*3.6/dis;
            return distance;
};
