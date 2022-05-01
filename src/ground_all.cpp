#include "ground_all.h"
#include "U_V.h"
#include "line_zoom.h"
#include "Obstacle_detection.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <rectangle_uv.h>
#include <ground_ex.h>

using namespace std;
using namespace cv;
extern int  setNumDisparities;
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
    Mat UdispMap=Mat(setNumDisparities,disp.cols,CV_16UC1);
    Mat VdispMap=Mat(disp.rows,setNumDisparities,CV_16UC1);
    computeUDisparity( UdispMap, disp);
    computeVDisparity(VdispMap,disp);    
    UdispMap.convertTo(UdispMap,CV_8UC1);
     VdispMap.convertTo(VdispMap,CV_8UC1); 
      //阈值化
     threshold(VdispMap,VdispMap,20,255,THRESH_BINARY);
     threshold(UdispMap,UdispMap,10,255,THRESH_BINARY);
    medianBlur(UdispMap,UdispMap,3);
    transpose(UdispMap, UdispMap);
    flip(UdispMap, UdispMap, 0);

    Mat U_V;
    vconcat(VdispMap,UdispMap,U_V);
     //namedWindow("U_V",WINDOW_FREERATIO);
     imshow("U_V",U_V);
        //连通区域 矩形框选
	    int lables_num_u,lables_num_v;	
       
        Mat labels_v  = Mat::zeros(VdispMap.size(), CV_32S);
	 	Mat labels_u = Mat::zeros(UdispMap.size(), CV_32S);
	
		Mat status_u = Mat::zeros(UdispMap.size(), CV_32S);
        Mat status_v = Mat::zeros(VdispMap.size(), CV_32S);
        vector<Vec4f>abstract_line_v;
        vector<Vec4f>ground_line_v;
        vector<Vec4f>u_line;
    //连通区域检测
         //第一次V 视图处理 连通区域检测
     connected_components_stat(VdispMap,"v_lian",labels_v,status_v,lables_num_u,abstract_line_v,ground_line_v,u_line);
        //地面直线过滤   计算地面 更准确
    Ground_line_Deal(ground_line_v,VdispMap);
        //第二次V 视图处理    将地面与障碍物直线分割开来
    Ground_Obstacle__Line_deal(abstract_line_v,ground_line_v, VdispMap);
    //地面直线与障碍物直线分离开后再次连通区域检测
    abstract_line_v.clear();
    ground_line_v.clear();
     connected_components_stat(VdispMap,"v_lian",labels_v,status_v,lables_num_u,abstract_line_v,ground_line_v,u_line);
     connected_components_stat(UdispMap,"u_lian",labels_u,status_u,lables_num_v,abstract_line_v,ground_line_v,u_line);
    
      // 地面分离
    //地面直线过滤   分离地面跟准确
    Ground_line_Deal(ground_line_v,VdispMap);
     Ground_Ex_line(ground_line_v, disp);
     //障碍物直线处理 障碍物提取
     Obstacle_line_Deal(ground_line_v,VdispMap);
     Obstacle_detection(abstract_line_v,u_line,disp); 
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
