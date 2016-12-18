#include "stdafx.h"
#include "testAlgorithm.h"
#include "..\ChaoticSystem\Logistic.h"
#include "..\math\math.h"
#include <atlimage.h>
#include "..\Image\Image.h"


testAlgorithm::testAlgorithm()
{
}


testAlgorithm::~testAlgorithm()
{
}


std::unique_ptr<CImage> testAlgorithm::EnCode(CImage *pImage, \
	std::vector<double> Param, std::vector<double> KeyValue)
{
	std::unique_ptr<CImage> EnImage(new CImage);

	if (Param.size() == 1 && KeyValue.size() == 1)
	{
		size_t rowImage = pImage->GetWidth();
		size_t colImage = pImage->GetHeight();
		size_t L = rowImage * colImage;
		
		EnImage->Create(rowImage, colImage, GrayImageBits);
		CImage *pEnImage = EnImage.get();
		ChaoticEncrypt::Image::InitGrayImageColorTable(pEnImage);
		ChaoticEncrypt::Image::InitGrayImageToPureImage(pEnImage, 0);

		std::vector<double*> *Seq = Logistic::GetInstance()->CreateSequence(Param, KeyValue, L);
		if (pImage && (GrayImageBits == pImage->GetBPP()))
		{
			double *Array = *Seq->begin();
			if (Array != nullptr)
			{
				size_t flag = 0;
				for (size_t i = 0; i < rowImage; ++i)
				{
					for (size_t j = 0; j < colImage; ++j)
					{
						size_t tmp = static_cast<size_t>(Array[flag] * 1000) % GrayImageLevel;
						++flag;
						tmp = (pImage->GetPixel(i, j) % GrayImageLevel) ^ tmp;
						EnImage->SetPixelRGB(i, j, tmp, tmp, tmp);
					}
				}
			}
		}
		FreeVec(Seq);
	}
	return EnImage;
}

std::unique_ptr<CImage> testAlgorithm::DnCode(CImage *pImage, \
	std::vector<double> Param, std::vector<double> KeyValue)
{
	std::unique_ptr<CImage> DnImage(new CImage(*pImage));
	if (Param.size() == 1 && KeyValue.size() == 1)
	{
		
		size_t rowImage = pImage->GetWidth();
		size_t colImage = pImage->GetHeight();
		size_t L = rowImage * colImage;

		std::vector<double*> *Seq = Logistic::GetInstance()->CreateSequence(Param, KeyValue, L);
		if (pImage && (GrayImageBits == pImage->GetBPP()))
		{
			double *Array = *Seq->begin();
			if (Array != nullptr)
			{
				size_t flag = 0;
				for (size_t i = 0; i < rowImage; ++i)
				{
					for (size_t j = 0; j < colImage; ++j)
					{
						size_t tmp = static_cast<size_t>(Array[flag] * 1000) % GrayImageLevel;
						++flag;
						tmp = (pImage->GetPixel(i, j) % GrayImageLevel) ^ tmp;
						DnImage->SetPixelRGB(i, j, tmp, tmp, tmp);
					}
				}
			}
		}
		FreeVec(Seq);
	}
	return DnImage;
}