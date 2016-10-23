// idtetity.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

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

extern "C" _declspec(dllexport)int _stdcall identity3(LPCTSTR imagesrc);
int _stdcall identity3(LPCTSTR imagesrc)
{//count 函数，使用参数 init 初始化静态的整形变量 S ，并使 S 自加 1 后返回该值
 
	/*string picsrc = "test4.jpg";*/
	string picsrc = string((char*)imagesrc); 
	int flag = 0;
	Mat image = imread(picsrc, CV_LOAD_IMAGE_GRAYSCALE);//读取图片并进行灰度化处理  
	threshold(image, image, 180 , 255, CV_THRESH_BINARY);//二值化  
	//获取轮廓  
	std::vector<std::vector<Point>> contours;
	//获取轮廓：  
	findContours(image,         //图像  
		contours,               //轮廓点  
		//包含图像拓扑结构的信息（可选参数，这里没有选）  
		CV_RETR_EXTERNAL,           //获取轮廓的方法（这里获取外围轮廓）  
		CV_CHAIN_APPROX_NONE);      //轮廓近似的方法（这里不近似，获取全部轮廓）

	if(contours.size()==0)
	{ 
		
		std::cout<<"flag："<<flag<<std::endl;  
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
	Mat image = imread(picsrc, CV_LOAD_IMAGE_GRAYSCALE);//读取图片并进行灰度化处理  

	threshold(image, image, 180 , 255, CV_THRESH_BINARY);//二值化  

	imshow("origin", image);//显示图片  

	//获取轮廓  
	std::vector<std::vector<Point>> contours;
	//获取轮廓：  
	findContours(image,         //图像  
		contours,               //轮廓点  
		//包含图像拓扑结构的信息（可选参数，这里没有选）  
		CV_RETR_EXTERNAL,           //获取轮廓的方法（这里获取外围轮廓）  
		CV_CHAIN_APPROX_NONE);      //轮廓近似的方法（这里不近似，获取全部轮廓）  
	//打印轮廓信息  
	std::cout<<"共有外围轮廓："<<contours.size()<<"条"<<std::endl;  
	if(contours.size()==0)
	{
		std::cout<<"质心数量："<<"sasasasa"<<std::endl;  
		flag = 1;
		std::cout<<"flag："<<flag<<std::endl;  
		return false;
		

	}
	else
	{
		std::vector<std::vector<Point>>::const_iterator itContours = contours.begin();  
		for(;itContours != contours.end();++itContours)  
		{  
			std::cout<<"每个轮廓的长度: "<<itContours->size()<<std::endl;  
		}  

		//画出轮廓  
		Mat result(image.size(),CV_8U,Scalar(255));  
		////画出轮廓，参数为：画板，轮廓，轮廓指示（这里画出所有轮廓），颜色，线粗  
		drawContours(result,contours,-1,Scalar(0),2);  
		//imshow("提取外围轮廓",result);  

		findContours(image,         //图像  
			contours,               //轮廓点  
			//包含图像拓扑结构的信息（可选参数，这里没有选）  
			CV_RETR_LIST,           //获取轮廓的方法（这里获取所有轮廓）  
			CV_CHAIN_APPROX_NONE);      //轮廓近似的方法（这里不近似，获取全部轮廓  
		//画出轮廓  
		drawContours(result,contours,-1,Scalar(0),2);  
		imshow("提取所有轮廓",result);  

		//除去太长或者太短的轮廓  
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

		//把结果画在源图像上：  
		Mat original = imread(picsrc);  
		if(!original.data)  
			return -1;  
		drawContours(original,contours,-1,Scalar(255,255,255),2);  
		imshow("动物的轮廓",original);  

		//将轮廓重绘于白板上  
		result.setTo(Scalar(255));  
		drawContours(result,contours,-1,Scalar(0),1);  



		//轮廓的形状描述子  
		//外接矩形  
		Rect r0 = boundingRect(Mat(contours[0]));  
		rectangle(result,r0,Scalar(0),2);  

		//最小外接圆  
		float radius;  
		Point2f center;  
		minEnclosingCircle(Mat(contours[1]),center,radius);  
		circle(result,Point(center),static_cast<int>(radius),Scalar(0),2);  

		//多边形估计  
		std::vector<Point> poly;  
		//参数为：输入图像的2维点集，输出结果，估计精度，是否闭合  
		approxPolyDP(Mat(contours[2]),poly,5,true);  
		std::cout<<"多边形大小："<<poly.size()<<std::endl;  
		//画出结果  
		std::vector<Point>::const_iterator itp = poly.begin();  
		while(itp != poly.end()-1)  
		{  
			line(result,*itp,*(itp+1),Scalar(0),2);  
			++itp;  
		}  
		//将第一个点和最后一点连起来  
		line(result,*(poly.begin()),*(poly.end()-1),Scalar(128),2);  


		//计算凸包  
		std::vector<Point> hull;  
		convexHull(Mat(contours[3]),hull);  
		std::vector<cv::Point>::const_iterator it= hull.begin();  
		while(it != (hull.end()-1))  
		{  
			line(result,*it,*(it+1),Scalar(0),2);  
			++it;  
		}  
		line(result,*(hull.begin()),*(hull.end()-1),Scalar(0),2);  


		//计算矩信息  
		itc = contours.begin();  
		int mom_num = 0;
		while(itc != contours.end())  
		{  
			//计算所有的距  
			Moments mom = moments(Mat(*itc++));  
			//计算并画出质心  
			circle(result,Point(mom.m10/mom.m00,mom.m01/mom.m00),2,Scalar(2),2);  
			mom_num++;
		}   

		if(mom_num>0)
		{
			std::cout<<"质心数量："<<mom_num<<std::endl;  

		}

		imshow("形状描述子",result);   
		std::cout<<"flag："<<flag<<std::endl;  
		return true;
		
	}

	waitKey();
}
