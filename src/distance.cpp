#include <opencv2/opencv.hpp>
#include <iostream>
#include "distance.h"
using namespace cv;
using namespace std;
/**
 * @brief 
 * 1/4"    cmos   对角线 1/4 英寸     3x1280=3840   720x3=2160     6x640=3840   一个像素6um
 * b 镜头中心距离
 * f  焦距  3.6  mm   
 * z 深度
 * z=b*f/(xl-xr)
 * 
 *     dis   要测量距离点的时差值
 * 
 * 
 * 40cm 25.7          14.3
 * 50cm 32.3           17.7
 * 60cm 37.8            22.2
 * 70cm 43.7           26.3
 * 80cm 50.5            29.5
 * 90cm 55.3   
 * 100cm 
 *           
 * @return double 
 */

extern int setNumDisparities;
extern Mat row;
extern Mat sgm_guiyi;
extern Mat Q_my;
static void onMouse( int event, int x_num, int y_num, int flag,void * disp)
{
        switch( event )
    {
        case EVENT_LBUTTONDOWN:
        Mat out;
        reprojectImageTo3D (sgm_guiyi,out,Q_my,false,-1);
        cout<<"x:"<<x_num<<"  y" <<y_num<<endl;
        for(int i=0;i<5;i++){
             int x= row.at<short>(Point(x_num+i,y_num))/16;//x 代表视差值
            // cout<<x<<"  ";
            // out.at<Vec3f>(Point(x_num+i,y_num))[0];
            cout<<"("<<(int)out.at<Vec3f>(Point(x_num+i,y_num))[0]-30<<","<<(int)out.at<Vec3f>(Point(x_num+i,y_num))[1]<<")"<<" ";

        }          
            cout <<endl;
/*             double depth=(5e-10)*x*x*x*x*x*x- 3e-07*x*x*x*x*x + 7e-05*x*x*x*x - 0.0087*x*x*x + 0.63*x*x - 26.27*x + 582.63;
            cout<<"distance:"<<depth<<"\n"; */
            break;
    }

}




/**
 * @brief 
 * 
 * 
 * /double depth=(5e-10)*x*x*x*x*x*x- 3e-07*x*x*x*x*x + 7e-05*x*x*x*x - 0.0087*x*x*x + 0.63*x*x - 26.27*x + 582.63;
 * @param disp 
 */
      void   mouce_distance(Mat  disp,Mat color){

          namedWindow("dis_depth",WINDOW_FREERATIO);
          setMouseCallback 	( "dis_depth",onMouse); //设置回调计算距离	
          imshow("dis_depth",color);//显示带有距离数据的图
 };
