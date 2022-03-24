#include  "U_V.h"
#include <iostream>
#include <opencv2/opencv.hpp>

void computeUDisparity(cv::Mat UdispMap,cv::Mat disp)
{
    UdispMap.setTo(0);
    int width=disp.cols;
    int height=disp.rows;
 
    for(int row=0;row<height;row++)
    {
        auto  pRowInDisp=disp.ptr<uchar>(row);
        for(int col=0;col<width;col++)
        {
            uint8_t currDisp=pRowInDisp[col];
            if(currDisp>0&&currDisp<128)
            {
                UdispMap.at<ushort>(currDisp,col)++;
            }
        }
    }
}


void computeVDisparity(cv::Mat &VdispMap,cv::Mat disp)
{
    VdispMap.setTo(0);
    int width=disp.cols;
    int height=disp.rows;
 
    for(int row=0;row<height;row++)
    {
        auto  pRowInDisp=disp.ptr<uchar>(row);
        for(int col=0;col<width;col++)
        {
            uint8_t currDisp=pRowInDisp[col];
            if(currDisp>0&&currDisp<128)
            {
                VdispMap.at<ushort>(row,currDisp)++;
            }
 
        }
    }
}