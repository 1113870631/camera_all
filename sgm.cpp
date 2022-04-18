#include "sgm.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;
  
/**
 * @brief
 * @Mat lift
 * @Mat rigit
 * @Mat *out
 * @int setNumDisparities 
 * @int setblock 
     @int  setUniquenessRatio
     @nt setSpeckleWindowSize, 
     @int setSpeckleRange 
    @nt setDisp12MaxDiff 
    @cv::Ptr<cv::StereoSGBM> sgbm
 */
   extern  int setblock;
    extern int setNumDisparities;
    extern int setUniquenessRatio;
    extern int setSpeckleWindowSize;
    extern int setSpeckleRange;
    extern int setDisp12MaxDiff;
    extern int setMinDisparity;
    extern int p1;
    extern int p2;


Mat Pic_per_L[thead_num];
Mat Pic_per_R[thead_num];

Mat Pic_per_L2[thead_num2];
Mat Pic_per_R2[thead_num2];

Mat PIc_end2[thead_num2];
Mat PIc_end[thead_num];
int sem[thead_num];
cv::Ptr<cv::StereoSGBM> Sgbm_Arr[thead_num];
vector<thread> mythreads;


//线程函数
void my_thread2(int num){

    while(1){
                  //等待信号
                    while(!sem[num]){   
                        //cout<<"waiting"<<num<<endl; 
                        }
                        //得到信号
                        
                         Sgbm_Arr[num]->setBlockSize(setblock);
                         Sgbm_Arr[num]->setNumDisparities(setNumDisparities);
                        Sgbm_Arr[num]->setP1(p1 * 1*setblock*setblock );
                        Sgbm_Arr[num]->setP2(p2 * 1*setblock*setblock);  
                        Sgbm_Arr[num]->setUniquenessRatio(setUniquenessRatio);
                        Sgbm_Arr[num]->setSpeckleWindowSize(setSpeckleWindowSize);
                        Sgbm_Arr[num]->setSpeckleRange(setSpeckleRange);
                        Sgbm_Arr[num]->setDisp12MaxDiff(setDisp12MaxDiff);
                        Sgbm_Arr[num]->setMinDisparity(0); 
                        Mat tmp;
                        Sgbm_Arr[num]->compute(Pic_per_L[num], Pic_per_R[num], tmp);                       
                        PIc_end[num]=tmp.clone();
                        
                        //vconcat(PIc_end2,thead_num2,PIc_end[num]);
                          //取消信号
                          sem[num]=0;


        }
}

void Set_Sgbm(void){
      for(int tmp=0;tmp<thead_num;tmp++){
             Sgbm_Arr[tmp]->setBlockSize(setblock);
             Sgbm_Arr[tmp]->setNumDisparities(setNumDisparities);
             Sgbm_Arr[tmp]->setP1(p1 * 1*setblock*setblock );
             Sgbm_Arr[tmp]->setP2(p2 * 1*setblock*setblock);  
             Sgbm_Arr[tmp]->setUniquenessRatio(setUniquenessRatio);
             Sgbm_Arr[tmp]->setSpeckleWindowSize(setSpeckleWindowSize);
             Sgbm_Arr[tmp]->setSpeckleRange(setSpeckleRange);
             Sgbm_Arr[tmp]->setDisp12MaxDiff(setDisp12MaxDiff);
             Sgbm_Arr[tmp]->setMinDisparity(0);     
            }
}
//生成线程和SGBM
void thread_prepare(int thread_num){                      
    for(int tmp=0;tmp<thead_num;tmp++){
             Sgbm_Arr[tmp]= cv::StereoSGBM::create(0,64, 3);
             /*  Sgbm_Arr[tmp]->setBlockSize(0);
             Sgbm_Arr[tmp]->setNumDisparities(1);
             Sgbm_Arr[tmp]->setP1(60 * 1*setblock*setblock );
             Sgbm_Arr[tmp]->setP2(300 * 1*setblock*setblock);  
             Sgbm_Arr[tmp]->setUniquenessRatio(0);
             Sgbm_Arr[tmp]->setSpeckleWindowSize(0);
             Sgbm_Arr[tmp]->setSpeckleRange(0);
             Sgbm_Arr[tmp]->setDisp12MaxDiff(500);
             Sgbm_Arr[tmp]->setMinDisparity(0);  */    

            mythreads.push_back(thread(my_thread2, tmp));
    }
};

void sgm(Mat lift,Mat rigit,Mat *out,int setNumDisparities)  {
     
           Mat grayLeft,grayRight;
            //分成分 分别进行立体匹配

             //转化为灰度图
            cvtColor(lift,grayLeft,COLOR_BGR2GRAY);
            cvtColor(rigit,grayRight,COLOR_BGR2GRAY);
            //分份
            int del=(lift.rows)%thead_num;
            int per=(lift.rows-del)/thead_num;
            Mat pic_del_l=grayLeft.rowRange(del,lift.rows);
            Mat pic_del_r=grayRight.rowRange(del,lift.rows);
            for(int tmp=0;tmp<thead_num;tmp++){
                Pic_per_R[tmp]=pic_del_r.rowRange(tmp*per,per*(1+tmp));
                Pic_per_L[tmp]=pic_del_l.rowRange(tmp*per,per*(1+tmp));
            } 
            //发送信号
            for(int tmp=0;tmp<thead_num;tmp++){
                sem[tmp]=1;
            }
          //等待完成信号
          int tmp_sem=0;
          for(int tmp=0;tmp<thead_num;tmp++){
              tmp_sem+=sem[tmp];
          }
          while(tmp_sem){
                   tmp_sem=0;
                    for(int tmp=0;tmp<thead_num;tmp++){
              tmp_sem+=sem[tmp];
             }
          }
          //归一化
         for(int tmp=0;tmp<thead_num;tmp++)
         {
              PIc_end[tmp].convertTo(PIc_end[tmp],CV_8UC1,255 / (setNumDisparities*16.0));
         }     
         //合并
        vconcat(PIc_end,thead_num,*out);
};




 /*  for(int i=0;i<thead_num;i++) //立体匹配
                    {
                                sgbm->compute(per_left[i], per_right[i], im3[i]);
                    }
              Mat out1;
            //拼合图像
            vconcat(im3,thead_num,out1);
            //输出原视差图
            *row_pic=out1;
            //输出归一化视差图
             out1.convertTo(out1, CV_16S); 
             out1.convertTo(out1,CV_8UC1,255 / (setNumDisparities*16.0));//归一化  十分重要
            *out=out1; */


