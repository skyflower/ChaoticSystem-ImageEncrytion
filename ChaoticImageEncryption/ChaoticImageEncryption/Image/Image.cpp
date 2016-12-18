
#include "stdafx.h"
#include <iostream>
#include "Image.h"


namespace ChaoticEncrypt
{

	std::vector<size_t> Image::StatisticsPixel(const CImage *pImage)
	{
		if (pImage == nullptr)
		{
			return std::vector<size_t>();
		}
		size_t PixelBits = pImage->GetBPP();
		std::vector<size_t> Hist(GrayImageLevel);
		memset(Hist.data(), 0, sizeof(size_t)* GrayImageLevel);

		size_t rowImage = pImage->GetWidth();
		size_t colImage = pImage->GetHeight();

		if (PixelBits == GrayImageBits)
		{
			for (size_t i = 0; i < rowImage; ++i)
			{
				for (size_t j = 0; j < colImage; ++j)
				{
					size_t tmp = pImage->GetPixel(i, j);
					Hist[tmp %GrayImageLevel] += 1;
				}
			}
		}
		else if (PixelBits == ColorImageBits)
		{
			for (size_t i = 0; i < rowImage; ++i)
			{
				for (size_t j = 0; j < colImage; ++j)
				{
					size_t tmp = pImage->GetPixel(i, j);
					Hist[tmp % GrayImageLevel] += 1;
					tmp = tmp / GrayImageLevel;
					Hist[tmp%GrayImageLevel] += 1;
					tmp = tmp / GrayImageLevel;
					Hist[tmp] += 1;
				}
			}
		}
		
		return Hist;
	}

	double Image::GrayImageEntropy(const CImage *pImage)
	{
		std::vector<size_t> && Hist = Image::StatisticsPixel(pImage);
		return GrayImageEntropy(Hist);
	}

	double Image::GrayImageEntropy(std::vector<size_t> & Hist)
	{
		
		size_t Length = Hist.size();
		size_t L = std::accumulate(Hist.begin(), Hist.end(), 0);
		double sum = 0.0;
		for (size_t i = 0; i < Length; ++i)
		{
			double temp = Hist[i] / static_cast<double>(L);
			sum = sum - temp * log2(temp);
		}
		return sum;
	}

	void Image::InitGrayImageColorTable(CImage *& pImage)
	{
		RGBQUAD* ColorTable;
		ColorTable = new RGBQUAD[GrayImageLevel];

		
		for (size_t i = 0; i < GrayImageLevel; ++i)
		{
			ColorTable[i].rgbBlue = ColorTable[i].rgbGreen = ColorTable[i].rgbRed = i;
			ColorTable[i].rgbReserved = 0;
		}
		pImage->SetColorTable(0, GrayImageLevel, ColorTable);

		delete ColorTable;
		ColorTable = nullptr;
	}

	std::vector<double> Image::PSNR_SNR_MSE(const CImage *First, const CImage *Second)
	{
		std::vector<double> p;
		if ((First == nullptr) || (Second == nullptr) ||	\
			(First->GetWidth() != Second->GetWidth()) ||	\
			(First->GetHeight() != Second->GetHeight()))
		{
			return p;
		}
		double MSE = 0.0;
		double SNR = 0.0;
		size_t rowImage = First->GetWidth();
		size_t colImage = First->GetHeight();

		for (size_t i = 0; i < rowImage; ++i)
		{
			for (size_t j = 0; j < colImage; ++j)
			{
				size_t FirstPixel = First->GetPixel(i, j) % GrayImageLevel;
				size_t SecondPixel = Second->GetPixel(i, j) % GrayImageLevel;
				MSE += (FirstPixel - SecondPixel) * (FirstPixel - SecondPixel);
				SNR += FirstPixel * FirstPixel;
			}
		}
		size_t L = rowImage * colImage;
		double PSNR = 10 * log10(L * (GrayImageLevel - 1) * (GrayImageLevel - 1) / MSE);
		SNR = 10 * log10(SNR / MSE);
		MSE = MSE / L;
		
		p.push_back(PSNR);
		p.push_back(MSE);
		p.push_back(SNR);
		return p;
	}


