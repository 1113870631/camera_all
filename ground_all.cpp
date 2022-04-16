#include "ground_all.h"
#include "U_V.h"
#include "line_zoom.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <rectangle_uv.h>
using namespace std;
using namespace cv;

void disp_per_deal(Mat & disp);//视差图预处理  加横格


/**
 * @brief 
 * 根据视差图生成u  v  视图 并进行地面和障碍物直线提取
 * 进行地面剔除
 * @param disp  视差图
 * 大致流程   
 *                    生成U——V视差图      阈值化 
 *                    连通区域检测                区域检测   区域过滤
 *                   直线提取                          根据区域 提取直线
 *                  公式计算                           公式计算
 */
void ground_all(Mat disp){
    //生成U V 视图
    double min,max;
    int x ,y;
	disp_per_deal(disp);
	imshow("tmp",disp);
    minMaxIdx (disp,&min,&max,&x,&y,noArray() ) ;
    Mat UdispMap=Mat(200,disp.cols,CV_16UC1);
    Mat VdispMap=Mat(disp.rows,200,CV_16UC1);
    computeUDisparity( UdispMap, disp);
    computeVDisparity(VdispMap,disp);    
    UdispMap.convertTo(UdispMap,CV_8UC1);
     VdispMap.convertTo(VdispMap,CV_8UC1); 
      //阈值化
     threshold(VdispMap,VdispMap,30,255,THRESH_BINARY);
     threshold(UdispMap,UdispMap,20,255,THRESH_BINARY);
     namedWindow("V",WINDOW_FREERATIO);
     namedWindow("U",WINDOW_FREERATIO);
     imshow("V",VdispMap);
     imshow("U",UdispMap);
        //连通区域 矩形框选
	    int lables_num_u,lables_num_v;	
       
        Mat labels_v = Mat::zeros(VdispMap.size(), CV_32S);
	 	Mat labels_u = Mat::zeros(UdispMap.size(), CV_32S);
	
		Mat status_u,status_v;

     connected_components_stat(VdispMap,"v_lian",labels_v,status_v,lables_num_u);
     connected_components_stat(UdispMap,"u_lian",labels_u,status_u,lables_num_v);
     //矩形处理
    rectangle_deal(status_v,lables_num_v);


          //直线检测
       //   lines_zoom*  zoom1;
      //zoom1=   MethodOne(VdispMap);

};

void disp_per_deal(Mat & disp){

	int hight =disp.rows;
	int weight =disp.cols;
	int per=hight/5;
	for (int i =0;i<5;i++){
		int tmp = per*i;
		for(int j=0;j<weight;j++){
			disp.at<double>(tmp,j)=0;
			disp.at<double>(tmp+1,j)=0;
		}
	}
};
