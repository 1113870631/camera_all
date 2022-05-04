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
#include "distance.h"
#include "ground_all.h"

using namespace cv;
using namespace std;

Mat row,sgm_guiyi;    
  //立体匹配参数
    int setblock=5;
    int setNumDisparities=165;
    int setUniquenessRatio=6;
    int setSpeckleWindowSize=90;
    int setSpeckleRange=1;
    int setDisp12MaxDiff=500;
    int setMinDisparity=0;
    int p1=21;
    int p2=61;


    //立体匹配参数回调函数
        void other_Callback(int , void* )
            {  
                        if(setblock%2==0)
                        {setblock=setblock+1;}
                        Set_Sgbm();                                   
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
    Mat Q_my;
   //得到重映射矩阵  和有效区域
    jibian_zhuanhuan(& mat11,&mat12,&mat21,&mat22,&Q_my,Size(640,480),&validPixROI1,&validPixROI2);
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
    cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));//视频流格式    
//cap.open("v4l2src device=/dev/video4    !   video/x-raw,width=1280,height=480  !  videoconvert   !  appsink", cv::CAP_GSTREAMER);
//cap.open("udpsrc port=5600 ! application/x-rtp ! rtph264depay   ! decodebin ! videoconvert ! video/x-raw,format=(string)BGR ! videoconvert ! appsink sync=false max-buffers=1 drop=true ", cv::CAP_GSTREAMER);
 

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

    //多线程准备
    thread_prepare(thead_num);    

while(1)
    {           


        // t = (double)cv::getTickCount();
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // 图片分离
        picture_ex( &frame,& LIFT,&RIGHT);
    
        //注意顺序   畸变矫正
        Mat out1;
        Mat out2;      
         jibian_correct(&RIGHT,&LIFT,&out1,&out2,& mat11,&mat12,& mat21,&mat22, validPixROI1 , validPixROI2);

         //画线
         int p=0;
         for(int p=0;p<20;p++)
         {
            if(40+p*40>out1.cols)
            break;
             line(out1,Point(0,40+p*40),Point(out1.cols,40+p*40),Scalar(0, 0, 255),1,8,0);
             line(out2,Point(0,40+p*40),Point(out2.cols,40+p*40),Scalar(0, 0, 255),1,8,0);
         }
         //显示矫正图像
        Mat hconcat_pic;
         hconcat(out1,out2,hconcat_pic); 
        // imshow("矫正图像",hconcat_pic);
        
        //立体匹配  注意顺序
         Mat sgm_guiy; 
         sgm(out1,out2,&sgm_guiyi,&row,setNumDisparities);
         medianBlur(sgm_guiyi,sgm_guiyi,5);
         medianBlur(row,row,5);
         blur(sgm_guiyi,sgm_guiyi,Size(3,3),Point(-1,-1),4);
         blur(row,row,Size(3,3),Point(-1,-1),4);

         //伪彩图
         Mat im_color;
         applyColorMap(sgm_guiyi, im_color, COLORMAP_JET);
          //距离图
          mouce_distance(row,im_color);
          im_color.convertTo(im_color,CV_8UC3);
          //分离地面   障碍物检测
          ground_all(sgm_guiyi,hconcat_pic); 

          if (waitKey(5) >= 0)
          break;
    }
    return 0;
}

