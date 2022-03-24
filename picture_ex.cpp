#include "picture_ex.h"


void picture_ex(Mat*  mat,Mat * LIFT,Mat * RIGHT){
  Mat tmp_r;
  Mat tmp_l;
  Mat tmp;
  tmp=*mat;
  tmp_r=tmp.colRange(0,tmp.cols/2);
  tmp_l=tmp.colRange(tmp.cols/2+1,tmp.cols);
  *LIFT=tmp_l;
  *RIGHT=tmp_r;

};