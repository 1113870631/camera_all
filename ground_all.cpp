#include "ground_all.h"
#include "U_V.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void ground_all(cv::Mat disp){
    double min,max;
    int x ,y;
   minMaxIdx 	( disp,&min,&max,&x,&y,noArray() ) ;
  Mat UdispMap=Mat(500,disp.cols,CV_16UC1);
  Mat VdispMap=Mat(disp.rows,500,CV_16UC1);
   computeUDisparity( UdispMap, disp);
    computeVDisparity(VdispMap,disp);

      UdispMap.convertTo(UdispMap,CV_8UC1);
      VdispMap.convertTo(VdispMap,CV_8UC1); 
     threshold(VdispMap,VdispMap,20,255,THRESH_BINARY);
     threshold(UdispMap,UdispMap,50,255,THRESH_BINARY);
     imshow("V",VdispMap);
     imshow("u",UdispMap);

};