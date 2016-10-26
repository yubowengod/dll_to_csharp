// idtetity.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h" 
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h> 


using namespace cv;
using namespace std;

#define cvQueryHistValue_2D( hist, idx0, idx1 )   cvGetReal2D( (hist)->bins, (idx0), (idx1) )

IplImage *g_pGrayImage = NULL;
IplImage *g_pBinaryImage = NULL;

const char *pstrWindowsBinaryTitle = "二值图";
const char *pstrWindowsSrcTitle = "原图";
const char *pstrWindowsToolBarName = "二值图阈值";

CvSeq *contourSeq = NULL;

int printlunkuonum(IplImage *binaryim)
{
	CvMemStorage *contourStorage=cvCreateMemStorage();
	cvFindContours(binaryim, contourStorage, &contourSeq, sizeof(CvContour),CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0)); 
	IplImage *pOutlineImage = cvCreateImage(cvGetSize(binaryim), IPL_DEPTH_8U, 3);    
	int nLevels = 5;
	cvRectangle(pOutlineImage,cvPoint(0,0),cvPoint(pOutlineImage->height,pOutlineImage->width),CV_RGB(0,0,0),CV_FILLED);
	cvDrawContours(pOutlineImage, contourSeq, CV_RGB(255,0,0), CV_RGB(0,255,0), nLevels,0.5); 
	int contourcount=0;
	for(;contourSeq!=0;contourSeq=contourSeq->h_next)
	{
		contourcount++;
	}
	return contourcount;
}

//CheckMode: 0代表去除黑区域，1代表去除白区域; NeihborMode：0代表4邻域，1代表8邻域;  
void RemoveSmallRegion(Mat& Src, Mat& Dst, int AreaLimit, int CheckMode, int NeihborMode)  
{     
	int RemoveCount=0;       //记录除去的个数  
	//记录每个像素点检验状态的标签，0代表未检查，1代表正在检查,2代表检查不合格（需要反转颜色），3代表检查合格或不需检查  
	Mat Pointlabel = Mat::zeros( Src.size(), CV_8UC1 );  

	if(CheckMode==1)  
	{  
		cout<<"Mode: 去除小区域. ";  
		for(int i = 0; i < Src.rows; ++i)    
		{    
			uchar* iData = Src.ptr<uchar>(i);  
			uchar* iLabel = Pointlabel.ptr<uchar>(i);  
			for(int j = 0; j < Src.cols; ++j)    
			{    
				if (iData[j] < 10)    
				{    
					iLabel[j] = 3;   
				}    
			}    
		}    
	}  
	else  
	{  
		cout<<"Mode: 去除孔洞. ";  
		for(int i = 0; i < Src.rows; ++i)    
		{    
			uchar* iData = Src.ptr<uchar>(i);  
			uchar* iLabel = Pointlabel.ptr<uchar>(i);  
			for(int j = 0; j < Src.cols; ++j)    
			{    
				if (iData[j] > 10)    
				{    
					iLabel[j] = 3;   
				}    
			}    
		}    
	}  

	vector<Point2i> NeihborPos;  //记录邻域点位置  
	NeihborPos.push_back(Point2i(-1, 0));  
	NeihborPos.push_back(Point2i(1, 0));  
	NeihborPos.push_back(Point2i(0, -1));  
	NeihborPos.push_back(Point2i(0, 1));  
	if (NeihborMode==1)  
	{  
		cout<<"Neighbor mode: 8邻域."<<endl;  
		NeihborPos.push_back(Point2i(-1, -1));  
		NeihborPos.push_back(Point2i(-1, 1));  
		NeihborPos.push_back(Point2i(1, -1));  
		NeihborPos.push_back(Point2i(1, 1));  
	}  
	else cout<<"Neighbor mode: 4邻域."<<endl;  
	int NeihborCount=4+4*NeihborMode;  
	int CurrX=0, CurrY=0;  
	//开始检测  
	for(int i = 0; i < Src.rows; ++i)    
	{    
		uchar* iLabel = Pointlabel.ptr<uchar>(i);  
		for(int j = 0; j < Src.cols; ++j)    
		{    
			if (iLabel[j] == 0)    
			{    
				//********开始该点处的检查**********  
				vector<Point2i> GrowBuffer;                                      //堆栈，用于存储生长点  
				GrowBuffer.push_back( Point2i(j, i) );  
				Pointlabel.at<uchar>(i, j)=1;  
				int CheckResult=0;                                               //用于判断结果（是否超出大小），0为未超出，1为超出  

				for ( int z=0; z<GrowBuffer.size(); z++ )  
				{  

					for (int q=0; q<NeihborCount; q++)                                      //检查四个邻域点  
					{  
						CurrX=GrowBuffer.at(z).x+NeihborPos.at(q).x;  
						CurrY=GrowBuffer.at(z).y+NeihborPos.at(q).y;  
						if (CurrX>=0&&CurrX<Src.cols&&CurrY>=0&&CurrY<Src.rows)  //防止越界  
						{  
							if ( Pointlabel.at<uchar>(CurrY, CurrX)==0 )  
							{  
								GrowBuffer.push_back( Point2i(CurrX, CurrY) );  //邻域点加入buffer  
								Pointlabel.at<uchar>(CurrY, CurrX)=1;           //更新邻域点的检查标签，避免重复检查  
							}  
						}  
					}  

				}  
				if (GrowBuffer.size()>AreaLimit) CheckResult=2;                 //判断结果（是否超出限定的大小），1为未超出，2为超出  
				else {CheckResult=1;   RemoveCount++;}  
				for (int z=0; z<GrowBuffer.size(); z++)                         //更新Label记录  
				{  
					CurrX=GrowBuffer.at(z).x;   
					CurrY=GrowBuffer.at(z).y;  
					Pointlabel.at<uchar>(CurrY, CurrX) += CheckResult;  
				}  
				//********结束该点处的检查**********  


			}    
		}    
	}    

	CheckMode=255*(1-CheckMode);  
	//开始反转面积过小的区域  
	for(int i = 0; i < Src.rows; ++i)    
	{    
		uchar* iData = Src.ptr<uchar>(i);  
		uchar* iDstData = Dst.ptr<uchar>(i);  
		uchar* iLabel = Pointlabel.ptr<uchar>(i);  
		for(int j = 0; j < Src.cols; ++j)    
		{    
			if (iLabel[j] == 2)    
			{    
				iDstData[j] = CheckMode;   
			}    
			else if(iLabel[j] == 3)  
			{  
				iDstData[j] = iData[j];  
			}  
		}    
	}   

	cout<<RemoveCount<<" objects removed."<<endl;  
}  








