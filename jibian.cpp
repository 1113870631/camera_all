#include "jibian.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>
#include <opencv2/imgproc/imgproc_c.h>


/**
 * @brief 
 * 计算重映射矩阵
 * 
 * @param mat11  重映射矩阵11
 * @param mat12   重映射矩阵12
 * @param mat21   重映射矩阵21
 * @param mat22   重映射矩阵22
 */
void jibian_zhuanhuan(Mat * mat11,Mat *mat12,Mat * mat21,Mat *mat22,Size size,Rect *validPixROI1 ,Rect* validPixROI2 )
{
    Mat cameraMatrix1 = Mat::zeros(3, 3, CV_64F);
    Mat cameraMatrix2 = Mat::zeros(3, 3, CV_64F);
    Mat distCoeffs1 = Mat::zeros(5, 1, CV_64F);
    Mat distCoeffs2 = Mat::zeros(5, 1, CV_64F);
    Mat R = Mat::zeros(3, 3, CV_64F);
    Mat T = Mat::zeros(3, 1, CV_64F);
    Mat P1 = Mat::zeros(3, 4, CV_64F);
    Mat P2 = Mat::zeros(3, 4, CV_64F);
    Mat R1 = Mat::zeros(3, 3, CV_64F);
    Mat R2 = Mat::zeros(3, 3, CV_64F);
    Mat Q;
    Mat RR=Mat::zeros(3, 3, CV_64F);
     
 if(size==Size(1280,720))
    {
         //相机一 内参
    cameraMatrix1.at<double>(0, 0) = 1.3513e+03;
    cameraMatrix1.at<double>(0, 1) = 0;
    cameraMatrix1.at<double>(0, 2) = 628.1604;

    cameraMatrix1.at<double>(1, 0) = 0;
    cameraMatrix1.at<double>(1, 1) = 1.3511e+03;
    cameraMatrix1.at<double>(1, 2) = 383.6009;

    cameraMatrix1.at<double>(2, 0) = 0;
    cameraMatrix1.at<double>(2, 1) = 0;
    cameraMatrix1.at<double>(2, 2) = 1;
    //相机二 内参
    cameraMatrix2.at<double>(0, 0) = 1.3556e+03;
    cameraMatrix2.at<double>(0, 1) = 0;
    cameraMatrix2.at<double>(0, 2) = 691.5902;

    cameraMatrix2.at<double>(1, 0) = 0;
    cameraMatrix2.at<double>(1, 1) = 1.3555e+03;
    cameraMatrix2.at<double>(1, 2) = 412.2236;

    cameraMatrix2.at<double>(2, 0) = 0;
    cameraMatrix2.at<double>(2, 1) = 0;
    cameraMatrix2.at<double>(2, 2) = 1;
    //相机一   畸变参数
     distCoeffs1.at<double>(0, 0) = -0.4356; // k1
    distCoeffs1.at<double>(1, 0) = 0.2390;  // k2
    distCoeffs1.at<double>(2, 0) = 0; //p1
    distCoeffs1.at<double>(3, 0) = 0; //p2
    distCoeffs1.at<double>(4, 0) = 0; //k3
    //相机二  畸变参数 
     distCoeffs2.at<double>(0, 0) = -0.4401; // k1
    distCoeffs2.at<double>(1, 0) = 0.2626;  // k2
    distCoeffs2.at<double>(2, 0) = 0; //p1
    distCoeffs2.at<double>(3, 0) = 0; //p2
    distCoeffs2.at<double>(4, 0) = 0; //k3

    //旋转转换矩阵
    R.at<double>(0, 0) = 1;
    R.at<double>(0, 1) = -1.9888e-04;
    R.at<double>(0, 2) = -0.0061;

    R.at<double>(1, 0) = -2.2428e-04;
    R.at<double>(1, 1) = 1;
    R.at<double>(1, 2) = -0.0042;

    R.at<double>(2, 0) = 0.0061;
    R.at<double>(2, 1) = 0.0042;
    R.at<double>(2, 2) = 1;
    //平移
    T.at<double>(0, 0) = 60.0013;
    T.at<double>(1, 0) = -0.1181;
    T.at<double>(2, 0) = 0.3540;
    }
    else if(size==Size(320,240))
    {
         //相机一 内参
    cameraMatrix1.at<double>(0, 0) = 453.3683;
    cameraMatrix1.at<double>(0, 1) = 0;
    cameraMatrix1.at<double>(0, 2) = 159.6383;

    cameraMatrix1.at<double>(1, 0) = 0;
    cameraMatrix1.at<double>(1, 1) = 453.2678;
    cameraMatrix1.at<double>(1, 2) = 133.7621;

    cameraMatrix1.at<double>(2, 0) = 0;
    cameraMatrix1.at<double>(2, 1) = 0;
    cameraMatrix1.at<double>(2, 2) = 1;
    //相机二 内参
    cameraMatrix2.at<double>(0, 0) = 455.1281;
    cameraMatrix2.at<double>(0, 1) = 0;
    cameraMatrix2.at<double>(0, 2) = 176.3203;

    cameraMatrix2.at<double>(1, 0) = 0;
    cameraMatrix2.at<double>(1, 1) = 454.9641;
    cameraMatrix2.at<double>(1, 2) = 138.4340;

    cameraMatrix2.at<double>(2, 0) = 0;
    cameraMatrix2.at<double>(2, 1) = 0;
    cameraMatrix2.at<double>(2, 2) = 1;
    //相机一   畸变参数
     distCoeffs1.at<double>(0, 0) = -0.4352; // k1
    distCoeffs1.at<double>(1, 0) = 0.2152;  // k2
    distCoeffs1.at<double>(2, 0) = 0; //p1
    distCoeffs1.at<double>(3, 0) = 0; //p2
    distCoeffs1.at<double>(4, 0) = 0; //k3
    //相机二  畸变参数 
     distCoeffs2.at<double>(0, 0) = -0.4492; // k1
    distCoeffs2.at<double>(1, 0) = 0.3226;  // k2
    distCoeffs2.at<double>(2, 0) = 0; //p1
    distCoeffs2.at<double>(3, 0) = 0; //p2
    distCoeffs2.at<double>(4, 0) = 0; //k3

    //旋转转换矩阵
    R.at<double>(0, 0) = 1;
    R.at<double>(0, 1) = 1.7893e-04;
    R.at<double>(0, 2) = -0.0039;

    R.at<double>(1, 0) = -1.8727e-04;
    R.at<double>(1, 1) = 1;
    R.at<double>(1, 2) = -0.0021;

    R.at<double>(2, 0) = 0.0039;
    R.at<double>(2, 1) = 0.0021;
    R.at<double>(2, 2) = 1;
    //平移
    T.at<double>(0, 0) = 60.0013;
    T.at<double>(1, 0) = -0.1062;
    T.at<double>(2, 0) = 0.5076;
    }
    else{

    
      //相机一 内参    640  x  480
    cameraMatrix1.at<double>(0, 0) = 901.2256;
    cameraMatrix1.at<double>(0, 1) = 0;
    cameraMatrix1.at<double>(0, 2) = 313.5635;

    cameraMatrix1.at<double>(1, 0) = 0;
    cameraMatrix1.at<double>(1, 1) = 901.4860;
    cameraMatrix1.at<double>(1, 2) = 256.2747;

    cameraMatrix1.at<double>(2, 0) = 0;
    cameraMatrix1.at<double>(2, 1) = 0;
    cameraMatrix1.at<double>(2, 2) = 1;
    //相机二 内参
    cameraMatrix2.at<double>(0, 0) = 903.8482;
    cameraMatrix2.at<double>(0, 1) = 0;
    cameraMatrix2.at<double>(0, 2) = 349.9874;

    cameraMatrix2.at<double>(1, 0) = 0;
    cameraMatrix2.at<double>(1, 1) = 903.5536;
    cameraMatrix2.at<double>(1, 2) = 275.5857;

    cameraMatrix2.at<double>(2, 0) = 0;
    cameraMatrix2.at<double>(2, 1) = 0;
    cameraMatrix2.at<double>(2, 2) = 1;
    //相机一   畸变参数
     distCoeffs1.at<double>(0, 0) = -0.4207; // k1
    distCoeffs1.at<double>(1, 0) = 0.2110;  // k2
    distCoeffs1.at<double>(2, 0) = 0; //p1
    distCoeffs1.at<double>(3, 0) = 0; //p2
    distCoeffs1.at<double>(4, 0) = 0; //k3
    //相机二  畸变参数 
     distCoeffs2.at<double>(0, 0) = -0.4357; // k1
    distCoeffs2.at<double>(1, 0) = 0.2674;  // k2
    distCoeffs2.at<double>(2, 0) = 0; //p1
    distCoeffs2.at<double>(3, 0) = 0; //p2
    distCoeffs2.at<double>(4, 0) = 0; //k3

    //旋转转换矩阵
    R.at<double>(0, 0) = 1;
    R.at<double>(0, 1) = 2.3909e-05;
    R.at<double>(0, 2) = -0.00118;

    R.at<double>(1, 0) = -1.6736e-04;
    R.at<double>(1, 1) = 1;
    R.at<double>(1, 2) = -0.0122;

    R.at<double>(2, 0) = 0.0118;
    R.at<double>(2, 1) = 0.0122;
    R.at<double>(2, 2) = 1;
    //平移
    T.at<double>(0, 0) = 61.2179;
    T.at<double>(1, 0) = 1.4210;
    T.at<double>(2, 0) = -0.0466;

    }
    

        stereoRectify( cameraMatrix1,  distCoeffs1,
                                  cameraMatrix2,  distCoeffs2,
                                 size,  R,  T,
                                  R1,  R2,
                                  P1,  P2,
                                  Q,  CALIB_ZERO_DISPARITY,
                                  0,  size,validPixROI1,validPixROI2);//  0 为重要参数

      initUndistortRectifyMap( cameraMatrix1,  distCoeffs1,R1,P1,size, CV_32FC1,  *mat11, * mat12 ); 
      initUndistortRectifyMap( cameraMatrix2,  distCoeffs2,R2,P2,size, CV_32FC1,  *mat21, * mat22 ); 
   }

