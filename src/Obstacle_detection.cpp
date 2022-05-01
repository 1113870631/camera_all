#include "Obstacle_detection.h"
using namespace std;
using namespace cv;

#define FIne_Err 5 

     void Obstacle_detection( vector<cv::Vec4f>abstract_line_v,vector<cv::Vec4f>u_line,Mat & disp){
        vector<Vec4f>::iterator it0;        
        Mat im_color;
         applyColorMap(disp, im_color, COLORMAP_JET);
        //遍历V 视图 障碍直线  寻找U 视图对应障碍物直线
        for(it0=abstract_line_v.begin();it0!=abstract_line_v.end();it0++){
            if((*it0)[0]<40)
            continue;
            int highth,weith;//障碍物高度 和 宽度
            int x_pos1,y_pos1,x_pos2,y_pos2; //障碍物 位置信息
            double disp_x=0;    //时差值
            
            highth=(*it0)[3]-(*it0)[1];
            disp_x=(*it0)[0];


            vector<Vec4f>::iterator it1;
            vector<Vec4f> tmp;
            //遍历U 寻找对应直线
            int i=0;
            for(it1=u_line.begin();it1!=u_line.end();it1++){
                //查找对应所有直线
                if(((*it0)[0]-(*it1)[0])<FIne_Err&&((*it0)[0]-(*it1)[0])>-FIne_Err){
                    tmp.push_back((*it1));
                    i++;
                }
            }
                //判断是否找到对应直线
                if(i==0)
                goto show;//未找到
                else{//找到 遍历画线           
                        vector<Vec4f>::iterator it2;
                        for(it2=tmp.begin();it2!=tmp.end();it2++){
                                                weith=(*it2)[3]-(*it2)[1];
                                                x_pos1=(*it2)[1];
                                                x_pos2=(*it2)[3];
                                                y_pos1=(*it0)[1];
                                                y_pos2=(*it0)[3]; 
                                                //坐标转换
                                                rectangle(im_color,Point(disp.cols-x_pos1,y_pos2),Point(disp.cols-x_pos2,y_pos1),Scalar(0,255,0),3,8,0); 
                        }
                        i=0;
                } 
        }  
show:
        imshow("obs",im_color);
    };   
