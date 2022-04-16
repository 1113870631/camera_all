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


 
 
void connected_components_stat(Mat& image,string win_name,Mat &labels,Mat &stats  ,int &num_labels) {
 
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
/**
 * @brief 
 * 
 * 连通区域矩形处理 得到地面矩形  障碍物矩形
 * 
 * @param status
 * @param lables_num
 */
void rectangle_deal(Mat & status,int &lables_num){

    Vec4i Rec_Ground [10];
	Vec4i Rec_Obs[10];
	int obs=0,ground=0;

	for (int i = 1; i < lables_num; i++) {
		int x = status.at<int>(i, CC_STAT_LEFT);
		int y = status.at<int>(i, CC_STAT_TOP);
		int width = status.at<int>(i, CC_STAT_WIDTH);
		int height = status.at<int>(i, CC_STAT_HEIGHT);
		int area = status.at<int>(i, CC_STAT_AREA);

		if(area<20)//过滤小块
		continue;
		else{

				if	((float)height/width>=5){//障碍物矩形
				    if(obs>=10){}
					else{
					Rec_Obs[obs]=Vec4i(x,y,width,height);
					obs++;
					} 
	
		        }
				else if((float)height/width>=0.3&&(float)height/width<5){//地面矩形
					if(ground>=10){}
					else{
					Rec_Ground [ground]=Vec4i(x,y,width,height);
					ground++;
					}
				} 
		}

		
	}
	//画出矩形
	Mat test = Mat::zeros(Size(400,800), CV_8UC1);
	for(int tmp=0;tmp<ground;tmp++)
	{
		 rectangle(test, Rect(Rec_Ground[tmp][0], Rec_Ground[tmp][1], Rec_Ground[tmp][2], Rec_Ground[tmp][3]), Scalar(255, 0, 255), 1, 8, 0);

	} 
    	for(int tmp=0;tmp<obs;tmp++)
	{
		rectangle(test, Rect(Rec_Obs[tmp][0], Rec_Obs[tmp][1], Rec_Obs[tmp][2], Rec_Obs[tmp][3]), Scalar(255, 0, 255), 1, 8, 0);
	} 
	imshow("rec_test",test); 


};