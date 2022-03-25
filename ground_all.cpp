#include "ground_all.h"
#include "U_V.h"
#include "line_zoom.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void ground_all(Mat disp){

    //生成U V 视图
    double min,max;
    int x ,y;
    minMaxIdx (disp,&min,&max,&x,&y,noArray() ) ;
    Mat UdispMap=Mat(200,disp.cols,CV_16UC1);
    Mat VdispMap=Mat(disp.rows,200,CV_16UC1);
    computeUDisparity( UdispMap, disp);
    computeVDisparity(VdispMap,disp);    
      UdispMap.convertTo(UdispMap,CV_8UC1);
      VdispMap.convertTo(VdispMap,CV_8UC1); 
      //阈值化
     threshold(VdispMap,VdispMap,30,255,THRESH_BINARY);
     threshold(UdispMap,UdispMap,20,255,THRESH_BINARY);
     namedWindow("V",WINDOW_FREERATIO);
     namedWindow("U",WINDOW_FREERATIO);
     imshow("V",VdispMap);
     imshow("U",UdispMap);

          //直线检测
          lines_zoom*  zoom1;
      zoom1=   MethodOne(VdispMap);

};