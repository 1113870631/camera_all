#ifndef  __OBSTACLE_DETECTION__
#define  __OBSTACLE_DETECTION__

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

/**
 * @brief     
 * 障碍物检测
 * abstract_line_v     V视图障碍物直线
 * u_line                        U视图 障碍物直线
 */
 void Obstacle_detection( vector<cv::Vec4f>abstract_line_v,vector<cv::Vec4f>u_line,Mat & disp,vector<cv::Vec4f>&Obstacles);
 void Obstacle_dis_rectangle(vector<cv::Vec4f> Obstacles,Mat color_picture,Mat disp,Mat World_coordinate_pos);



#endif // ! __OBSTACLE_DETECTION__

