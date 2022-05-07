#include <rectangle_uv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <opencv2/core/matx.hpp>
#include<algorithm>  

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
 
  //开运算  闭运算
	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	//morphologyEx(image, image, MORPH_OPEN, k);
	morphologyEx(image, image, MORPH_CLOSE, k); 
	//计算连通域
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
				if((double)height/width<4&&(double)height/width>0.5){//ground
					//rectangle(test, Rect(x, y, width, height), Scalar(255, 0, 255), 1, 8, 0);
					line(test,Point(x,y),Point(x+width,y+height),Scalar(255,0,255),2);
					ground_line.push_back(Vec4f(x,y,x+width,y+height));
				}
				if((double)height/width>4){//abstract
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



void Ground_line_Deal(vector<Vec4f>&ground_line_v,Mat VdispMap){
	//位置处理 下半部分的地面直线去除出去
	if(ground_line_v.empty()){//检测是否为空
		return;
	}
 	vector<Vec4f>::iterator it0;
	int half_y=VdispMap.rows/2;
	again:for(it0=ground_line_v.begin();it0!=ground_line_v.end();it0++){
		if((*it0)[1]<half_y&&(*it0)[3]<half_y){
			ground_line_v.erase(it0);
		      goto again;
		}
	};
	//斜率过滤   
	double tmp_k;
	vector<double>k_list;
	for(it0=ground_line_v.begin();it0!=ground_line_v.end();it0++){
		tmp_k=((*it0)[3]-(*it0)[1])/((*it0)[2]-(*it0)[0]);
		k_list.push_back(tmp_k);
	}
	//检测是否为空
	if(k_list.empty()){
		return;
	}
    //正向排序：按照从小到大的顺序排序
    sort(k_list.begin(), k_list.end());
	//取出中位斜率 tmp_K
	tmp_k=k_list.at((int)k_list.size()/2);
	//去除不符合斜率的直线
	again2:for(it0=ground_line_v.begin();it0!=ground_line_v.end();it0++){
		double k_present=((*it0)[3]-(*it0)[1])/((*it0)[2]-(*it0)[0]);
		if(k_present-tmp_k<-1&&k_present-tmp_k>1){
			ground_line_v.erase(it0);
		      goto again2;
		}
	} 
	//距离过滤


	

};


bool  comp( Vec4f &a,  Vec4f &b) {
	return a[0] < b[0];
}
void Obstacle_line_Deal(vector<Vec4f>&abstract_line_v,Mat VdispMap,vector<Vec4f>&abstract_line_v_end){
	if(abstract_line_v.size()<=1)
	return;
	vector<Vec4f>::iterator it0;
	//V 图直线合并
		//排序
	sort(abstract_line_v.begin(),abstract_line_v.end(),comp);
	  //寻找大间隔
	  vector<Vec4f>list;
	  int num=0;
	  // ag 4           size=4     size-1=3 
	for(int i=0;i<abstract_line_v.size()-1;i++){
		num++;
		if(   abstract_line_v.at(i+1)[0]-abstract_line_v.at(i)[0]>10   ){
					//找到大间隔	
					/*
					有以下情况
					1   |||||||||||||    ||||||||||||||||
					2  ||||||||||||||||||||||||         |
					*/
					if(i==abstract_line_v.size()-2){//倒数第一个和第二个有大间隔   
						//pushback    
						list.push_back(Vec4f(i,num,abstract_line_v.at(i)[0],0));
						list.push_back(Vec4f(i+1,1,abstract_line_v.at(i+1)[0],0));
					}
					else{//中间有大间隔
						list.push_back(Vec4f(i,num,abstract_line_v.at(i)[0],0));
						num=0;
					}
					//line(VdispMap,Point(abstract_line_v.at(i+1)[0],VdispMap.rows),Point(abstract_line_v.at(i+1)[0],0),Scalar(255,255,255),4,8,0);
					//line(VdispMap,Point(abstract_line_v.at(i)[0],VdispMap.rows),Point(abstract_line_v.at(i)[0],0),Scalar(255,255,255),4,8,0);
		}  
		else if (i==abstract_line_v.size()-2){//没有遇到
		 	if(i==abstract_line_v.size()-2){
				 	list.push_back(Vec4f(i+1,num+1,abstract_line_v.at(i+1)[0],0));
			 }
		}
		
    }
   //聚合
	for(it0=list.begin();it0!=list.end();it0++){
		//debug划线
		//line(VdispMap,Point((*it0)[2],VdispMap.rows),Point((*it0)[2],0),Scalar(255,255,255),4,8,0);
		vector<int>y;
		int num=(*it0)[1];
		int pos=(*it0)[0];
		int x=(*it0)[2];
		for(int j=pos-num+1;j<=pos;j++){
			//cout<<j<<endl;
			y.push_back(abstract_line_v.at(j)[1]);
			y.push_back(abstract_line_v.at(j)[3]);
		}
		sort(y.begin(),y.end());
		//circle(VdispMap,Point(abstract_line_v.at(pos)[0],y.at(y.size()-1)),5,Scalar(255,255,255),1,8,0);
		//circle(VdispMap,Point(abstract_line_v.at(pos)[0],y.at(0)),5,Scalar(255,255,255),1,8,0);
	   //line(VdispMap,Point(abstract_line_v.at(pos)[0],y.at(0)),Point(abstract_line_v.at(pos)[0],y.at(y.size()-1)),Scalar(255,255,255),4,8,0);
	 // Vec4f(abstract_line_v.at(pos)[0],y.at(0),abstract_line_v.at(pos)[0],y.at(y.size()-1));
	  abstract_line_v_end.push_back(Vec4f(abstract_line_v.at(pos)[0],y.at(0),abstract_line_v.at(pos)[0],y.at(y.size()-1)));
	}	 
   //imshow("vv",VdispMap);	
}
	


void Ground_Obstacle__Line_deal(vector<Vec4f>&abstract_line_v,vector<Vec4f>&ground_line_v, Mat &VdispMap){

	vector<Vec4f>::iterator it0;
	double k;
	double x1,y1,x2,y2;

	for(it0=ground_line_v.begin();it0!=ground_line_v.end();it0++){
		x1+=(*it0)[0];
		x2+=(*it0)[2];
		y1+=(*it0)[1];
		y2+=(*it0)[3];
	}
	    x1/=ground_line_v.size();
		x2/=ground_line_v.size();
		y1/=ground_line_v.size();
		y2/=ground_line_v.size();
		k=(y2-y1)/(x2-x1);
		//y=kx+b     k    (x1,y1)   
		//b=y-kx
		double b=y1-k*x1;
		//划线 将地面直线与障碍物直线分割开来
		line(VdispMap,Point(0,b-20),Point(VdispMap.cols,k*VdispMap.cols+b-20),Scalar(0,0,0),2,8,0);
};