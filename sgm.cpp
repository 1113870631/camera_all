#include "sgm.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
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



Mat Pic_per_L[thead_num];
Mat Pic_per_R[thead_num];
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
                        Mat tmp;
                        Sgbm_Arr[num]->compute(Pic_per_L[num], Pic_per_R[num], tmp);
                        PIc_end[num]=tmp.clone();
                          //取消信号
                          sem[num]=0;
    }

}

//生成线程和SGBM
void thread_prepare(int thread_num){
    for(int tmp=0;tmp<thead_num;tmp++){
          Sgbm_Arr[tmp]= cv::StereoSGBM::create(0,9, 3);
           Sgbm_Arr[tmp]->setBlockSize(3);
            Sgbm_Arr[tmp]->setNumDisparities(130);
            Sgbm_Arr[tmp]->setP1(1 );
            Sgbm_Arr[tmp]->setP2(32);  
            Sgbm_Arr[tmp]->setUniquenessRatio(3);
            Sgbm_Arr[tmp]->setSpeckleWindowSize(3);
            Sgbm_Arr[tmp]->setSpeckleRange(3);
            Sgbm_Arr[tmp]->setDisp12MaxDiff(3);
            Sgbm_Arr[tmp]->setMinDisparity(0);     
          mythreads.push_back(thread(my_thread2, tmp));
    }
};

void sgm(Mat lift,Mat rigit,Mat *out,Mat *row_pic,int setNumDisparities,cv::Ptr<cv::StereoSGBM> sgbm)  {

           Mat grayLeft,grayRight;
            //分成16分 分别进行立体匹配

            Mat im3[thead_num];
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
          //显示
         for(int tmp=0;tmp<thead_num;tmp++)
         {
              PIc_end[tmp].convertTo(PIc_end[tmp], CV_16S); 
             PIc_end[tmp].convertTo(PIc_end[tmp],CV_8UC1,255 / (setNumDisparities*16.0));
             imshow(to_string(tmp),PIc_end[tmp]);
         }



                  
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


