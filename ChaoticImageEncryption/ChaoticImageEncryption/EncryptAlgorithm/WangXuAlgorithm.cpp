#include "stdafx.h"
#include "WangXuAlgorithm.h"
#include "..\Image\Image.h"
#include "..\ChaoticSystem\PWLCM.h"


WangXuAlgorithm::WangXuAlgorithm()
{
}


WangXuAlgorithm::~WangXuAlgorithm()
{
}

//	Param:		
//	KeyValue:	0.2, 0.2, 0.2, 0.3, 10, 100

std::unique_ptr<CImage> WangXuAlgorithm::EnCode(CImage *pImage, \
	std::vector<double> Param, std::vector<double> KeyValue)
{
	std::unique_ptr<CImage> EnImage(new CImage);
	if (pImage->GetBPP() == GrayImageBits)
	{
		size_t rowImage = pImage->GetWidth();
		size_t colImage = pImage->GetHeight();

		EnImage->Create(rowImage, colImage, GrayImageBits);
		CImage *pEnImage = EnImage.get();
		ChaoticEncrypt::Image::InitGrayImageColorTable(pEnImage);

		if (KeyValue.size() != 6)
		{
			return EnImage;
		}

		for (size_t i = 0; i < rowImage; ++i)
		{
			for (size_t j = 0; j < colImage; ++j)
			{
				pEnImage->SetPixel(i, j, pImage->GetPixel(i, j));
			}
		}
		
		size_t L = rowImage * colImage;

		//size_t Count = 0;
		double U = KeyValue[0];
		double V = KeyValue[1];
		

		
		size_t ImageSum = ChaoticEncrypt::Image::GrayImageSum(EnImage.get());
		double Delta = (ImageSum / static_cast<double>(pow(10, 14)) - static_cast<int>(ImageSum / static_cast<double>(pow(10, 14)))) / static_cast<double>(100);

		U = U - Delta;
		if (U <= 0 || U >= 1)
		{
			U = fabs(U);
			U = U - static_cast<int>(U);
		}
		V = V - Delta;
		if (V <= 0 || V >= 1)
		{
			V = fabs(V);
			V = V - static_cast<int>(V);
		}

		for (size_t i = 0; i < rowImage; ++i)
		{
			for (size_t j = 0; j < colImage; ++j)
			{
				double a = U * 2 * PI;
				double b = V * PI;

				size_t x = static_cast<size_t>(KeyValue[4] * sin(a) * cos(b)) % rowImage;
				size_t y = static_cast<size_t>(KeyValue[4] * sin(a) * sin(b)) % colImage;

				size_t temp = EnImage->GetPixel(i, j);
				EnImage->SetPixel(i, j, EnImage->GetPixel(x, y));
				EnImage->SetPixel(x, y, temp);

				U = 3.925 * U * (1 - U);
				V = 3.925 * V * (1 - V);
			}
		}
		
		U = KeyValue[0];
		V = KeyValue[1];
		
		std::vector<double*> *Seq = nullptr;

		do
		{
			std::vector<double> tmpParam;
			tmpParam.push_back(KeyValue[3]);

			std::vector<double> tmpInitValue;
			tmpInitValue.push_back(KeyValue[2]);

			Seq = PWLCM::GetInstance()->CreateSequence(tmpParam, tmpInitValue, L + 1);

		} while (0);
		
		if (Seq == nullptr)
		{
			return EnImage;
		}
		//tmpInitValue.clear();
		//tmpInitValue.push_back((*Seq->data())[L]);

		for (size_t i = 0; i < rowImage; ++i)
		{
			for (size_t j = 0; j < colImage; ++j)
			{
				U = 3.925 * U * (1 - U);
				V = 3.925 * V * (1 - V);
				size_t tmpU = static_cast<size_t>(U * pow(10, 10)) % GrayImageLevel;
				size_t tmpV = static_cast<size_t>(V * pow(10, 10)) % GrayImageLevel;
				if ((i == 0) && (j == 0))
				{
					size_t d = static_cast<size_t>((*Seq->data())[0] * pow(10, 14)) % GrayImageLevel;
					size_t temp = (EnImage->GetPixel(0, 0) % GrayImageLevel + tmpU) % GrayImageLevel;
					temp = temp ^ d ^ static_cast<size_t>(KeyValue[5] + tmpV) % GrayImageLevel;
					EnImage->SetPixelRGB(0, 0, temp, temp, temp);
				}
				else
				{
					size_t d = static_cast<size_t>((*Seq->data())[i * colImage + j] * pow(10, 14)) % GrayImageLevel;
					size_t temp = 0;
					if (j == 0)
					{
						temp = (EnImage->GetPixel(i - 1, colImage - 1) % GrayImageLevel + tmpV) % GrayImageLevel;
					}
					else
					{
						temp = (EnImage->GetPixel(i, j - 1) % GrayImageLevel + tmpV) % GrayImageLevel;
					}
					temp = ((EnImage->GetPixel(i, j) % GrayImageLevel + tmpU) % GrayImageLevel) ^ temp ^ d;
					EnImage->SetPixelRGB(i, j, temp, temp, temp);
				}
			}
		}
		FreeVec(Seq);
		
		
	}
	return EnImage;
}

