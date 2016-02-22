#include "ISC.h"
using namespace std;





int main()
{
	IplImage * load;
	load = cvLoadImage("C:\\lowd.png");//Í¼Æ¬Â·¾¶
	IplImage* test = cvCreateImage(cvGetSize(load), IPL_DEPTH_8U, 1);
	IplImage* res = cvCreateImage(cvGetSize(load), IPL_DEPTH_8U, 1);
	
	cvCvtColor(load, test, CV_BGR2GRAY);// »Ò¶ÈÍ¼
	cvNamedWindow("test_demo", 1);
	cvShowImage("test_demo", test);
	cvWaitKey(0);
	
	myhist(test,res,1.5,600);
	cvShowImage("test_demo1", test);
	cvWaitKey(0);
	cvDestroyWindow("test_demo");
	cvDestroyWindow("test_demo1");
	cvReleaseImage(&test);
	return 0;
}
