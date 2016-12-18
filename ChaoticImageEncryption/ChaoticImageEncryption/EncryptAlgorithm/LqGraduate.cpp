#include "stdafx.h"
#include "LqGraduate.h"
#include "..\Image\Image.h"
#include "..\ChaoticSystem\PWLCM.h"

LqGraduate::LqGraduate()
{

}

LqGraduate::~LqGraduate()
{

}

//% Param = [10 8/3 16 -0.69999 0.001 25000 200 1.2 0.3 30];
//% InitValue = [0.72345 0.8783 0.27965 0.3462];

unsigned char* LqGraduate::GenerateChaticSeq(std::vector<double> Param, std::vector<double> InitValue)
{
	if ((Param.size() != 10) || (InitValue.size() != 4))
	{
		return nullptr;
	}
	std::vector<double> ChaoticParam;
	ChaoticParam.push_back(Param[7]);
	ChaoticParam.push_back(Param[8]);
	std::vector<double> ChaoticInitValue;
	ChaoticInitValue.push_back(InitValue[0]);
	ChaoticInitValue.push_back(InitValue[3]);
	vector<double*> * tmpVec = Henon::GetInstance()->CreateSequence(ChaoticParam, ChaoticInitValue, Param[6]);
	InitValue[0] = *(*tmpVec->data() + static_cast<unsigned int>(Param[6]) - 1);
	InitValue[3] = (*tmpVec)[1][static_cast<unsigned int>(Param[6] - 1)];
	//HenonInitValue.clear();
	FreeVec(tmpVec);
	ChaoticInitValue[0] = InitValue[1];
	ChaoticInitValue[1] = InitValue[2];

	tmpVec = Henon::GetInstance()->CreateSequence(ChaoticParam, ChaoticInitValue, Param[6]);
	InitValue[1] = *(*tmpVec->data() + static_cast<unsigned int>(Param[6]) - 1);
	InitValue[2] = (*tmpVec)[1][static_cast<unsigned int>(Param[6] - 1)];
	FreeVec(tmpVec);

	ChaoticParam.clear();
	for (size_t i = 0; i < 5; ++i)
	{
		ChaoticParam.push_back(Param[i]);
	}
	tmpVec = SuperChen::GetInstance()->CreateSequence(ChaoticParam, ChaoticInitValue, Param[5]);
	
	size_t nBitLength = static_cast<size_t>(Param[5] * tmpVec->size());
	unsigned char *pResult = new unsigned char[nBitLength];
	memset(pResult, 0, sizeof(unsigned char)* nBitLength);

	size_t Begin = 0;
	size_t nBitsCount = Param[9];
	for (size_t i = 0; i < Param[5]; ++i)
	{
		for (size_t j = 0; j < tmpVec->size(); ++j)
		{
			double * p = *(tmpVec->data() + j);
			int IntPart = static_cast<int>(p[i]);
			IntPart = (IntPart % nBitsCount + nBitsCount) % nBitsCount;
			double DecimalPart = p[i] - floor(p[i]);
			pResult[Begin++] = static_cast<int>(DecimalPart * pow(2, IntPart)) & 1;
		}
	}
	return pResult;
}


std::unique_ptr<CImage> LqGraduate::EnCode(CImage *pImage, \
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

		if ((Param.size() != 6) || (KeyValue.size() != 7))
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

		unsigned int L = rowImage * colImage;
		size_t nBitSize = (L * ceil(log2(L)) + 3 * L * GrayImageBits) / SuperChen::GetInstance()->GetDimension();
		std::vector<double> ChaoticParam = {Param[0], Param[1], Param[2], KeyValue[0], \
			Param[3], static_cast<double>(nBitSize), Param[4], \
			KeyValue[1], KeyValue[2], Param[5] };
		
		std::vector<double> ChaoticInitValue = {KeyValue[3], KeyValue[4], KeyValue[5], KeyValue[6]};
		unsigned char *pBitSeq = GenerateChaticSeq(ChaoticParam, ChaoticParam);
		std::vector<unsigned int*> *tmpVec = GroupByToInt(pBitSeq, nBitSize, ceil(L), L, L, 1);
		
		unsigned char *ImageArray = ChaoticEncrypt::Image::GrayImageToSequence(pImage);
		for (size_t i = 0; i < L; ++i)
		{
			size_t Index = (*tmpVec->data())[i];
			unsigned char tmp = ImageArray[i];
			ImageArray[i] = ImageArray[Index];
			ImageArray[Index] = tmp;
		}
		FreeVec(tmpVec);
		size_t nMode = 3;
		tmpVec = GroupByToInt(pBitSeq + static_cast<int>(L * ceil(L)), nBitSize - L * ceil(L), GrayImageBits, GrayImageLevel, L, nMode);
		FreeArray(pBitSeq);

		unsigned int *E = *tmpVec->data();
		unsigned int *F = *(tmpVec->data() + 1);
		unsigned int *H = *(tmpVec->data() + 2);
		ImageArray[0] = E[0] ^ ((ImageArray[0] + F[0]) % GrayImageLevel);
		for (size_t i = 2; i < L; ++i)
		{
			unsigned char tmp = E[0] ^ ((ImageArray[i] + F[i]) % GrayImageLevel);
			ImageArray[i] = tmp ^ ((ImageArray[i - 1] + H[i]) % GrayImageLevel);
		}
		FreeVec(tmpVec);
		for (size_t i = 0; i < rowImage; ++i)
		{
			for (size_t j = 0; j < colImage; ++j)
			{
				size_t tmp = ImageArray[i * colImage + j];
				pEnImage->SetPixelRGB(i, j, tmp, tmp, tmp);
			}
		}
		FreeArray(ImageArray);
	}
	return EnImage;
}

std::unique_ptr<CImage> LqGraduate::DnCode(CImage *pImage, \
	std::vector<double> Param, std::vector<double> KeyValue)
{
	std::unique_ptr<CImage> DnImage(new CImage);
	if (pImage->GetBPP() == GrayImageBits)
	{

	}
	return DnImage;
}
