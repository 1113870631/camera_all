#include <rectangle_uv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <opencv2/core/matx.hpp>

RNG rng(123);

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


 
 
void connected_components_stat(Mat& image,string win_name,Mat &labels,Mat &stats  ,int &num_labels,vector<Vec4f>&abstract_line,vector<Vec4f>&ground_line,vector<Vec4f>&u_line) {
 
	//计算连通域
	//Mat labels = Mat::zeros(image.size(), CV_32S);
	Mat  centroids;
	 num_labels = connectedComponentsWithStats(image, labels, stats, centroids, 8, 4);
 
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
	Mat test = Mat::zeros(image.size(), image.type());
    cvtColor(test,test,COLOR_GRAY2BGR);

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
		if(width<30&&height<30){//过滤极小点
			 rectangle(dst, Rect(x, y, width, height), Scalar(0, 0, 0), -1, 8, 0);
			continue;
		}
        if(win_name=="v_lian"){
             if(height>10){
                circle(dst, Point(pt[0], pt[1]), 2, Scalar(0, 0, 255), -1, 8, 0);
                rectangle(dst, Rect(x, y, width, height), Scalar(255, 0, 255), 1, 8, 0);
				if((double)height/width<5&&(double)height/width>0.5){//ground
					//rectangle(test, Rect(x, y, width, height), Scalar(255, 0, 255), 1, 8, 0);
					line(test,Point(x,y),Point(x+width,y+height),Scalar(255,0,255),2);
					ground_line.push_back(Vec4f(x,y,x+width,y+height));
				}
				if((double)height/width>5){//abstract
					//rectangle(test, Rect(x, y, width, height), Scalar(255, 255, 255), 1, 8, 0);
					line(test,Point(x+width/2,y),Point(x+width/2,y+height),Scalar(255,255,255),2);
					abstract_line.push_back(Vec4f(x+width/2,y,x+width/2,y+height));
				}
				imshow("test_v",test);
              }
	  
        }
         if(win_name=="u_lian"){
             if(height>10){
                circle(dst, Point(pt[0], pt[1]), 2, Scalar(0, 0, 255), -1, 8, 0);
                rectangle(dst, Rect(x, y, width, height), Scalar(255, 255, 255), 1, 8, 0);
				u_line.push_back(Vec4f(x+width/2,y,x+width/2,y+height));
              }
        }		
	}
    //namedWindow(win_name,WINDOW_FREERATIO);
	imshow(win_name, dst);
};
