#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <string.h>

#include "picture_ex.h"
#include "jibian.h"
#include "sgm.h"

using namespace cv;
using namespace std;


  //立体匹配参数
    int setblock=1;
    int setNumDisparities=10;
    int setUniquenessRatio=10;
    int setSpeckleWindowSize=100;
    int setSpeckleRange=32;
    int setDisp12MaxDiff=1;
    int setMinDisparity=-50;
    int p1=8;
    int p2=32;
    int MD=1;
    cv::Ptr<cv::StereoSGBM> sgbm= cv::StereoSGBM::create(0,9, setblock);

    //立体匹配参数回调函数
        void other_Callback(int , void* )
            {  
                        if(setblock%2==0)
                        {setblock=setblock+1;}
                         if(MD%2==0)
                        {MD=MD+1;}

                        sgbm->setBlockSize(setblock);
                        sgbm->setNumDisparities(setNumDisparities);
                        sgbm->setP1(p1 * 1*setblock*setblock);
                        sgbm->setP2(p2 * 1*setblock*setblock);  
                        sgbm->setUniquenessRatio(setUniquenessRatio);
                        sgbm->setSpeckleWindowSize(setSpeckleWindowSize);
                        sgbm->setSpeckleRange(setSpeckleRange);
                        sgbm->setDisp12MaxDiff(setDisp12MaxDiff);
                         sgbm->setMinDisparity(setMinDisparity);

            };


int main()
{
    Rect validPixROI1;
    Rect validPixROI2;
    Mat frame; 
    Mat LIFT; 
    Mat RIGHT; 
    Mat  mat11;
    Mat  mat12;
    Mat  mat21;
    Mat  mat22;

     //得到重映射矩阵  和有效区域
     jibian_zhuanhuan(& mat11,&mat12,&mat21,&mat22,Size(640,480),&validPixROI1,&validPixROI2);

    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 4;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    cap.set(CAP_PROP_FRAME_WIDTH,1280);
    cap.set(CAP_PROP_FRAME_HEIGHT,480);

    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
        double t=0;
        double fps=0;


    //设置参数调整bar
    namedWindow("out4",WINDOW_FREERATIO);
    createTrackbar("setNumDisparities","out4",&setNumDisparities,512,other_Callback);
    createTrackbar("setblock","out4",&setblock,21,other_Callback);
    createTrackbar("setUniquenessRatio","out4",&setUniquenessRatio,500,other_Callback);
    createTrackbar("setSpeckleWindowSize","out4",&setSpeckleWindowSize,500,other_Callback);
    createTrackbar("setSpeckleRange","out4",&setSpeckleRange,200,other_Callback);    
    createTrackbar("setDisp12MaxDiff","out4",&setDisp12MaxDiff,100,other_Callback);   
    createTrackbar("p1","out4",&p1,21,other_Callback);   
    createTrackbar("p2","out4",&p2,21,other_Callback); 
    createTrackbar("setMinDisparity","out4",&setMinDisparity,100,other_Callback);
    createTrackbar("MD","out4",&MD,100,other_Callback);                  
        if(setblock%2==0)
            {setblock=setblock+1;}
            sgbm->setBlockSize(setblock);
            sgbm->setNumDisparities(setNumDisparities);
            sgbm->setP1(p1 * 1*setblock*setblock);
            sgbm->setP2(p2 * 1*setblock*setblock);  
            sgbm->setUniquenessRatio(setUniquenessRatio);
            sgbm->setSpeckleWindowSize(setSpeckleWindowSize);
            sgbm->setSpeckleRange(setSpeckleRange);
            sgbm->setDisp12MaxDiff(setDisp12MaxDiff);
            sgbm->setMinDisparity(setMinDisparity);
while(1)
    {
         t = (double)cv::getTickCount();
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // 图片分离
        picture_ex( &frame,& RIGHT,&LIFT);

        //畸变矫正
        Mat out1;
        Mat out2;
        Mat out3;
         jibian_correct(&LIFT,&RIGHT,&out1,&out2,& mat11,&mat12,& mat21,&mat22, validPixROI1 , validPixROI2);
         namedWindow("LIFT",WINDOW_FREERATIO);
         imshow("LIFT",LIFT);
        //立体匹配
        Mat out4;
         sgm(out1,out2,&out4,setNumDisparities,sgbm) ;
         medianBlur(out4, out4, MD);
         
         imshow("out4",out4);

          t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
            fps = 1.0 / t;

            cout<<fps<<endl;
            cout<<"\n"<<endl;
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;


}




