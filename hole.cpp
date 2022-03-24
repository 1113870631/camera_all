#include "hole.h"
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
#define  MAX_POINT  10

void full_hole(cv::Mat * disp)
{ 
     int xo,yo,num=0;
     int weight=(*disp).rows;
     int hight=(*disp).cols;

    //遍历图像寻找感性区域

     //cout<<(*disp).size<<"\n";
    for(int i=0;i<(*disp).rows;i++)
    {
        for(int j=0;j<(*disp).cols;j++)
        {//遍历图像  i   x    row      j   y    col 
           if( (*disp).at<uchar>(i,j) ==0)
           { 
               int tmpi=i,tmpj=j;
               double total_x1=0,total_x2=0, total_y1=0,total_y2=0;
                 while(1)
                 {         
                          if(j==hight){
                              total_y1=0;
                              break;
                          }
                          if( (*disp).at<uchar>(i,j++) !=0)
                          {
                              num++;                           
                              total_y1+=(*disp).at<uchar>(i,j) ;
                              //达到最大所需点数   num =0  跳出循环
                              if(num==MAX_POINT||j==hight)
                             {
                                break;
                              }

                          }
                 }
                 i=tmpi;
                 j=tmpj;      
                 if(num!=0)        
                 total_y1/=num;
                 else
                 total_y1=0;

                num=0;

                  while(1)
                 {         
                          if(j==0){
                              total_y2=0;
                              break;
                          }
                          if( (*disp).at<uchar>(i,j--) !=0)
                          {
                              num++;                           
                              total_y2+=(*disp).at<uchar>(i,j) ;
                              //达到最大所需点数   num =0  跳出循环
                              if(num==MAX_POINT||j==0)
                             {
                                break;
                              }

                          }
                 }    
                 i=tmpi;
                 j=tmpj;     
                 if(num!=0)        
                 total_y2/=num;
                 else
                 total_y2=0;
                 
                num=0;
              //   x1 x2  


              while(1)
                 {         
                          if(i==weight){
                              total_x1=0;
                              break;
                          }
                          if( (*disp).at<uchar>(i++,j) !=0)
                          {
                              num++;                           
                              total_x1+=(*disp).at<uchar>(i,j) ;
                              //达到最大所需点数   num =0  跳出循环
                              if(num==MAX_POINT||i==weight)
                             {
                                break;
                              }

                          }
                 }
                 i=tmpi;
                 j=tmpj;      
                 if(num!=0)        
                 total_x1/=num;
                 else
                 total_x1=0;

                num=0;

                  while(1)
                 {         
                          if(i==0){
                              total_x2=0;
                              break;
                          }
                          if( (*disp).at<uchar>(i--,j) !=0)
                          {
                              num++;                           
                              total_x2+=(*disp).at<uchar>(i--,j) ;
                              //达到最大所需点数   num =0  跳出循环
                              if(num==MAX_POINT||i==0)
                             {
                                break;
                              }

                          }
                 }    
                 i=tmpi;
                 j=tmpj;     
                 if(num!=0)        
                 total_x2/=num;
                 else
                 total_x2=0;
                 
                num=0;



                (*disp).at<uchar>(i,j)=(total_y2+total_y1+total_x2+total_x1)/4;

            
           }
                       
        }
    }
}









