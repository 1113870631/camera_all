#include "sgm.h"
#include <iostream>
#include <opencv2/opencv.hpp>
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

#define thead_num 180
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
            int row=grayLeft.rows;
            int col=grayLeft.cols;
            int tmp=0;
            while(row%thead_num!=0)
            {  //不是16的整数倍  舍弃一行
                row--;
                tmp++;
            }    
           int per_row=row/thead_num;//每份图片的行数
           Mat tmp_r,tmp_l;
            tmp_l = grayLeft.rowRange(tmp,grayLeft.rows);//得到裁减后的图片
            tmp_r =  grayRight.rowRange(tmp,grayLeft.rows);//得到裁减后的图片
            //复制给图片数组
            /**
             * @brief 
             * 0            9
             * 10        19
             * 20        29     
             */
      // #pragma omp parallel
        {
          // #pragma omp for
            for(int p=0;p<thead_num;p++)//分份
                {
                    per_left[p]=tmp_l.rowRange(0+p*per_row,(per_row-1)+p*per_row);
                    per_right[p]=tmp_r.rowRange(0+p*per_row,(per_row-1)+p*per_row);
                }
        }
        double t = (double)cv::getTickCount();
    //  #pragma omp parallel
        {
          // #pragma omp for
                    for(int i=0;i<thead_num;i++) //立体匹配
                    {
                                sgbm->compute(per_left[i], per_right[i], im3[i]);
                    }
        }
        t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
        //cout<<t<<"\n";
            
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