/**
 * @brief 
 * 畸变矫正 重映射
 * 
 * @param mat_l  输入左图像
 * @param mat_r  输入右图像
 *  @param mat_l_o  输出左图像
 * @param  mat_r_o   输出右图像 
 * @param mat11 重映射矩阵11
 * @param mat12  重映射矩阵12
 * @param mat21  重映射矩阵21
 * @param mat22  重映射矩阵22
 */
void jibian_correct(Mat * mat_l,Mat *mat_r,Mat * mat_l_o,Mat *mat_r_o,Mat * mat11,Mat *mat12,Mat * mat21,Mat *mat22,Rect validPixROI1 ,Rect validPixROI2){

     remap(*mat_l,*mat_l_o,*mat11,*mat12,INTER_LINEAR,BORDER_TRANSPARENT,0);
     remap(*mat_r,*mat_r_o,*mat21,*mat22,INTER_LINEAR,BORDER_TRANSPARENT,0);

     *mat_l_o=(*mat_l_o).colRange(validPixROI1.x,validPixROI1.width+validPixROI1.x);
     *mat_l_o=(*mat_l_o).rowRange(validPixROI1.y,validPixROI1.y+validPixROI1.height);
     *mat_r_o=(*mat_r_o).colRange(validPixROI2.x,validPixROI2.width+validPixROI2.x);
     *mat_r_o=(*mat_r_o).rowRange(validPixROI2.y,validPixROI2.y+validPixROI2.height); 
     
    
     
     
};









