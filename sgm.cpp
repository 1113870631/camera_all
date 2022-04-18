#include "sgm.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "omp.h"
#include <CL/cl.h>
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

#define thead_num 16
void sgm(Mat lift,Mat rigit,Mat *out,Mat *row_pic,int setNumDisparities,cv::Ptr<cv::StereoSGBM> sgbm)  {

           Mat grayLeft,grayRight;
            //分成16分 分别进行立体匹配
           Mat per_left[thead_num];
           Mat per_right[thead_num];
            Mat im3[thead_num];
             //转化为灰度图
            cvtColor(lift,grayLeft,COLOR_BGR2GRAY);
            cvtColor(rigit,grayRight,COLOR_BGR2GRAY);
            //分份
            int del=(lift.rows)%thead_num;
            int per=(lift.rows-del)/thead_num;
            Mat pic_del_l=grayLeft.rowRange(del,lift.rows);
            Mat pic_del_r=grayRight.rowRange(del,lift.rows);
            for(int tmp=0;tmp<thead_num;tmp++){
                per_right[tmp]=pic_del_r.rowRange(tmp*per,per*(1+tmp));
                per_left[tmp]=pic_del_l.rowRange(tmp*per,per*(1+tmp));
            }      
                    for(int i=0;i<thead_num;i++) //立体匹配
                    {
                                sgbm->compute(per_left[i], per_right[i], im3[i]);
                    }
              Mat out1;
            //拼合图像
            vconcat(im3,thead_num,out1);
            //输出原视差图
            *row_pic=out1;
            //输出归一化视差图
             out1.convertTo(out1, CV_16S); 
             out1.convertTo(out1,CV_8UC1,255 / (setNumDisparities*16.0));//归一化  十分重要
            *out=out1;
};