std::unique_ptr<CImage> WangXuAlgorithm::DnCode(CImage *pImage, \
	std::vector<double> Param, std::vector<double> KeyValue)
{
	std::unique_ptr<CImage> DnImage(new CImage);
	if (pImage->GetBPP() == GrayImageBits)
	{
		size_t rowImage = pImage->GetWidth();
		size_t colImage = pImage->GetHeight();

		DnImage->Create(rowImage, colImage, GrayImageBits);
		CImage *pDnImage = DnImage.get();
		ChaoticEncrypt::Image::InitGrayImageColorTable(pDnImage);

		if (KeyValue.size() != 6)
		{
			return DnImage;
		}

		for (size_t i = 0; i < rowImage; ++i)
		{
			for (size_t j = 0; j < colImage; ++j)
			{
				pDnImage->SetPixel(i, j, pImage->GetPixel(i, j));
			}
		}

		size_t L = rowImage * colImage;

		//size_t Count = 0;
		double U = KeyValue[0];
		double V = KeyValue[1];

		std::vector<double*> *Seq = nullptr;

		do
		{
			std::vector<double> tmpParam;
			tmpParam.push_back(KeyValue[3]);

			std::vector<double> tmpInitValue;
			tmpInitValue.push_back(KeyValue[2]);

			Seq = PWLCM::GetInstance()->CreateSequence(tmpParam, tmpInitValue, L + 1);

		} while (0);

		if (Seq == nullptr)
		{
			return DnImage;
		}
		double *tmpArrayU = new double[L];
		memset(tmpArrayU, 0, sizeof(double)* L);
		tmpArrayU[0] = 3.925 * U *(1 - U);
		for (size_t i = 1; i < L; ++i)
		{
			tmpArrayU[i] = 3.925 * tmpArrayU[i - 1] * (1 - tmpArrayU[i - 1]);
		}

		double *tmpArrayV = new double[L];
		memset(tmpArrayV, 0, sizeof(double)* L);
		tmpArrayV[0] = 3.925 * V * (1 - V);
		for (size_t i = 1; i < L; ++i)
		{
			tmpArrayV[i] = 3.925 * tmpArrayV[i - 1] * (1 - tmpArrayV[i - 1]);
		}

		size_t tmpBegin = L - 1;
		for (size_t i = rowImage - 1; i != -1; --i)
		{
			for (size_t j = colImage - 1; j != -1; --j)
			{
				size_t tmpU = static_cast<size_t>(tmpArrayU[tmpBegin] * pow(10, 10)) % GrayImageLevel;
				size_t tmpV = static_cast<size_t>(tmpArrayV[tmpBegin] * pow(10, 10)) % GrayImageLevel;
				--tmpBegin;
				size_t CurPixel = pDnImage->GetPixel(i, j) % GrayImageLevel;
				if ((i == 0) && (j == 0))
				{
					size_t d = static_cast<size_t>((*Seq->data())[0] * pow(10, 14)) % GrayImageLevel;
					CurPixel = ((CurPixel ^ d ^ (static_cast<size_t>(KeyValue[5] + tmpV) % GrayImageLevel)) + GrayImageLevel - tmpU) % GrayImageLevel;
					//pDnImage->SetPixelRGB(i, j, CurPixel, CurPixel, CurPixel);
				}
				else
				{
					size_t d = static_cast<size_t>((*Seq->data())[i * colImage + j] * pow(10, 14)) % GrayImageLevel;
					size_t PrePixel = 0;
					if (j == 0)
					{
						PrePixel = (pDnImage->GetPixel(i - 1, colImage - 1) % GrayImageLevel + tmpV);
					}
					else
					{
						PrePixel = (pDnImage->GetPixel(i, j - 1) % GrayImageLevel + tmpV) % GrayImageLevel;
					}
					CurPixel = ((CurPixel ^ d ^ PrePixel) + GrayImageLevel - tmpU) % GrayImageLevel;
					//pDnImage->SetPixelRGB(i, j, CurPixel, CurPixel, CurPixel);
				}
				pDnImage->SetPixelRGB(i, j, CurPixel, CurPixel, CurPixel);
			}
		}
		FreeArray(tmpArrayU);
		FreeArray(tmpArrayV);
		FreeVec(Seq);

		U = KeyValue[0];
		V = KeyValue[1];
		size_t ImageSum = ChaoticEncrypt::Image::GrayImageSum(DnImage.get());
		double Delta = (ImageSum / static_cast<double>(pow(10, 14)) - static_cast<int>(ImageSum / static_cast<double>(pow(10, 14)))) / static_cast<double>(100);

		U = U - Delta;
		if (U <= 0 || U >= 1)
		{
			U = fabs(U);
			U = U - static_cast<int>(U);
		}
		V = V - Delta;
		if (V <= 0 || V >= 1)
		{
			V = fabs(V);
			V = V - static_cast<int>(V);
		}

		tmpArrayU = new double[L];
		memset(tmpArrayU, 0, sizeof(double)* L);
		tmpArrayU[0] = U;
		for (size_t i = 1; i < L; ++i)
		{
			tmpArrayU[i] = 3.925 * tmpArrayU[i - 1] * (1 - tmpArrayU[i - 1]);
		}

		tmpArrayV = new double[L];
		memset(tmpArrayV, 0, sizeof(double)* L);
		tmpArrayV[0] = V;
		for (size_t i = 1; i < L; ++i)
		{
			tmpArrayV[i] = 3.925 * tmpArrayV[i - 1] * (1 - tmpArrayV[i - 1]);
		}
		tmpBegin = L - 1;
		for (size_t i = rowImage - 1; i != -1; --i)
		{
			for (size_t j = colImage - 1; j != -1; --j)
			{
				double a = tmpArrayU[tmpBegin] * 2 * PI;
				double b = tmpArrayV[tmpBegin] * PI;
				--tmpBegin;
				size_t x = static_cast<size_t>(KeyValue[4] * sin(a) * cos(b)) % rowImage;
				size_t y = static_cast<size_t>(KeyValue[4] * sin(a) * sin(b)) % colImage;

				size_t temp = DnImage->GetPixel(i, j);
				DnImage->SetPixel(i, j, DnImage->GetPixel(x, y));
				DnImage->SetPixel(x, y, temp);
			}
		}
		FreeArray(tmpArrayU);
		FreeArray(tmpArrayV);

		////////

	}
	return DnImage;
}