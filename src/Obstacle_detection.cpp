#include "Obstacle_detection.h"
using namespace std;
using namespace cv;

#define FIne_Err 5 

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
    void Obstacle_dis_rectangle(vector<cv::Vec4f> Obstacles,Mat color_picture,Mat disp){
        imshow("row",disp);
        vector<Vec4f>::iterator it0;
        for(it0=Obstacles.begin();it0!=Obstacles.end();it0++){
            rectangle(color_picture,Point((*it0)[0],(*it0)[1]),Point((*it0)[2],(*it0)[3]),Scalar(0,255,0),3,8,0);
            //得到障碍物区域 
            Mat rol_obs=disp.rowRange((*it0)[3],(*it0)[1]);
           rol_obs=rol_obs.colRange((*it0)[2],(*it0)[0]);
           rol_obs.convertTo(rol_obs,CV_8UC1);
            //进行视差值处理       求x交叉线所有元素的均值  小于均值的元素设为0  剩下的元素求均值
           //中值滤波
            medianBlur(rol_obs,rol_obs,5);

/*             rol_obs.convertTo(rol_obs,CV_8UC1);
             Mat im_color;
            applyColorMap(rol_obs, im_color, COLORMAP_JET);
             imshow("re",im_color); */
                int height=rol_obs.rows;
                int length=rol_obs.cols;
                int tmp1=0,tmp2=0;
                for(int i=length/4;i<(int)(length*3/4);i++){
                    cout<<rol_obs.at<short>((int)(height/2),i)<<endl;
                }
               // cout<<tmp1<<endl;
                  for(int i=height/4;i<(int)(height*3/4);i++){
                    tmp2+=rol_obs.at<short>(i,(int)length/2);
                }
                tmp1=2*(tmp1+tmp2)/(height+length)/16;

       /*   double tmp2=0;
                num=0;
                threshold(rol_obs,rol_obs,tmp1,tmp1,THRESH_TOZERO_INV);
                for(int x=0;x<rol_obs.cols;x++)
                    for(int y=0;y<rol_obs.rows;y++){
                        if(rol_obs.at<short>(x,y)!=0&&rol_obs.at<short>(x,y)>0)
                        tmp2+=rol_obs.at<short>(x,y);
                        num++;
                    }
                    tmp2/=num*16; */
                    //cout<<tmp2<<endl;
                 /*    double x=tmp2;
                    double depth=(5e-10)*x*x*x*x*x*x- 3e-07*x*x*x*x*x + 7e-05*x*x*x*x - 0.0087*x*x*x + 0.63*x*x - 26.27*x + 582.63;  */
                string distance = to_string((int)tmp1);
                putText(color_picture, distance, Point((*it0)[0]+20,(*it0)[1] ),  FONT_HERSHEY_SIMPLEX, 1.0f, Scalar (255,255,0), 3, 8,false);

           
 


        }
        imshow("obs",color_picture);



    };
