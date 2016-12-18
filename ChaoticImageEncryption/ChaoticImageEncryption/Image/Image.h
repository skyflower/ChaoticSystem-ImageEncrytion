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
		function:	����Ҷ�ͼ�����Ϣ��

		Param:
			pImage:		��Ҫ�������ͼ��

		return:		ͼ�����Ϣ��
		*/
		static double GrayImageEntropy(const CImage *pImage);

		/*
		function:	ͳ��ÿ������ֵ���ֵĴ���

		Param��
			pImage:	��ͳ�����س��ִ�����ͼ��

		return:	ͳ��ÿ�����س��ֵĴ���
		*/
		static std::vector<size_t> StatisticsPixel(const CImage *pImage);

		
		/*
		function: ����ͼ�����������//  PSNR  SNR  MSE

		Param��
			First��		ԭʼͼ��
			Second��		����ͼ��

		return:		����PSNR,SNR,MSE������������
		*/
		static std::vector<double> PSNR_SNR_MSE(const CImage *First, const CImage *Second);
		

		/*
		function:	�������ĵ�ͼ���NPCR��UACI

		Param:
			EnOne:	����ͼ��
			EnTwo��	����ͼ��

		return:		����NPCR,UACI������������
		*/
		static std::vector<double> NPCR_UACI(const CImage *EnOne, const CImage *EnTwo);


		/*
		function:	��ʼ��ͼ�����ɫ��

		Param��
			pImage��		��������ɫ���ͼ��
		return��
		*/
		static void InitGrayImageColorTable(CImage *& pImage);


		/*
		function:	���Ҷ�ͼ������Ϊ��ɫͼ��

		Param��
			pImage��		�����õ�ͼ��ָ��
		return��
		*/
		static void InitGrayImageToPureImage(CImage *& pImage, unsigned char k);

		/*
		function:	��ʼ����ɫͼ��

		Param��
			pImage��		�����õ�ͼ��ָ��
			R:			����ֵ�ĺ�ɫ����
			G��			����ֵ����ɫ����
			B��			����ֵ����ɫ����
		return��
		*/
		static void InitColorImage(CImage *&pImage, unsigned char R = 255,	\
			unsigned char G = 255, unsigned char B = 255);

		static size_t GrayImageSum(CImage *pImage);


		// ͼ���źŵ����ϵ��
		// ˮƽ���򣬴�ֱ���򣬶Խ��߷���
		/*
		function:	����ͼ����������ص������

		Param:
			pImage:		������������������Ե�ͼ��

		return:		����ˮƽ���򣬴�ֱ���򣬶Խ��߷�������ϵ��
		*/
		static std::vector<double> CorrelationCoefficient(const CImage *pImage);

		/*
		function:	����ֱ��ͼ����CImageͼ��

		Param:
			Hist:	�Ҷ�ͼ���Ӧ��ֱ��ͼ
			L��		ͼ������ظ���

		return:		��ԭʼͼ���ֱ��ͼ������CImageͼ��
		*/
		//static CImage * ImageHist(std::vector<size_t> &Hist, size_t L);

		/*
		function:	����ֱ��ͼ����CImageͼ��

		Param:
			Hist:	�Ҷ�ͼ���Ӧ��ֱ��ͼ
	
		return:		��ԭʼͼ���ֱ��ͼ������CImageͼ��
		*/
		static CImage * HistFromVector(std::vector<size_t> &Hist);
		static CImage * HistFromImage(const CImage *pImage);

		/*
		function:	����ˮƽ���򡢴�ֱ���򡢶Խ��߷����������صĹ�ϵͼ

		return:
		*/
		static CImage * HorzRelative(const CImage * pImage);
		static CImage * VertRelative(const CImage * pImage);
		static CImage * DiagRelative(const CImage * pImage);
		static std::vector<CImage*>* ImageRelative(const CImage *pImage);

		/*
		function:	���Ҷ�ͼ��ת��������

		Param:
			pImage:		��Ҫ��ת�������е�ͼ��ָ��

		return��		����ָ��
		*/
		static unsigned char *GrayImageToSequence(const CImage *pImage);

		/*
		function:	���ͼ������

		Param:	
			pImage:		�Ҷ�ͼ������ָ��
		*/
		static void OutputImage(CImage *pImage);
		


		/*
		function:	���ͼ������

		Param:
			pImage:		������ֵ������ļ���ͼ��ָ�루�Ҷ�ͼ������ָ�룩
			FilePath:	��������ļ�·��

		return:	
		*/
		static void OutputToFile(CImage *pImage, std::string FilePath);

		/*
		function:	��char����ת���ɻҶ�ͼ��

		Param:
			Seq:		��Ҫ��ת����ͼ�������ָ��
			rowImage:	ͼ����
			colImage:	ͼ��߶�

		return��		�Ҷ�ͼ��ָ��
		*/
		static CImage * SequenceToGrayImage(unsigned char *Seq, size_t rowImage, size_t colImage);

		/*
		function:	������д���ļ�,��д��ģʽΪ������ļ���

		Param:
			Array:		����ָ��
			N��			���鳤��
			FilePath��	��д����ļ�·��
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
		function:	��Ϣ��

		Param��
		Hist��	Hist[i]��ʾ�ź�i���ֵĴ���

		return:	ͳ�ƽ��ΪHist����Ϣ��

		*/
		static double GrayImageEntropy(std::vector<size_t> &Hist);
		
	};
}