	// 图像信号的相关系数
	// 水平方向，垂直方向，对角线方向
	std::vector<double> Image::CorrelationCoefficient(const CImage *pImage)
	{
		std::vector<double> p;
		if ((pImage == nullptr) || (pImage->GetBPP() == GrayImageBits))
		{
			return p;
		}
		size_t rowImage = pImage->GetWidth();
		size_t colImage = pImage->GetHeight();
		size_t L = rowImage * colImage;
		size_t flag = 0;
		unsigned char *Array = new unsigned char[L];
		memset(Array, 0, sizeof(unsigned char)* L);


		size_t len = rowImage > colImage ? rowImage : colImage;
		double *tmp = new double[len];
		memset(tmp, 0, sizeof(double)* len);

		unsigned char **ImageMat = SequenceToMatrix(Array, rowImage, colImage);

		// 垂直方向
		for (size_t i = 0; i < colImage - 1; ++i)
		{
			tmp[i] = Coef(*(ImageMat + i), *(ImageMat + i + 1), rowImage);
		}
		double VCoef = AverageX(Array, colImage - 1);

		unsigned char **TImageMat = Transposition(ImageMat, rowImage, colImage);
		FreeMatrix(ImageMat, rowImage);

		//  水平方向
		memset(tmp, 0, sizeof(double)* len);
		for (size_t i = 0; i < rowImage - 1; ++i)
		{
			tmp[i] = Coef(*(TImageMat + i), *(TImageMat + i + 1), colImage);
		}
		double HCoef = AverageX(tmp, rowImage - 1);

		FreeMatrix(TImageMat, rowImage);
		FreeArray(tmp);

		//  对角线方向
		L = rowImage * colImage - rowImage - colImage + 1;
		unsigned char *First = new unsigned char[L];
		memset(First, 0, sizeof(unsigned char)* L);

		unsigned char *Second = new unsigned char[L];
		memset(Second, 0, sizeof(unsigned char)* L);

		size_t k = 0;
		len = rowImage * colImage;
		for (size_t i = 0; i < len - colImage; ++i)
		{
			if (((i + 1) % colImage) == 0)
			{
				continue;
			}
			First[k] = Array[i];
			Second[k] = Array[i + colImage + 1];
			k = k + 1;
		}
		double DiagCoef = Coef(First, Second, L);
		p.push_back(HCoef);
		p.push_back(VCoef);
		p.push_back(DiagCoef);

		FreeArray(Array);
		FreeArray(First);
		FreeArray(Second);

		return p;
	}


	void Image::InitGrayImageToPureImage(CImage *& pImage, unsigned char k)
	{
		if ( (pImage != nullptr) && (pImage->GetBPP() == GrayImageBits) )
		{
			if (pImage->GetMaxColorTableEntries() == 0)
			{
				InitGrayImageColorTable(pImage);
			}
			size_t rowImage = pImage->GetWidth();
			size_t colImage = pImage->GetHeight();
			for (size_t i = 0; i < rowImage; ++i)
			{
				for (size_t j = 0; j < colImage; ++j)
				{
					pImage->SetPixelRGB(i, j, k, k, k);
				}
			}
		}
	}

	void Image::InitColorImage(CImage *&pImage, unsigned char R, \
		unsigned char G, unsigned char B)
	{
		if (pImage->GetBPP() != ColorImageBits)
		{
			return;
		}
		if (pImage == nullptr)
		{
			pImage = new CImage;
			pImage->Create(GrayImageBits, GrayImageBits, ColorImageBits);
		}
		size_t rowImage = pImage->GetWidth();
		size_t colImage = pImage->GetHeight();
		for (size_t i = 0; i < rowImage; ++i)
		{
			for (size_t j = 0; j < colImage; ++j)
			{
				pImage->SetPixelRGB(i, j, R, G, B);
			}
		}
	}

