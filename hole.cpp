#include "hole.h"
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
#define  size_full  10

void full_hole(cv::Mat * disp)
{   //生成积分图
     int xo,yo,height,width;
    Mat sum_img = Mat::zeros((*disp).rows + 1, (*disp).cols + 1, CV_32FC1);
	Mat sqsum_img = Mat::zeros((*disp).rows + 1, (*disp).cols + 1, CV_64FC1);
	integral(*disp, sum_img, sqsum_img);

    //遍历图像寻找感性区域
    /**
     * @brief 
     * black point
     * ********************************
     * XO,YO               weight   tmp_x      *
     *                                                                *
     *                                                                *
     *                                                                *
     *                                                                *
     * hight   tmp_y                                    *  
     *                                                                *
     * *******************************
     * 
     */

    for(int i=0;i<(*disp).rows;i++)
    {
        for(int j=0;j<(*disp).cols;j++)
        {//遍历图像
           if( (*disp).at<uchar>(i,j) ==0)
           {

             int tmp_weight=1;
              int tmp_hight=1;
                 //获得空洞宽度
                 while((*disp).at<uchar>(i,j++) ==0)
                 {
                      tmp_weight++;
                     //判断是否达到边界
                     if(j==(*disp).cols)
                     {
                         j++;
                         break;
                     }   
                 }
                 j=j-tmp_weight;
                     //获得空洞长度
                 while((*disp).at<uchar>(i++,j) ==0)
                 {
                    tmp_hight++;
                     //判断是否达到边界
                     if(i==(*disp).rows)
                     {
                         i++;
                         break;
                     }
                     
                 }
                  i=i-tmp_hight;  

                              xo=j;
                              yo=i;
          //积分图计算感性区域 像素总和
                int roi_weight=xo + tmp_weight+20;
                int  roi_hight=yo +tmp_hight+20;
                 if(roi_weight>(*disp).cols)
                  {
                      roi_weight=(*disp).cols;
                  }
                    if(roi_hight>(*disp).rows)
                  {
                      roi_hight=(*disp).rows;
                  }  
                int integral_value = sum_img.at<int>(yo + tmp_hight, xo + tmp_weight) - sum_img.at<int>(yo + tmp_hight, xo)
                - sum_img.at<int>(yo, xo + tmp_weight)
                + sum_img.at<int>(yo, xo);

                 (*disp).at<uchar>(i,j) =integral_value/((roi_hight)*(roi_weight)-tmp_hight*tmp_weight);
                //cout<<"high"<<tmp_hight<<"\n";
                //cout<<"weight"<<tmp_weight<<"\n";

                //cout<<"with:"<<tmp_with<<"\n"<<endl;
           }
                       
        }
    }
}









