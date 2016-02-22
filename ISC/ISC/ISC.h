#ifndef ISC_H
#define ISC_H
#include <cv.h>
#include <highgui.h>
#include <cxcore.h> 
#include <compat.hpp>


void myhist(IplImage* src, IplImage* dst,float khist,unsigned int lowgray);
CvHistogram* CreateGrayImageHist(IplImage **ppImage);
void findpos(unsigned int *in, unsigned int low, unsigned char *first, unsigned char *last);
void findminmax(double *in, unsigned int flag,   int *result, unsigned char *pos);
#endif

