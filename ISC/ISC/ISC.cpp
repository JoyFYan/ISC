#include "ISC.h"

void CreateGrayImageHist(IplImage **ppImage,unsigned int *out)//直方图创建
{
	int nHistSize = 256;
	float fRange[] = { 0, 255 };  //灰度级的范围    
	float *pfRanges[] = { fRange };
	CvHistogram *pcvHistogram = cvCreateHist(1, &nHistSize, CV_HIST_ARRAY, pfRanges);
	cvCalcHist(ppImage, pcvHistogram);
	for (int i = 0;i<nHistSize;i++)
	{
		
		out[i] = cvQueryHistValue_1D(pcvHistogram, i); //像素i的概率  float bin_val
	}
}

void findpos(unsigned int *in, unsigned int low, unsigned char *first, unsigned char *last)
{
	unsigned char temp0 = 0;
	int i=0;
	for (i = 0;i < 256;i++)
	{
		if (in[i] > low)
		{
			*first = i;
			break;
		}
	}
	for (i=i+1;i < 256;i++)
	{
		if (in[i] > low)
		{
			temp0 = i;
		}
	}
	*last = temp0;
}

void findminmax(double *in,unsigned int flag,int *result, unsigned char *pos)//1小
{
	unsigned int i = 0;
	double temp = in[0];
	unsigned int len = 256 ;
	if (flag)
	{
		for (i = 1;i < len;i++)
		{
			if (in[i] < temp)
			{
				temp = in[i];
				*pos = i;
			}
		}
	}
	else
	{
		for (i = 1;i < len;i++)
		{
			if (in[i] > temp)
			{
				temp = in[i];
				*pos = i;
			}
		}
	}
}

void myhist(IplImage* src, IplImage* dst, float khist, unsigned int lowgray)
{
	int m = src->height, n = src->width,step = src->widthStep;
	uchar* srcData = (uchar*)src->imageData;
	int  pos = 0;
	unsigned char first = 0, last = 0, locMp = 0, locNp = 0;
	float  fMaxHistValue = 0, kl = 0;
	unsigned int hist[256];
	int Mp = 0, Np = 0;
	double k[256] = { 0 }, k0[256] = {0},L=0,rd=0,tempmax = 0;
	int i = 0, j = 0;
	CreateGrayImageHist(&src, hist);
	//cvGetMinMaxHistValue(gray_hist, NULL, &fMaxHistValue, NULL, NULL);
	findpos(hist,lowgray,&first,&last);
	for (i = first + 1;i < 256;i++) //正向计算斜率
	{
		k[i] = (float(hist[i]) -float( hist[first])) / double(double(i) - double(first));
	}
	findminmax(k, 0, &Mp, &locMp);
	Mp = hist[locMp];
	for (i = 0;i < (last);i++) //正向计算斜率
	{
		k0[i] =(float (hist[last])-float( hist[i])) / double(double(i) - double(last));
	}
	findminmax(k0, 0, &Np, &locNp);
	Np = hist[locNp];
	kl = double(Np - Mp) / double(double(locNp) - double(locMp));
	/*for i = locMp:locNp
		L = Mp + kl*(i - locMp);
	rd = L - h(i);
	if rd>tempmax
		tempmax = rd;
	pos = i;
	end
		end*/
	for (i = locMp;i <= locNp;i++)
	{
		L = Mp + kl*(double(i) - double(locMp));
		rd = L - hist[i];
		if (rd > tempmax)
		{
			tempmax = rd;
			pos = i;
		}
	}
	double const1 = log((pos / khist + 1)) / pos;//计算指数系数
	double const2 = 9 / (255 - pos);
	double const3 = 1 - pos*const2;
	for (int x = 0;x < m;x++)
	{
		uchar* ptr = (uchar*)(src->imageData + x*src->widthStep);
		for (int y = 0;y < n;y++)
		{
			
			if (ptr[y] <= pos)ptr[y] = uchar(exp(ptr[y] *const1) - 1);
			else ptr[y] = pos / khist + (255 - pos / khist)*log10((const2*ptr[y] + const3));
		}
	}

	//for (int row = 0; row < src->height; row++)
	//{
	//	for (int col = 0; col < src->width; col++)
	//	{
	//		uchar sdata = srcData[row*step + col*src->nChannels];//Blue通道
	//		if (sdata <= pos)srcData[row*step + col*src->nChannels] = uchar (exp(sdata*const1) - 1);
	//		else srcData[row*step + col*src->nChannels] = pos / khist + (255 - pos / khist)*log10((const2*sdata + const3));
	//	}
	//}
	//dst = src;
	//for (int row = 0;row < m ;row++)
	//{
	//	const float* ptr=(const float*)(src->da)
	//	for (j = 0;j < n;j++)
	//	{
	//		if()
	//	}
	//}
	//for i = 1:m
	//	for j = 1 : n
	//		if J0(i, j) <= pos
	//			J0(i, j) = floor(exp((J0(i, j)*const1)) - 1);
	//		else
	//			J0(i, j) = pos / khist + (255 - pos / khist)*log10((const2*J0(i, j) + const3));
	//end
	//	end
	//	end
	
}