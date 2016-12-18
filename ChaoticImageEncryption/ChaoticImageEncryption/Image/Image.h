#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "..\math\math.h"
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>

namespace ChaoticEncrypt
{
	class Image
	{
	public:

		/*
		function:	计算灰度图像的信息熵

		Param:
			pImage:		将要被计算的图像

		return:		图像的信息熵
		*/
		static double GrayImageEntropy(const CImage *pImage);

		/*
		function:	统计每个像素值出现的次数

		Param：
			pImage:	被统计像素出现次数的图像

		return:	统计每个像素出现的次数
		*/
		static std::vector<size_t> StatisticsPixel(const CImage *pImage);

		
		/*
		function: 计算图像的三个参数//  PSNR  SNR  MSE

		Param：
			First：		原始图像
			Second：		密文图像

		return:		返回PSNR,SNR,MSE三个数的容器
		*/
		static std::vector<double> PSNR_SNR_MSE(const CImage *First, const CImage *Second);
		

		/*
		function:	计算密文的图像的NPCR，UACI

		Param:
			EnOne:	密文图像
			EnTwo：	密文图像

		return:		返回NPCR,UACI两个数的容器
		*/
		static std::vector<double> NPCR_UACI(const CImage *EnOne, const CImage *EnTwo);


		/*
		function:	初始化图像的颜色表

		Param：
			pImage：		被计算颜色表的图像
		return：
		*/
		static void InitGrayImageColorTable(CImage *& pImage);


		/*
		function:	将灰度图像设置为纯色图像

		Param：
			pImage：		被设置的图像指针
		return：
		*/
		static void InitGrayImageToPureImage(CImage *& pImage, unsigned char k);

		/*
		function:	初始化彩色图像

		Param：
			pImage：		被设置的图像指针
			R:			像素值的红色分量
			G：			像素值的绿色分量
			B：			像素值的蓝色分量
		return：
		*/
		static void InitColorImage(CImage *&pImage, unsigned char R = 255,	\
			unsigned char G = 255, unsigned char B = 255);

		static size_t GrayImageSum(CImage *pImage);


		// 图像信号的相关系数
		// 水平方向，垂直方向，对角线方向
		/*
		function:	计算图像的相邻像素的相关性

		Param:
			pImage:		被计算相邻像素相关性的图像

		return:		返回水平方向，垂直方向，对角线方向的相关系数
		*/
		static std::vector<double> CorrelationCoefficient(const CImage *pImage);

		/*
		function:	根据直方图构建CImage图像

		Param:
			Hist:	灰度图像对应的直方图
			L：		图像的像素个数

		return:		由原始图像的直方图构建的CImage图像
		*/
		//static CImage * ImageHist(std::vector<size_t> &Hist, size_t L);

		/*
		function:	根据直方图构建CImage图像

		Param:
			Hist:	灰度图像对应的直方图
	
		return:		由原始图像的直方图构建的CImage图像
		*/
		static CImage * HistFromVector(std::vector<size_t> &Hist);
		static CImage * HistFromImage(const CImage *pImage);

		/*
		function:	计算水平方向、垂直方向、对角线方向相邻像素的关系图

		return:
		*/
		static CImage * HorzRelative(const CImage * pImage);
		static CImage * VertRelative(const CImage * pImage);
		static CImage * DiagRelative(const CImage * pImage);
		static std::vector<CImage*>* ImageRelative(const CImage *pImage);

		/*
		function:	将灰度图像转化成序列

		Param:
			pImage:		将要被转化成序列的图像指针

		return：		序列指针
		*/
		static unsigned char *GrayImageToSequence(const CImage *pImage);

		/*
		function:	输出图像像素

		Param:	
			pImage:		灰度图像像素指针
		*/
		static void OutputImage(CImage *pImage);
		


		/*
		function:	输出图像像素

		Param:
			pImage:		将像素值输出到文件的图像指针（灰度图像像素指针）
			FilePath:	输出到的文件路径

		return:	
		*/
		static void OutputToFile(CImage *pImage, std::string FilePath);

		/*
		function:	将char序列转化成灰度图像

		Param:
			Seq:		将要被转化成图像的序列指针
			rowImage:	图像宽度
			colImage:	图像高度

		return：		灰度图像指针
		*/
		static CImage * SequenceToGrayImage(unsigned char *Seq, size_t rowImage, size_t colImage);

		/*
		function:	将数据写入文件,（写入模式为先清空文件）

		Param:
			Array:		数据指针
			N：			数组长度
			FilePath：	被写入的文件路径
		*/
		template<typename type>
		static bool SaveToFile(type *Array, size_t N, std::string FilePath)
		{
			std::ofstream fw;
			fw.open(FilePath.c_str());
			if (fw.is_open())
			{
				for (size_t i = 0; i < N; ++i)
				{
					fw << Array[i] << "\n";
				}
				fw.flush();

				fw.clear();
				fw.close();
				return true;
			}
			return false;
			
		}

		template<typename type>
		static bool IsEqualFile(type *Array, size_t N, std::string FilePath)
		{
			std::ifstream fw;
			fw.open(FilePath.c_str());
			if (fw.is_open())
			{
				type tmp;
				size_t i = 0;
				while ((fw >> tmp) && (i < N))
				{
					if (Array[i] != tmp)
					{
						return false;
					}
					++i;
				}
				//fw.flush();
				fw.clear();
				fw.close();
				return true;
			}
			return false;
		}

		template<typename type>
		static void OutputArray(type *Array, size_t N)
		{
			if (Array)
			{
				size_t i = 0;
				for (; i < N - 3; i = i + 3)
				{
					TRACE3("First = %d, Second = %d, Three = %d\n", Array[i], Array[i + 1], Array[i + 2]);
				}
				if (N - i == 1)
				{
					TRACE1("First = %d\n", Array[i]);
				}
				else if (N - i == 2)
				{
					TRACE2("First = %d, Second = %d\n", Array[i], Array[i + 1]);
				}
			}
		}



		template<typename type>
		static CImage * CreateImageFromData(type *Array, size_t Length, double MinValue, double MaxValue)
		{
			if (Length > GrayImageLevel)
			{
				return nullptr;
			}
			CImage *Lst = new CImage;
			Lst->Create(GrayImageLevel, GrayImageLevel, ColorImageBits);
			//type MaxCount = *std::max_element(Array, Array + Length);

			InitColorImage(Lst, 255, 255, 255);
			size_t Pixel = 0;
			double tmpSpacePixel = MaxValue - MinValue;
			for (size_t i = 0; i < Length; ++i)
			{
				if (Array[i] <= MinValue)
				{
					Pixel = 0;
				}
				else if (Array[i] >= MaxValue)
				{
					Pixel = GrayImageLevel;
				}
				else
				{
					Pixel = static_cast<size_t>((Array[i] - MinValue) / static_cast<double>(tmpSpacePixel)* GrayImageLevel);
				}
				
				for (size_t j = 0; j < Pixel; ++j)
				{
					Lst->SetPixelRGB(i, GrayImageLevel - j - 1, 0, 0, 255);
				}
			}
			return Lst;
		}

	private:
		static enum { nMaxPixelValue = 180 };

		/*
		function:	信息熵

		Param：
		Hist：	Hist[i]表示信号i出现的次数

		return:	统计结果为Hist的信息熵

		*/
		static double GrayImageEntropy(std::vector<size_t> &Hist);
		
	};
}
