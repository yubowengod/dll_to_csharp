// idtetity.cpp : ���� DLL Ӧ�ó���ĵ���������
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

const char *pstrWindowsBinaryTitle = "��ֵͼ";
const char *pstrWindowsSrcTitle = "ԭͼ";
const char *pstrWindowsToolBarName = "��ֵͼ��ֵ";

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

//CheckMode: 0����ȥ��������1����ȥ��������; NeihborMode��0����4����1����8����;  
void RemoveSmallRegion(Mat& Src, Mat& Dst, int AreaLimit, int CheckMode, int NeihborMode)  
{     
	int RemoveCount=0;       //��¼��ȥ�ĸ���  
	//��¼ÿ�����ص����״̬�ı�ǩ��0����δ��飬1�������ڼ��,2�����鲻�ϸ���Ҫ��ת��ɫ����3������ϸ������  
	Mat Pointlabel = Mat::zeros( Src.size(), CV_8UC1 );  

	if(CheckMode==1)  
	{  
		cout<<"Mode: ȥ��С����. ";  
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
		cout<<"Mode: ȥ���׶�. ";  
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

	vector<Point2i> NeihborPos;  //��¼�����λ��  
	NeihborPos.push_back(Point2i(-1, 0));  
	NeihborPos.push_back(Point2i(1, 0));  
	NeihborPos.push_back(Point2i(0, -1));  
	NeihborPos.push_back(Point2i(0, 1));  
	if (NeihborMode==1)  
	{  
		cout<<"Neighbor mode: 8����."<<endl;  
		NeihborPos.push_back(Point2i(-1, -1));  
		NeihborPos.push_back(Point2i(-1, 1));  
		NeihborPos.push_back(Point2i(1, -1));  
		NeihborPos.push_back(Point2i(1, 1));  
	}  
	else cout<<"Neighbor mode: 4����."<<endl;  
	int NeihborCount=4+4*NeihborMode;  
	int CurrX=0, CurrY=0;  
	//��ʼ���  
	for(int i = 0; i < Src.rows; ++i)    
	{    
		uchar* iLabel = Pointlabel.ptr<uchar>(i);  
		for(int j = 0; j < Src.cols; ++j)    
		{    
			if (iLabel[j] == 0)    
			{    
				//********��ʼ�õ㴦�ļ��**********  
				vector<Point2i> GrowBuffer;                                      //��ջ�����ڴ洢������  
				GrowBuffer.push_back( Point2i(j, i) );  
				Pointlabel.at<uchar>(i, j)=1;  
				int CheckResult=0;                                               //�����жϽ�����Ƿ񳬳���С����0Ϊδ������1Ϊ����  

				for ( int z=0; z<GrowBuffer.size(); z++ )  
				{  

					for (int q=0; q<NeihborCount; q++)                                      //����ĸ������  
					{  
						CurrX=GrowBuffer.at(z).x+NeihborPos.at(q).x;  
						CurrY=GrowBuffer.at(z).y+NeihborPos.at(q).y;  
						if (CurrX>=0&&CurrX<Src.cols&&CurrY>=0&&CurrY<Src.rows)  //��ֹԽ��  
						{  
							if ( Pointlabel.at<uchar>(CurrY, CurrX)==0 )  
							{  
								GrowBuffer.push_back( Point2i(CurrX, CurrY) );  //��������buffer  
								Pointlabel.at<uchar>(CurrY, CurrX)=1;           //���������ļ���ǩ�������ظ����  
							}  
						}  
					}  

				}  
				if (GrowBuffer.size()>AreaLimit) CheckResult=2;                 //�жϽ�����Ƿ񳬳��޶��Ĵ�С����1Ϊδ������2Ϊ����  
				else {CheckResult=1;   RemoveCount++;}  
				for (int z=0; z<GrowBuffer.size(); z++)                         //����Label��¼  
				{  
					CurrX=GrowBuffer.at(z).x;   
					CurrY=GrowBuffer.at(z).y;  
					Pointlabel.at<uchar>(CurrY, CurrX) += CheckResult;  
				}  
				//********�����õ㴦�ļ��**********  


			}    
		}    
	}    

	CheckMode=255*(1-CheckMode);  
	//��ʼ��ת�����С������  
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
{//count ������ʹ�ò��� init ��ʼ����̬�����α��� S ����ʹ S �Լ� 1 �󷵻ظ�ֵ

	IplImage * src;
	
	Mat image = imread((char*)imagesrc);//��ȡͼƬ�����лҶȻ�����  
	IplImage qImg;
	qImg = IplImage(image); 



	if (!(src = &IplImage(image)))
	{
		cout << "û���ҵ�Դ�ļ�" << endl;
		return -1;
	}

	IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
	IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );	
	IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* planes[] = { h_plane, s_plane };

	/** H ��������Ϊ���ȼ���S��������Ϊ���ȼ�*/
	int h_bins = 16, s_bins = 8;
	int hist_size[] = {h_bins, s_bins};

	/** H �����ı仯��Χ*/
	float h_ranges[] = { 0, 180 }; 

	/** S �����ı仯��Χ*/
	float s_ranges[] = { 0, 255 };
	float* ranges[] = { h_ranges, s_ranges };

	/** ����ͼ��ת����HSV��ɫ�ռ�*/
	cvCvtColor( src, hsv, CV_BGR2HSV );
	//cvNamedWindow( "hsv", 1 );
	//cvShowImage( "hsv", hsv );
	cvSplit( hsv, h_plane, s_plane, v_plane, 0 );

	// תΪ�Ҷ�ͼ
	g_pGrayImage =  cvCreateImage(cvGetSize(hsv), IPL_DEPTH_8U, 1);
	cvCvtColor(hsv, g_pGrayImage, CV_BGR2GRAY);

	// ������ֵͼ
	g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);

	// ��ʾԭͼ
	//cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	//cvShowImage(pstrWindowsSrcTitle, hsv);

	// ������ֵͼ����
	//cvNamedWindow(pstrWindowsBinaryTitle, CV_WINDOW_AUTOSIZE);	

	// תΪ��ֵͼ
	cvThreshold(g_pGrayImage, g_pBinaryImage, 123, 255, CV_THRESH_BINARY);

	// ��ʾ��ֵͼ
	/*cvShowImage*/(pstrWindowsBinaryTitle, g_pBinaryImage);




	double t = (double)getTickCount();  


	cv::Mat Src(g_pBinaryImage,0); 
	/*Mat Src = imread(g_pBinaryImage, CV_LOAD_IMAGE_GRAYSCALE);  */
	Mat Dst = Mat::zeros(Src.size(), CV_8UC1);  


	//��ֵ������  
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

// ����������ʹ�á� _stdcall �� ��׼����
extern "C" _declspec(dllexport)int _stdcall identity(int init);
int _stdcall identity(int init)
{//count ������ʹ�ò��� init ��ʼ����̬�����α��� S ����ʹ S �Լ� 1 �󷵻ظ�ֵ
	static int S=init;
	S++;
	return S;
}

extern "C" _declspec(dllexport)int _stdcall identity1(int init);
int _stdcall identity1(int init)
{//count ������ʹ�ò��� init ��ʼ����̬�����α��� S ����ʹ S �Լ� 1 �󷵻ظ�ֵ

	return init;
}

extern "C" _declspec(dllexport)int _stdcall identity4(int init);
int _stdcall identity4(int init)
{//count ������ʹ�ò��� init ��ʼ����̬�����α��� S ����ʹ S �Լ� 1 �󷵻ظ�ֵ

	return init;
}

extern "C" _declspec(dllexport)int _stdcall identity2(LPCTSTR init);
int _stdcall identity2(LPCTSTR init)
{//count ������ʹ�ò��� init ��ʼ����̬�����α��� S ����ʹ S �Լ� 1 �󷵻ظ�ֵ

	return 1;
}


bool main()
{
	string picsrc = "test4.jpg";
	int flag = 0;
	Mat image = imread(picsrc, CV_LOAD_IMAGE_GRAYSCALE);//��ȡͼƬ�����лҶȻ�����  

	threshold(image, image, 180 , 255, CV_THRESH_BINARY);//��ֵ��  

	imshow("origin", image);//��ʾͼƬ  

	//��ȡ����  
	std::vector<std::vector<Point>> contours;
	//��ȡ������  
	findContours(image,         //ͼ��  
		contours,               //������  
		//����ͼ�����˽ṹ����Ϣ����ѡ����������û��ѡ��  
		CV_RETR_EXTERNAL,           //��ȡ�����ķ����������ȡ��Χ������  
		CV_CHAIN_APPROX_NONE);      //�������Ƶķ��������ﲻ���ƣ���ȡȫ��������  
	//��ӡ������Ϣ  
	std::cout<<"������Χ������"<<contours.size()<<"��"<<std::endl;  
	if(contours.size()==0)
	{
		std::cout<<"����������"<<"sasasasa"<<std::endl;  
		flag = 1;
		std::cout<<"flag��"<<flag<<std::endl;  
		return false;


	}
	else
	{
		std::vector<std::vector<Point>>::const_iterator itContours = contours.begin();  
		for(;itContours != contours.end();++itContours)  
		{  
			std::cout<<"ÿ�������ĳ���: "<<itContours->size()<<std::endl;  
		}  

		//��������  
		Mat result(image.size(),CV_8U,Scalar(255));  
		////��������������Ϊ�����壬����������ָʾ�����ﻭ����������������ɫ���ߴ�  
		drawContours(result,contours,-1,Scalar(0),2);  
		//imshow("��ȡ��Χ����",result);  

		findContours(image,         //ͼ��  
			contours,               //������  
			//����ͼ�����˽ṹ����Ϣ����ѡ����������û��ѡ��  
			CV_RETR_LIST,           //��ȡ�����ķ����������ȡ����������  
			CV_CHAIN_APPROX_NONE);      //�������Ƶķ��������ﲻ���ƣ���ȡȫ������  
		//��������  
		drawContours(result,contours,-1,Scalar(0),2);  
		imshow("��ȡ��������",result);  

		//��ȥ̫������̫�̵�����  
		int cmin = 100;  
		int cmax = 100000;  
		std::vector<std::vector<Point>>::const_iterator itc = contours.begin();  
		while(itc != contours.end())  
		{  
			if(itc->size()<cmin || itc->size()>cmax)  
				itc = contours.erase(itc);  
			else  
				++itc;  
		}  

		//�ѽ������Դͼ���ϣ�  
		Mat original = imread(picsrc);  
		if(!original.data)  
			return -1;  
		drawContours(original,contours,-1,Scalar(255,255,255),2);  
		imshow("���������",original);  

		//�������ػ��ڰװ���  
		result.setTo(Scalar(255));  
		drawContours(result,contours,-1,Scalar(0),1);  



		//��������״������  
		//��Ӿ���  
		Rect r0 = boundingRect(Mat(contours[0]));  
		rectangle(result,r0,Scalar(0),2);  

		//��С���Բ  
		float radius;  
		Point2f center;  
		minEnclosingCircle(Mat(contours[1]),center,radius);  
		circle(result,Point(center),static_cast<int>(radius),Scalar(0),2);  

		//����ι���  
		std::vector<Point> poly;  
		//����Ϊ������ͼ���2ά�㼯�������������ƾ��ȣ��Ƿ�պ�  
		approxPolyDP(Mat(contours[2]),poly,5,true);  
		std::cout<<"����δ�С��"<<poly.size()<<std::endl;  
		//�������  
		std::vector<Point>::const_iterator itp = poly.begin();  
		while(itp != poly.end()-1)  
		{  
			line(result,*itp,*(itp+1),Scalar(0),2);  
			++itp;  
		}  
		//����һ��������һ��������  
		line(result,*(poly.begin()),*(poly.end()-1),Scalar(128),2);  


		//����͹��  
		std::vector<Point> hull;  
		convexHull(Mat(contours[3]),hull);  
		std::vector<cv::Point>::const_iterator it= hull.begin();  
		while(it != (hull.end()-1))  
		{  
			line(result,*it,*(it+1),Scalar(0),2);  
			++it;  
		}  
		line(result,*(hull.begin()),*(hull.end()-1),Scalar(0),2);  


		//�������Ϣ  
		itc = contours.begin();  
		int mom_num = 0;
		while(itc != contours.end())  
		{  
			//�������еľ�  
			Moments mom = moments(Mat(*itc++));  
			//���㲢��������  
			circle(result,Point(mom.m10/mom.m00,mom.m01/mom.m00),2,Scalar(2),2);  
			mom_num++;
		}   

		if(mom_num>0)
		{
			std::cout<<"����������"<<mom_num<<std::endl;  

		}

		imshow("��״������",result);   
		std::cout<<"flag��"<<flag<<std::endl;  
		return true;

	}

	waitKey();
}