	std::vector<double> Image::NPCR_UACI(const CImage *First, const CImage *Second)
	{
		std::vector<double> p;
		if ((First == nullptr) || (Second == nullptr) || \
			(First->GetWidth() != Second->GetWidth()) || \
			(First->GetHeight() != Second->GetHeight()))
		{
			return p;
		}
		double NPCR = 0.0;
		double UACI = 0.0;
		size_t rowImage = First->GetWidth();
		size_t colImage = First->GetHeight();
		size_t L = rowImage * colImage;
		for (size_t i = 0; i < rowImage; ++i)
		{
			for (size_t j = 0; j < colImage; ++j)
			{
				if (First->GetPixel(i, j) != Second->GetPixel(i, j))
				{
					size_t FirstPixel = First->GetPixel(i, j) % GrayImageLevel;
					size_t SecondPixel = Second->GetPixel(i, j) % GrayImageLevel;
					NPCR += 1;
					UACI += abs((double)FirstPixel - SecondPixel);
				}
			}
		}
		NPCR = NPCR / static_cast<double>(L);
		UACI = UACI / static_cast<double>((GrayImageLevel - 1) * L);
		p.push_back(NPCR);
		p.push_back(UACI);
		return p;
	}

	CImage * Image::HistFromVector(std::vector<size_t> &Hist)
	{
		CImage *Lst = new CImage;
		Lst->Create(GrayImageLevel, GrayImageLevel, ColorImageBits);
		size_t MaxCount = *std::max_element(Hist.begin(), Hist.end());
		size_t Length = Hist.size();

		InitColorImage(Lst, 255, 255, 255);

		for (size_t i = 0; i < Length; ++i)
		{
			size_t Pixel = static_cast<size_t>((Hist[i] / static_cast<double>(MaxCount)) * nMaxPixelValue);

			for (size_t j = 0; j < Pixel; ++j)
			{
				Lst->SetPixelRGB(i, GrayImageLevel - j - 1, 0, 0, 255);
			}
		}
		return Lst;
	}

	CImage * Image::HistFromImage(const CImage *pImage)
	{
		if (pImage && (pImage->GetBPP() == GrayImageBits))
		{
			size_t rowImage = pImage->GetWidth();
			size_t colImage = pImage->GetHeight();
			size_t *tmpNum = new size_t[GrayImageLevel];
			memset(tmpNum, 0, sizeof(size_t)* GrayImageLevel);
			
			for (size_t i = 0; i < rowImage; ++i)
			{
				for (size_t j = 0; j < colImage; ++j)
				{
					size_t && tmpValue = pImage->GetPixel(i, j) % GrayImageLevel;
					tmpNum[tmpValue] += 1;
				}
			}

			size_t MaxCount = *std::max_element(tmpNum, tmpNum + GrayImageLevel);
			
			CImage *Lst = new CImage;
			Lst->Create(GrayImageLevel, GrayImageLevel, ColorImageBits);
			InitColorImage(Lst, 255, 255, 255);
			for (size_t i = 0; i < GrayImageLevel; ++i)
			{
				size_t Pixel = static_cast<size_t>((tmpNum[i] / static_cast<double>(MaxCount)) * nMaxPixelValue);

				for (size_t j = 0; j < Pixel; ++j)
				{
					Lst->SetPixelRGB(i, GrayImageLevel - j - 1, 0, 0, 255);
				}
			}

			delete [] tmpNum;
			tmpNum = nullptr;
			return Lst;
		}
		return nullptr;
	}


	void Image::OutputImage(CImage *pImage)
	{
		if (pImage && (pImage->GetBPP() == GrayImageBits))
		{
			size_t rowImage = pImage->GetWidth();
			size_t colImage = pImage->GetHeight();
			for (size_t i = 0; i < rowImage; ++i)
			{
				for (size_t j = 0; j < colImage; ++j)
				{
					size_t tmp = pImage->GetPixel(i, j);
					TRACE3("i = %d, j  = %d, Pixel = %d\n", i, j, tmp % GrayImageLevel);
				}
			}
		}
	}

