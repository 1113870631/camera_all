#include "ground_ex.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <math.h>

using namespace   std;
using namespace   cv;

void ground_ex(lines_zoom * zoom,Mat v   ,Mat  disp)
{
    double tmp_dis=0;
    int tmp_num=0;
    Mat dst3(v.rows,v.cols,CV_8UC1,255);
    cvtColor(dst3,dst3,COLOR_GRAY2BGR);
    vector<one_k_clss_line>::iterator it;
    vector<one_k_clss_line>::iterator it_end;
    vector<Vec4f>::iterator it_4f;
    disp.convertTo(disp,CV_8UC1);
  for(it=zoom->k_class.begin();it!=zoom->k_class.end();it++)
  {//遍历所有k_class 
      if((*it).k_present<5)
      {//筛选k_class   选出符合条件的k_class 的长度最长的那个
         //   斜率小于5 都符合   选出斜率小于5   长度最长的那个k_class 
          vector<Vec4f>::iterator it2;
          it2=(*it).line_point_data.begin();  
          cv::Vec4i line_point = *it2;
          double dis=sqrt(((line_point)[3]-(line_point)[1]) * ((line_point)[3]-(line_point)[1])+((line_point)[2]-(line_point)[0]) * ((line_point)[2]-(line_point)[0]));
          cout<<"k:"<<(*it).k_present<<endl;
          cout<<"d:"<<(*it).dis_preset<<endl;
          cout<<"dis:"<<dis<<endl;
          cout<<cv::Point(line_point[0],line_point[1])<<cv::Point(line_point[2],line_point[3])<<endl;
          cout<<"\n"<<endl;
          
          line(dst3,cv::Point(line_point[0],line_point[1]),cv::Point(line_point[2],line_point[3]), cv::Scalar(255, 0, 0), 2);
          
          if(tmp_num==0){//第一次tmp_dis    it_end 赋初值  
          tmp_dis=dis;
          it_end=it;
          }

          if(dis>tmp_dis){//找到更大的dis 更新tmp_dis  和 it_end
            it_end=it;
            tmp_dis=dis;
          }
          //更新tmp_num
          tmp_num++;
     }   
  } 
    namedWindow("ground",WINDOW_FREERATIO);
    imshow("ground",dst3);

    //得到目标 直线点
    it_4f = it_end->line_point_data.begin();
    cout<<*it_4f<<endl;
    //得到y=kx+b
    double tmp_k=((*it_4f)[3]-(*it_4f)[1])/((*it_4f)[2]-(*it_4f)[0]);
    // y=kx+b   b=y-kx
    double tmp_b=(*it_4f)[3]-tmp_k*(*it_4f)[2];

    /*遍历图像 
     * 寻找符合y=kx+b 的点
     * y表示视差 x 表示 v 坐标  
     *                                             
     *                                              *
     *                                              *
     *                    **************************      -mid_rows
     *                    *                        *                          *
     *        * *****************************************      U
     *                    *                        *                          *
     *                    ***************************   mid_rows
     *                                                *
     *                                                *
     *                                                *    V
     * 已知 V 和视差  按 V 坐标方向 寻找符合视差的点
     */                       


    //1 寻找视差图中心坐标
    int mid_rows=disp.rows/2;
    int min_cols=disp.cols/2;
    for(int tmp_v=0;tmp_v<disp.rows;tmp_v++)
    {

              
         if(tmp_v<(*it_4f)[3]&&tmp_v>(*it_4f)[1])
         {
                    //计算目标视差
                double tmp_disp=(tmp_v-tmp_b)/tmp_k;
                //遍历这一行 寻找符合该视差的点
                for(int tmp_U=0;tmp_U<disp.cols;tmp_U++)
                {
                    uchar *data = disp.ptr<uchar>(tmp_v, tmp_U);
                    if((int)(*data)-tmp_disp<10&&(int)(*data)-tmp_disp>-10)
                    *data=0;
                    //cout<<(int)*data<<endl;
                
                }
        }
       

    }
    //imshow("disp",disp);
};

#define Ground_err 10
//分离地面
void Ground_Ex_line(vector<Vec4f>ground_line_v, Mat  &disp,Mat & color_picture){
    //为空返回
    if(ground_line_v.empty()){
        return;
    }
//处理障碍物和地面直线
     vector<Vec4f>::iterator it;
     //disp=k*v+b
     double x1,y1,x2,y2;
     for(it=ground_line_v.begin();it!=ground_line_v.end();it++){
         x1+=(*it)[0];
         y1+=(*it)[1];
         x2+=(*it)[2];
         y2+=(*it)[3];
     }
     x1/=ground_line_v.size();
     x2/=ground_line_v.size();
     y1/=ground_line_v.size();
     y2/=ground_line_v.size();
    //得到y=kx+b
    double tmp_k=(y2-y1)/(x2-x1);
    // y=kx+b   b=y-kx
    double tmp_b=y2-tmp_k*x2;

    //地面检测
        //1 寻找视差图中心坐标
    int mid_rows=disp.rows/2;
    int min_cols=disp.cols/2;
    for(int tmp_v=0;tmp_v<disp.rows;tmp_v++)
    {         
        // if(tmp_v<(*it_4f)[3]&&tmp_v>(*it_4f)[1])
         {
                    //计算目标视差
                double tmp_disp=(tmp_v-tmp_b)/tmp_k;
                //遍历这一行 寻找符合该视差的点
                for(int tmp_U=0;tmp_U<disp.cols;tmp_U++)
                {
                    uchar *data = disp.ptr<uchar>(tmp_v, tmp_U);
                    if((int)(*data)-tmp_disp<Ground_err&&(int)(*data)-tmp_disp>-Ground_err)
                   { *data=0;
                    color_picture.at<Vec3b>(tmp_v,tmp_U)=0;
                    }
                    //cout<<(int)*data<<endl;               
                }
        }          
    }
       Mat disp_color;
        applyColorMap(disp, disp_color, COLORMAP_JET);
        imshow("disp_without_ground",disp_color);
}




