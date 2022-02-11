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

using namespace cv;
using namespace std;

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
     jibian_zhuanhuan(& mat11,&mat12,&mat21,&mat22,Size(320,240),&validPixROI1,&validPixROI2);

    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 4;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    cap.set(CAP_PROP_FRAME_WIDTH,640);
    cap.set(CAP_PROP_FRAME_HEIGHT,240);

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
        //左右图片显示

        //畸变矫正
        Mat out1;
        Mat out2;
        Mat out3;
      jibian_correct(&LIFT,&RIGHT,&out1,&out2,& mat11,&mat12,& mat21,&mat22, validPixROI1 , validPixROI2);
        namedWindow("out1",WINDOW_FREERATIO);
        imshow("out1", out1);
        namedWindow("out2",WINDOW_FREERATIO);
        imshow("out2", out2);
        cout<<out1.size<<"\n"<<endl;
         cout<<out2.size<<"\n"<<endl;
        //hconcat(out1,out2,out3);
        //namedWindow("out3",WINDOW_FREERATIO);
        //imshow("out3", out3);
        //立体匹配

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




