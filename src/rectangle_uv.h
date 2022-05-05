#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
using namespace  cv;
using namespace  std;

//连通区域检测  直线提取
void connected_components(Mat& image,string win_name);        //不带统计信息
void connected_components_stat(Mat& image,\
                                                                        string win_name,\
                                                                        Mat &labels,\
                                                                        Mat &stats  ,\
                                                                        int &num_labels,\
                                                                        vector<Vec4f>&abstract_line,\
                                                                        vector<Vec4f>&ground_line,\
                                                                        vector<Vec4f>&u_line);          //带统计信息

//直线处理
void Ground_line_Deal(vector<Vec4f>&ground_line_v,Mat VdispMap);
void Obstacle_line_Deal(vector<Vec4f>&abstract_line_v,Mat VdispMap,vector<Vec4f>&abstract_line_v_end);


void Ground_Obstacle__Line_deal(vector<Vec4f>&abstract_line_v,vector<Vec4f>&ground_line_v, Mat &VdispMap);
