#include "ground_all.h"
#include "U_V.h"
#include "line_zoom.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
using namespace std;
using namespace cv;

void connected_components(Mat& image,string win_name);        //不带统计信息
void connected_components_stat(Mat& image,string win_name);
RNG rng(123);
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
    minMaxIdx (disp,&min,&max,&x,&y,noArray() ) ;
    Mat UdispMap=Mat(200,disp.cols,CV_16UC1);
    Mat VdispMap=Mat(disp.rows,200,CV_16UC1);
    computeUDisparity( UdispMap, disp);
    computeVDisparity(VdispMap,disp);    
    UdispMap.convertTo(UdispMap,CV_8UC1);
     VdispMap.convertTo(VdispMap,CV_8UC1); 
      //阈值化
     threshold(VdispMap,VdispMap,30,255,THRESH_BINARY);
     threshold(UdispMap,UdispMap,30,255,THRESH_BINARY);
     namedWindow("V",WINDOW_FREERATIO);
     namedWindow("U",WINDOW_FREERATIO);
     imshow("V",VdispMap);
     imshow("U",UdispMap);
     //connected_components(VdispMap);
     connected_components_stat(VdispMap,"v_lian");
    // connected_components(VdispMap);
     connected_components_stat(UdispMap,"u_lian");

          //直线检测
       //   lines_zoom*  zoom1;
      //zoom1=   MethodOne(VdispMap);

};


void connected_components(Mat& image,string win_name) {
    //计算连通域
	Mat labels = Mat::zeros(image.size(), CV_32S);
	int num_labels = connectedComponents(image, labels, 8, CV_32S);
 
	//使用不同的颜色标记连通域
	vector<Vec3b> color(num_labels);
	color[0] = Vec3b(0, 0, 0);                                                           //设置背景颜色
	for (size_t i = 1; i < num_labels; i++){
		color[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256)); //设置目标颜色
	}
 
	Mat dst = Mat::zeros(image.size(), image.type());
	int w = image.cols;
	int h = image.rows;
    //遍历图像标签 填色
    cvtColor(dst,dst,COLOR_GRAY2BGR);
	for (size_t row = 0; row < h; row++){
		for (size_t col = 0; col < w; col++){
			int label = labels.at<int>(row, col);
			if (label == 0) continue;
			dst.at<Vec3b>(row, col) = color[label] ;
		}
	}
    namedWindow(win_name,WINDOW_FREERATIO);
	imshow("win_name", dst); 
};


 
 
void connected_components_stat(Mat& image,string win_name) {
 
	//计算连通域
	Mat labels = Mat::zeros(image.size(), CV_32S);
	Mat stats, centroids;
	int num_labels = connectedComponentsWithStats(image, labels, stats, centroids, 8, 4);
 
	//使用不同的颜色标记连通域
	vector<Vec3b> colors(num_labels);
	// background color
	colors[0] = Vec3b(0, 0, 0);
	// object color
	for (int i = 1; i < num_labels; i++) {
		colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	}
 
	// render result
	Mat dst = Mat::zeros(image.size(), image.type());
    cvtColor(dst,dst,COLOR_GRAY2BGR);
	int w = image.cols;
	int h = image.rows;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			int label = labels.at<int>(row, col);
			if (label == 0) continue;
			dst.at<Vec3b>(row, col) = colors[label];
		}
	}
 
	//利用统计信息标记连通域
	for (int i = 1; i < num_labels; i++) {
		Vec2d pt = centroids.at<Vec2d>(i, 0);
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);
		//printf("area : %d, center point(%.2f, %.2f)\n", area, pt[0], pt[1]);
        if(win_name=="v_lian"){
             if(height>10){
                circle(dst, Point(pt[0], pt[1]), 2, Scalar(0, 0, 255), -1, 8, 0);
                rectangle(dst, Rect(x, y, width, height), Scalar(255, 0, 255), 1, 8, 0);
              }
        }
         if(win_name=="u_lian"){
             if(width>10){
                circle(dst, Point(pt[0], pt[1]), 2, Scalar(0, 0, 255), -1, 8, 0);
                rectangle(dst, Rect(x, y, width, height), Scalar(255, 0, 255), 1, 8, 0);
              }
        }		
	}
    namedWindow(win_name,WINDOW_FREERATIO);
	imshow(win_name, dst);
};