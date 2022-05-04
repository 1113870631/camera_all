#include "Obstacle_detection.h"
using namespace std;
using namespace cv;
extern Mat row;
#define FIne_Err 10 

     void Obstacle_detection( vector<cv::Vec4f>abstract_line_v,vector<cv::Vec4f>u_line,Mat & disp,vector<cv::Vec4f>&Obstacles){
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
                                                //rectangle(im_color,Point(disp.cols-x_pos1,y_pos2),Point(disp.cols-x_pos2,y_pos1),Scalar(0,255,0),3,8,0); 
                                                Obstacles.push_back(Vec4f(disp.cols-x_pos1,y_pos2,disp.cols-x_pos2,y_pos1));
                        }
                        i=0;
                } 
        }  
     show:
         // imshow("obs",im_color);
        ; //防止goto show 报错
    };   

/**
 * @brief 
 *标出障碍物并计算距离
 * 
 * @param Obstacles   障碍物
 * @param color_picture   显示的图片
 */

 extern Mat row;
    void Obstacle_dis_rectangle(vector<cv::Vec4f> Obstacles,Mat color_picture){
        
        vector<Vec4f>::iterator it0;
        for(it0=Obstacles.begin();it0!=Obstacles.end();it0++){
            //画矩形
            rectangle(color_picture,Point((*it0)[0],(*it0)[1]),Point((*it0)[2],(*it0)[3]),Scalar(0,255,0),3,8,0);
            //算视差
            int tmp_dis=0;
            int num=0;
            for(int i=(*it0)[2]+10;i<(*it0)[0]-10;i++)
                for(int j=(*it0)[3];j<(*it0)[1];j++){
                    if( (row.at<short>(Point(i,j))/16)>0){
                        tmp_dis+= (row.at<short>(Point(i,j))/16);
                        num++;
                   }        
                 }
                 if(num!=0){
                    cout<<tmp_dis/num<<endl;
                 }
                
        }
        imshow("obs",color_picture);
        //imshow("row",row);
         //int x= row.at<short>(row.cols/2,row.rows/2)/16;//x 代表视差值
        // cout<<x<<endl;



    };
