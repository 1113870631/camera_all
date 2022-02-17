#include "sgm.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include </usr/include/opencv2/calib3d/calib3d_c.h>
#include "omp.h"
using namespace cv;
using namespace std;
  
    
    

/**
 * @brief
 * @Mat lift
 * @Mat rigit
 * @Mat *out
 * @int setNumDisparities 
 * @int setblock 
     @int  setUniquenessRatio
     @nt setSpeckleWindowSize, 
     @int setSpeckleRange 
    @nt setDisp12MaxDiff 
    @cv::Ptr<cv::StereoSGBM> sgbm
 */
void sgm(Mat lift,Mat rigit,Mat *out,int setNumDisparities,cv::Ptr<cv::StereoSGBM> sgbm)  {

            Mat grayLeft,grayRight,grayLeft_h,grayRight_h, im3;

            cvtColor(lift,grayLeft,COLOR_BGR2GRAY);
            cvtColor(rigit,grayRight,COLOR_BGR2GRAY);
            grayLeft_h=grayLeft;
            grayRight_h=grayRight;
            sgbm->compute(grayLeft_h, grayRight_h, im3);
            im3.convertTo(im3, CV_16S); 
            im3.convertTo(im3,CV_8UC1,255 / (setNumDisparities*16.0));//归一化  十分重要

            *out=im3;
};








  
