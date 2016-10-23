// idtetity.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

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

extern "C" _declspec(dllexport)int _stdcall identity3(LPCTSTR imagesrc);
int _stdcall identity3(LPCTSTR imagesrc)
{//count ������ʹ�ò��� init ��ʼ����̬�����α��� S ����ʹ S �Լ� 1 �󷵻ظ�ֵ
 
	/*string picsrc = "test4.jpg";*/
	string picsrc = string((char*)imagesrc); 
	int flag = 0;
	Mat image = imread(picsrc, CV_LOAD_IMAGE_GRAYSCALE);//��ȡͼƬ�����лҶȻ�����  
	threshold(image, image, 180 , 255, CV_THRESH_BINARY);//��ֵ��  
	//��ȡ����  
	std::vector<std::vector<Point>> contours;
	//��ȡ������  
	findContours(image,         //ͼ��  
		contours,               //������  
		//����ͼ�����˽ṹ����Ϣ����ѡ����������û��ѡ��  
		CV_RETR_EXTERNAL,           //��ȡ�����ķ����������ȡ��Χ������  
		CV_CHAIN_APPROX_NONE);      //�������Ƶķ��������ﲻ���ƣ���ȡȫ��������

	if(contours.size()==0)
	{ 
		
		std::cout<<"flag��"<<flag<<std::endl;  
		return flag;	
	}

	else
	{
		flag = 1;
		 return flag;			
	}


	//return init;
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