extern "C" _declspec(dllexport)int _stdcall identity3(LPCTSTR imagesrc);
int _stdcall identity3(LPCTSTR imagesrc)
{//count 函数，使用参数 init 初始化静态的整形变量 S ，并使 S 自加 1 后返回该值

	IplImage * src;
	
	Mat image = imread((char*)imagesrc);//读取图片并进行灰度化处理  
	IplImage qImg;
	qImg = IplImage(image); 



	if (!(src = &IplImage(image)))
	{
		cout << "没有找到源文件" << endl;
		return -1;
	}

	IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
	IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );	
	IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* planes[] = { h_plane, s_plane };

	/** H 分量划分为个等级，S分量划分为个等级*/
	int h_bins = 16, s_bins = 8;
	int hist_size[] = {h_bins, s_bins};

	/** H 分量的变化范围*/
	float h_ranges[] = { 0, 180 }; 

	/** S 分量的变化范围*/
	float s_ranges[] = { 0, 255 };
	float* ranges[] = { h_ranges, s_ranges };

	/** 输入图像转换到HSV颜色空间*/
	cvCvtColor( src, hsv, CV_BGR2HSV );
	//cvNamedWindow( "hsv", 1 );
	//cvShowImage( "hsv", hsv );
	cvSplit( hsv, h_plane, s_plane, v_plane, 0 );

	// 转为灰度图
	g_pGrayImage =  cvCreateImage(cvGetSize(hsv), IPL_DEPTH_8U, 1);
	cvCvtColor(hsv, g_pGrayImage, CV_BGR2GRAY);

	// 创建二值图
	g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);

	// 显示原图
	//cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	//cvShowImage(pstrWindowsSrcTitle, hsv);

	// 创建二值图窗口
	//cvNamedWindow(pstrWindowsBinaryTitle, CV_WINDOW_AUTOSIZE);	

	// 转为二值图
	cvThreshold(g_pGrayImage, g_pBinaryImage, 123, 255, CV_THRESH_BINARY);

	// 显示二值图
	/*cvShowImage*/(pstrWindowsBinaryTitle, g_pBinaryImage);




	double t = (double)getTickCount();  


	cv::Mat Src(g_pBinaryImage,0); 
	/*Mat Src = imread(g_pBinaryImage, CV_LOAD_IMAGE_GRAYSCALE);  */
	Mat Dst = Mat::zeros(Src.size(), CV_8UC1);  


	//二值化处理  
	for(int i = 0; i < Src.rows; ++i)    
	{    
		uchar* iData = Src.ptr<uchar>(i);  
		for(int j = 0; j < Src.cols; ++j)    
		{    
			if(iData[j] == 0 || iData[j]==255) continue;  
			else if (iData[j] < 10)    
			{    
				iData[j] = 0;    
				//cout<<'#';  
			}    
			else if (iData[j] > 10)    
			{    
				iData[j] = 255;   
				//cout<<'!';  
			}    
		}    
	}    
	cout<<"Image Binary processed."<<endl;  

	RemoveSmallRegion(Src, Dst, 20, 1, 1);  
	RemoveSmallRegion(Dst, Dst, 20, 0, 0);  
	cout<<"Done!"<<endl;  
	//imwrite(OutPath, Dst);  

	t = ((double)getTickCount() - t)/getTickFrequency();  
	cout<<"Time cost: "<<t<<" sec."<<endl;  

	IplImage *quzao = &IplImage(Dst);



	IplImage *dsw = cvCreateImage(cvGetSize( quzao), 8, 1);    
	IplImage *dst = cvCreateImage(cvGetSize( quzao), 8, 3);   
	/*IplImage *dsw = cvCreateImage(cvGetSize( g_pBinaryImage), 8, 1);    
	IplImage *dst = cvCreateImage(cvGetSize( g_pBinaryImage), 8, 3);   */
	CvMemStorage *storage = cvCreateMemStorage(0);    
	CvSeq *first_contour = NULL;    

	//turn the src image to a binary image    
	//cvThreshold(src, dsw, 125, 255, CV_THRESH_BINARY_INV);    
	cvThreshold(quzao, dsw, 100, 255, CV_THRESH_BINARY);    

	int Num = cvFindContours(dsw, storage, &first_contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);  
	std::cout<<"The number of Contours is:"<<Num<<std::endl;  
	cvZero(dst);    
	int cnt = 0;    
	for(; first_contour != 0; first_contour = first_contour->h_next)    
	{    
		/*printf("***************************************************\n");  
		for(int i=0;i<first_contour->total;i++)  
		{  
		CvPoint* p=(CvPoint*)cvGetSeqElem(first_contour,i);  
		printf("p->x=%d,p->y=%d\n",p->x,p->y);   

		}    */



		CvScalar color = CV_RGB(rand()&255, rand()&255, rand()&255);    
		cvDrawContours(dst, first_contour, color, color, 0, 2, CV_FILLED, cvPoint(0, 0));    



		CvRect rect = cvBoundingRect(first_contour,0);  
		cvRectangle(dst, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height),CV_RGB(255, 0, 0), 1, 8, 0);  
		cnt++;    

		/*first_contour = cvApproxPoly( first_contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 3, 1 );  */
	}    

	if(cnt>6)
	{
		return 1;    
	}
	else if(cnt<=6)
	{
		return 0;    
	}

}

// 导出函数，使用“ _stdcall ” 标准调用
extern "C" _declspec(dllexport)int _stdcall identity(int init);
int _stdcall identity(int init)
{//count 函数，使用参数 init 初始化静态的整形变量 S ，并使 S 自加 1 后返回该值
	static int S=init;
	S++;
	return S;
}

extern "C" _declspec(dllexport)int _stdcall identity1(int init);
int _stdcall identity1(int init)
{//count 函数，使用参数 init 初始化静态的整形变量 S ，并使 S 自加 1 后返回该值

	return init;
}

extern "C" _declspec(dllexport)int _stdcall identity4(int init);
int _stdcall identity4(int init)
{//count 函数，使用参数 init 初始化静态的整形变量 S ，并使 S 自加 1 后返回该值

	return init;
}

extern "C" _declspec(dllexport)int _stdcall identity2(LPCTSTR init);
int _stdcall identity2(LPCTSTR init)
{//count 函数，使用参数 init 初始化静态的整形变量 S ，并使 S 自加 1 后返回该值

	return 1;
}



