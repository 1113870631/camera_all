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
#include "hole.h"

using namespace cv;
using namespace std;

  //立体匹配参数
    int setblock=0;
    int setNumDisparities=143;
    int setUniquenessRatio=0;
    int setSpeckleWindowSize=0;
    int setSpeckleRange=1;
    int setDisp12MaxDiff=500;
    int setMinDisparity=0;
    int p1=0;
    int p2=192;
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

void my_ButtonCallback (int , void* ){


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
    createTrackbar("setUniquenessRatio","out4",&setUniquenessRatio,10,other_Callback);
    createTrackbar("setSpeckleWindowSize","out4",&setSpeckleWindowSize,200,other_Callback);
    createTrackbar("setSpeckleRange","out4",&setSpeckleRange,6,other_Callback);    
    createTrackbar("setDisp12MaxDiff","out4",&setDisp12MaxDiff,500,other_Callback);   
    createTrackbar("p1","out4",&p1,500,other_Callback);   
    createTrackbar("p2","out4",&p2,500,other_Callback); 
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
        

        //注意顺序   畸变矫正
        Mat out1;
        Mat out2;
         jibian_correct(&RIGHT,&LIFT,&out1,&out2,& mat11,&mat12,& mat21,&mat22, validPixROI1 , validPixROI2);
         //
         int p=0;
         for(int p=0;p<20;p++)
         {
            if(40+p*40>out1.cols)
            break;
             line(out1,Point(0,40+p*40),Point(out1.cols,40+p*40),Scalar(0, 0, 255),1,8,0);
             line(out2,Point(0,40+p*40),Point(out2.cols,40+p*40),Scalar(0, 0, 255),1,8,0);
         }
  


        
         namedWindow("out1",WINDOW_FREERATIO);
         imshow("out1",out1);
         namedWindow("out2",WINDOW_FREERATIO);
         imshow("out2",out2);

        //立体匹配  注意顺序
         Mat out4;
          sgm(out2,out1,&out4,setNumDisparities,sgbm) ;
          Mat disp=out4.colRange(setNumDisparities,out4.cols); 
         Mat disp_row=disp.clone();
         imshow("row_disp",disp_row);
         //填补空洞
         full_hole(&disp);
         imshow("disp",disp);
        

         //生成伪彩图
          Mat im_color;
          applyColorMap(disp, im_color, COLORMAP_JET);
         namedWindow("out5",WINDOW_FREERATIO);
          imshow("out5",im_color);


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