	void Image::OutputToFile(CImage *pImage, std::string FilePath)
	{
		if (pImage && (pImage->GetBPP() == GrayImageBits))
		{
			std::ofstream fw;
			fw.open(FilePath.c_str());
			if (fw.is_open())
			{
				size_t rowImage = pImage->GetWidth();
				size_t colImage = pImage->GetHeight();
				for (size_t i = 0; i < rowImage; ++i)
				{
					for (size_t j = 0; j < colImage; ++j)
					{
						size_t tmp = pImage->GetPixel(i, j) % GrayImageLevel;
						fw << tmp << "\t";
					}
					fw << "\n";
				}
			}
			fw.flush();
			fw.clear();
			fw.close();
		}
	}

	std::vector<CImage*>* Image::ImageRelative(const CImage *pImage)
	{
		if (pImage && (pImage->GetBPP() == GrayImageBits))
		{
			const size_t nRelative = 3;
			std::vector<CImage*> *p = new std::vector<CImage*>(nRelative);
			for (size_t i = 0; i < p->size(); ++i)
			{
				CImage *& tmp = *(p->data() + i);
				tmp = new CImage;
				tmp->Create(GrayImageLevel, GrayImageLevel, ColorImageBits);
				ChaoticEncrypt::Image::InitColorImage(tmp, GrayImageLevel - 1, GrayImageLevel - 1, GrayImageLevel - 1);
			}
			
			size_t rowImage = pImage->GetWidth();
			size_t colImage = pImage->GetHeight();

			for (size_t i = 0; i < rowImage - 1; ++i)
			{
				for (size_t j = 0; j < colImage - 1; ++j)
				{
					size_t CurPixel = pImage->GetPixel(i, j) % GrayImageLevel;
					size_t HorzPixel = pImage->GetPixel(i, j + 1) % GrayImageLevel;
					size_t VertPixel = pImage->GetPixel(i + 1, j) % GrayImageLevel;
					size_t DiagPixel = pImage->GetPixel(i + 1, j + 1) % GrayImageLevel;
					(*p)[0]->SetPixelRGB(CurPixel, HorzPixel, 0, 0, 255);
					(*p)[1]->SetPixelRGB(CurPixel, VertPixel, 0, 0, 255);
					(*p)[2]->SetPixelRGB(CurPixel, DiagPixel, 0, 0, 255);
				}
			}
			return p;
		}
		return nullptr;
	}

	CImage * Image::HorzRelative(const CImage * pImage)
	{
		if (pImage && (pImage->GetBPP() == GrayImageBits))
		{
			CImage *Horz = new CImage;
			Horz->Create(GrayImageLevel, GrayImageLevel, ColorImageBits);
			//ChaoticEncrypt::Image::InitGrayImageColorTable(Horz);
			size_t rowImage = pImage->GetWidth();
			size_t colImage = pImage->GetHeight();

			ChaoticEncrypt::Image::InitColorImage(Horz, 255, 255, 255);

			for (size_t i = 0; i < rowImage; ++i)
			{
				for (size_t j = 0; j < colImage - 1; ++j)
				{
					size_t FirstPixel = pImage->GetPixel(i, j) % GrayImageLevel;
					size_t SecondPixel = pImage->GetPixel(i, j + 1) % GrayImageLevel;
					Horz->SetPixelRGB(FirstPixel, SecondPixel, 0, 0, 255);
				}
			}
			return Horz;
		}
		return nullptr;
	}


