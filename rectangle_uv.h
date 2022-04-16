#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
using namespace  cv;
using namespace  std;


void connected_components(Mat& image,string win_name);        //不带统计信息
void connected_components_stat(Mat& image,string win_name,Mat &labels,Mat &stats  ,\
                                                                        int &num_labels);          //带统计信息

void rectangle_deal(Mat & status,int &lables_num);
