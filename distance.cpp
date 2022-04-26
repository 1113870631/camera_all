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


extern Mat row;
static void onMouse( int event, int x, int y, int,void * disp)
{
    Mat* tmp=(Mat*)disp;
        switch( event )
    {
        case EVENT_LBUTTONDOWN:
            //cout<<"left\n";
           // cout<<"x:"<<x<<"y:"<<y<<"\n";

            cout<<"depth:"<<(*tmp).at<float>(x,y)<<"\n";
            cout<<row.type()<<endl;
            cout<<"dis:"<<row.at<short>(x,y)/16<<"\n";
            
    
            break;
    }

}


      void   mouce_distance(Mat  &disp){
          Mat tmp;//显示的8U_C1 图像
           disp.convertTo( tmp,CV_8UC1);
           Mat im_color;
          applyColorMap(tmp, im_color, COLORMAP_JET);
          namedWindow("dis_depth",WINDOW_FREERATIO);
           setMouseCallback 	( "dis_depth",onMouse,&disp); //设置回调计算距离	
           imshow("dis_depth",im_color);//显示带有距离数据的图像
 };