	CImage * Image::VertRelative(const CImage * pImage)
	{
		if (pImage && (pImage->GetBPP() == GrayImageBits))
		{
			CImage *Vert = new CImage;
			Vert->Create(GrayImageLevel, GrayImageLevel, ColorImageBits);
			//ChaoticEncrypt::Image::InitGrayImageColorTable(Horz);
			size_t rowImage = pImage->GetWidth();
			size_t colImage = pImage->GetHeight();

			ChaoticEncrypt::Image::InitColorImage(Vert, 255, 255, 255);

			for (size_t i = 0; i < rowImage - 1; ++i)
			{
				for (size_t j = 0; j < colImage; ++j)
				{
					size_t FirstPixel = pImage->GetPixel(i, j) % GrayImageLevel;
					size_t SecondPixel = pImage->GetPixel(i + 1, j) % GrayImageLevel;
					Vert->SetPixelRGB(FirstPixel, SecondPixel, 0, 0, 255);
				}
			}
			return Vert;
		}
		return nullptr;
	}

	CImage * Image::DiagRelative(const CImage * pImage)
	{
		if (pImage && (pImage->GetBPP() == GrayImageBits))
		{
			CImage *Diag = new CImage;
			Diag->Create(GrayImageLevel, GrayImageLevel, ColorImageBits);
			//ChaoticEncrypt::Image::InitGrayImageColorTable(Horz);
			size_t rowImage = pImage->GetWidth();
			size_t colImage = pImage->GetHeight();

			ChaoticEncrypt::Image::InitColorImage(Diag, 255, 255, 255);

			for (size_t i = 0; i < rowImage - 1; ++i)
			{
				for (size_t j = 0; j < colImage - 1; ++j)
				{
					size_t FirstPixel = pImage->GetPixel(i, j) % GrayImageLevel;
					size_t SecondPixel = pImage->GetPixel(i + 1, j + 1) % GrayImageLevel;
					Diag->SetPixelRGB(FirstPixel, SecondPixel, 0, 0, 255);
				}
			}
			return Diag;
		}
		return nullptr;
	}

	unsigned char *Image::GrayImageToSequence(const CImage *pImage)
	{
		if (pImage)
		{
			size_t rowImage = pImage->GetWidth();
			size_t colImage = pImage->GetHeight();
			size_t L = rowImage * colImage;
			unsigned char *K = new unsigned char[L];
			memset(K, 0, sizeof(unsigned char)* L);
			size_t Begin = 0;
			for (size_t i = 0; i < rowImage; ++i)
			{
				for (size_t j = 0; j < colImage; ++j)
				{
					size_t tmp = pImage->GetPixel(i, j) % GrayImageLevel;
					K[Begin++] = tmp;
				}
			}
			return K;
		}
		return nullptr;
		
	}

	CImage * Image::SequenceToGrayImage(unsigned char *Seq, size_t rowImage, size_t colImage)
	{
		if (Seq || (rowImage > 0) || (colImage > 0))
		{
			CImage *pImage = new CImage;
			pImage->Create(rowImage, colImage, GrayImageBits);
			ChaoticEncrypt::Image::InitGrayImageColorTable(pImage);
			size_t Begin = 0;
			for (size_t i = 0; i < rowImage; ++i)
			{
				for (size_t j = 0; j < colImage; ++j)
				{
					unsigned char tmp = Seq[Begin];
					pImage->SetPixelRGB(i, j, tmp, tmp, tmp);
					++Begin;
				}
			}
			return pImage;
		}
		return nullptr;
	}

	size_t Image::GrayImageSum(CImage *pImage)
	{
		if (!pImage || pImage->IsNull() || pImage->GetBPP() != GrayImageBits)
		{
			return 0;
		}
		size_t Result = 0;
		size_t rowImage = pImage->GetWidth();
		size_t colImage = pImage->GetHeight();
		for (size_t i = 0; i != rowImage; ++i)
		{
			for (size_t j = 0; j != colImage; ++j)
			{
				size_t tmp = 0;
				tmp = pImage->GetPixel(i, j);
				Result += tmp % GrayImageLevel;
			}
		}
		return Result;
	}
}