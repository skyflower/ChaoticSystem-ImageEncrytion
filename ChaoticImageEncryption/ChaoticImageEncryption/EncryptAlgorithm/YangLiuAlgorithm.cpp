#include "stdafx.h"
#include "YangLiuAlgorithm.h"
#include "..\Image\Image.h"
#include "..\ChaoticSystem\SuperChen.h"
#include <cmath>
#include <cstdlib>


YangLiuAlgorithm::YangLiuAlgorithm()
{
}


YangLiuAlgorithm::~YangLiuAlgorithm()
{
}

std::unique_ptr<CImage> YangLiuAlgorithm::EnCode(CImage *pImage,	\
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
		
		if ((Param.size() != 7) || (KeyValue.size() != 8))
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
		size_t N = 2 * L;

		std::vector<double> InitValueOne;
		InitValueOne.push_back(KeyValue[0]);
		InitValueOne.push_back(KeyValue[1]);
		InitValueOne.push_back(KeyValue[4]);
		InitValueOne.push_back(KeyValue[5]);

		std::vector<double> InitValueTwo;
		InitValueTwo.push_back(KeyValue[2]);
		InitValueTwo.push_back(KeyValue[3]);
		InitValueTwo.push_back(KeyValue[6]);
		InitValueTwo.push_back(KeyValue[7]);

		std::vector<double> tmpParam;
		tmpParam.push_back(Param[0]);
		tmpParam.push_back(Param[1]);
		tmpParam.push_back(Param[2]);
		tmpParam.push_back(Param[3]);
		tmpParam.push_back(Param[4]);
		//tmpParam.push_back(Param[5]);

		std::vector<double*> *tmpVec = SuperChen::GetInstance()->CreateSequence(tmpParam, InitValueOne, Param[5]);
		KeyValue[0] = (*tmpVec)[0][(int)(Param[5] - 1)];
		KeyValue[1] = (*tmpVec)[1][(int)(Param[5] - 1)];
		KeyValue[4] = (*tmpVec)[2][(int)(Param[5] - 1)];
		KeyValue[5] = (*tmpVec)[3][(int)(Param[5] - 1)];
		FreeVec(tmpVec);

		tmpVec = SuperChen::GetInstance()->CreateSequence(tmpParam, InitValueTwo, Param[5]);
		KeyValue[2] = (*tmpVec)[0][(int)(Param[5] - 1)];
		KeyValue[3] = (*tmpVec)[1][(int)(Param[5] - 1)];
		KeyValue[6] = (*tmpVec)[2][(int)(Param[5] - 1)];
		KeyValue[7] = (*tmpVec)[3][(int)(Param[5] - 1)];
		FreeVec(tmpVec);

		for (size_t i = 0; i < KeyValue.size(); ++i)
		{
			KeyValue[i] = fabs(KeyValue[i] - static_cast<int>(KeyValue[i]));
		}

		InitValueOne.clear();
		InitValueTwo.clear();
		for (size_t i = 0; i < 4; ++i)
		{
			InitValueOne.push_back(KeyValue[i]);
		}
		for (size_t i = 4; i < KeyValue.size(); ++i)
		{
			InitValueTwo.push_back(KeyValue[i]);
		}
		tmpVec = SuperChen::GetInstance()->CreateSequence(tmpParam, InitValueOne, N);
		unsigned char *KnOne = Combinate(tmpVec, N, 8, Param[6]);

		FreeVec(tmpVec);

		tmpVec = SuperChen::GetInstance()->CreateSequence(tmpParam, InitValueTwo, N);
		unsigned char *KnTwo = Combinate(tmpVec, N, 8, Param[6]);
		FreeVec(tmpVec);

		size_t *R = UserGroup(KnOne, ceil(log2(rowImage)), rowImage, rowImage);
		size_t *S = UserGroup(KnTwo, ceil(log2(colImage)), colImage, colImage);

		
		for (size_t i = 0; i < rowImage; ++i)
		{
			for (size_t j = 0; j < colImage; ++j)
			{
				COLORREF tmp = pEnImage->GetPixel(i, j);
				pEnImage->SetPixel(i, j, pEnImage->GetPixel(R[i], S[j]));
				pEnImage->SetPixel(R[i], S[j], tmp);
			}
		}
		FreeArray(R);
		FreeArray(S);
		size_t *U = UserGroup(KnOne, GrayImageBits, GrayImageLevel - 1, N);
		FreeArray(KnOne);

		size_t *V = UserGroup(KnTwo, GrayImageBits, GrayImageLevel - 1, N);
		FreeArray(KnTwo);


		for (size_t i = 0; i < N; ++i)
		{
			if (U[i] == 0)
			{
				U[i] = 1;
			}
			else if ((U[i] & 1) == 0)
			{
				U[i] = U[i] - 1;
			}
		}

		
		size_t *Reverse = ReverseElement(GrayImageLevel + 1);
		unsigned char *ImageArray = ChaoticEncrypt::Image::GrayImageToSequence(pEnImage);
		
		
		ImageArray[0] = (U[0] * Reverse[ImageArray[0]] + V[0]) % GrayImageLevel;
		for (size_t i = 1; i < L; ++i)
		{
			ImageArray[i] = (U[i] * Reverse[ImageArray[i]] + V[i]) % GrayImageLevel;
			ImageArray[i] = ImageArray[i] ^ ImageArray[i - 1];
		}
		
		
		ImageArray[L - 1] = ((ImageArray[L - 1] + U[L]) % GrayImageLevel) ^ V[L];
		for (int i = L - 2; i != -1; --i)
		{
			ImageArray[i] = ((ImageArray[i] + U[2 * L - i - 1]) % GrayImageLevel) ^ V[2 * L - i - 1];
			ImageArray[i] = ImageArray[i] ^ ImageArray[i + 1];
		}
		
		
		FreeArray(U);
		FreeArray(V);
		FreeArray(Reverse);

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

std::unique_ptr<CImage> YangLiuAlgorithm::DnCode(CImage *pImage, \
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
		
		if ((Param.size() != 7) || (KeyValue.size() != 8))
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
		size_t N = 2 * L;

		std::vector<double> InitValueOne;
		InitValueOne.push_back(KeyValue[0]);
		InitValueOne.push_back(KeyValue[1]);
		InitValueOne.push_back(KeyValue[4]);
		InitValueOne.push_back(KeyValue[5]);

		std::vector<double> InitValueTwo;
		InitValueTwo.push_back(KeyValue[2]);
		InitValueTwo.push_back(KeyValue[3]);
		InitValueTwo.push_back(KeyValue[6]);
		InitValueTwo.push_back(KeyValue[7]);

		std::vector<double> tmpParam;
		tmpParam.push_back(Param[0]);
		tmpParam.push_back(Param[1]);
		tmpParam.push_back(Param[2]);
		tmpParam.push_back(Param[3]);
		tmpParam.push_back(Param[4]);

		std::vector<double*> *tmpVec = SuperChen::GetInstance()->CreateSequence(tmpParam, InitValueOne, Param[5]);
		KeyValue[0] = (*tmpVec)[0][(int)(Param[5] - 1)];
		KeyValue[1] = (*tmpVec)[1][(int)(Param[5] - 1)];
		KeyValue[4] = (*tmpVec)[2][(int)(Param[5] - 1)];
		KeyValue[5] = (*tmpVec)[3][(int)(Param[5] - 1)];
		FreeVec(tmpVec);

		tmpVec = SuperChen::GetInstance()->CreateSequence(tmpParam, InitValueTwo, Param[5]);
		KeyValue[2] = (*tmpVec)[0][(int)(Param[5] - 1)];
		KeyValue[3] = (*tmpVec)[1][(int)(Param[5] - 1)];
		KeyValue[6] = (*tmpVec)[2][(int)(Param[5] - 1)];
		KeyValue[7] = (*tmpVec)[3][(int)(Param[5] - 1)];
		FreeVec(tmpVec);

		for (size_t i = 0; i < KeyValue.size(); ++i)
		{
			KeyValue[i] = fabs(KeyValue[i] - static_cast<int>(KeyValue[i]));
		}

		InitValueOne.clear();
		InitValueTwo.clear();
		for (size_t i = 0; i < 4; ++i)
		{
			InitValueOne.push_back(KeyValue[i]);
		}
		for (size_t i = 4; i < KeyValue.size(); ++i)
		{
			InitValueTwo.push_back(KeyValue[i]);
		}
		tmpVec = SuperChen::GetInstance()->CreateSequence(tmpParam, InitValueOne, N);
		unsigned char *KnOne = Combinate(tmpVec, N, 8, Param[6]);
		FreeVec(tmpVec);

		tmpVec = SuperChen::GetInstance()->CreateSequence(tmpParam, InitValueTwo, N);
		unsigned char *KnTwo = Combinate(tmpVec, N, 8, Param[6]);
		FreeVec(tmpVec);

		size_t *U = UserGroup(KnOne, GrayImageBits, GrayImageLevel - 1, N);
		
		for (size_t i = 0; i < N; ++i)
		{
			if (U[i] == 0)
			{
				U[i] = 1;
			}
			else if ((U[i] & 1) == 0)
			{
				U[i] = U[i] - 1;
			}
		}

		size_t *V = UserGroup(KnTwo, GrayImageBits, GrayImageLevel - 1, N);
		
		unsigned char *ImageArray = ChaoticEncrypt::Image::GrayImageToSequence(pImage);
		
		
		for (size_t i = 0; i < L - 1; ++i)
		{
			ImageArray[i] = ImageArray[i] ^ ImageArray[i + 1];
			ImageArray[i] = ((ImageArray[i] ^ V[2 * L - i - 1]) + GrayImageLevel - U[2 * L - i - 1]) % GrayImageLevel;
		}
		ImageArray[L - 1] = ((ImageArray[L - 1] ^ V[L]) + GrayImageLevel - U[L]) % GrayImageLevel;
		
		
		size_t *Reverse = ReverseElement(GrayImageLevel + 1);
		size_t *ReReverse = new size_t[GrayImageLevel + 1];
		for (size_t i = 0; i < GrayImageLevel + 1; ++i)
		{
			ReReverse[Reverse[i]] = i;
		}
		FreeArray(Reverse);
		for (size_t i = L - 1; i != -1; --i)
		{
			if (i > 0)
			{
				ImageArray[i] = ImageArray[i] ^ ImageArray[i - 1];
			}
			
			int CurrentPixel = ImageArray[i] - V[i];
			if (CurrentPixel < 0)
			{
				CurrentPixel = CurrentPixel + GrayImageLevel;
			}
			size_t tmp = 0;
			for (size_t j = 0; j < GrayImageLevel + 1; ++j)
			{
				if (((U[i] * j) % GrayImageLevel) == CurrentPixel)
				{
					tmp = j;
					break;
				}
			}
			ImageArray[i] = ReReverse[tmp];
		}

		
		FreeArray(ReReverse);
		FreeArray(U);
		FreeArray(V);


		for (size_t i = 0; i < rowImage; ++i)
		{
			for (size_t j = 0; j < colImage; ++j)
			{
				size_t tmp = ImageArray[i * colImage + j];
				pDnImage->SetPixelRGB(i, j, tmp, tmp, tmp);
			}
		}

		FreeArray(ImageArray);

		size_t *R = UserGroup(KnOne, ceil(log2(rowImage)), rowImage, rowImage);
		FreeArray(KnOne);

		size_t *S = UserGroup(KnTwo, ceil(log2(colImage)), colImage, colImage);
		FreeArray(KnTwo);

		
		for (size_t i = rowImage - 1; i != -1; --i)
		{
			for (size_t j = colImage - 1; j != -1; --j)
			{
				COLORREF tmp = pDnImage->GetPixel(i, j);
				pDnImage->SetPixel(i, j, pDnImage->GetPixel(R[i], S[j]));
				pDnImage->SetPixel(R[i], S[j], tmp);
			}
		}
		FreeArray(R);
		FreeArray(S);
		
	}
	return DnImage;
}

unsigned char * YangLiuAlgorithm::Combinate(std::vector<double*> *& tmpVec,		\
	size_t N, size_t BitCount, size_t Precision)
{
	size_t len = N * tmpVec->size() * BitCount;
	unsigned char *K = new unsigned char[len];
	memset(K, '0', sizeof(unsigned char)* len);
	size_t Begin = 0;
	size_t M = pow(2, BitCount);
	size_t Base = pow(10, Precision);
	for (size_t i = 0; i < N; ++i)
	{
		size_t nSize = tmpVec->size();
		for (size_t j = 0; j < nSize; ++j)
		{
			double *& p = *(tmpVec->data() + j);
			unsigned char *tmp = ToBitStream(static_cast<size_t>(p[i] * Base) & (M - 1), BitCount);
			memcpy(K + Begin, tmp, sizeof(unsigned char)* BitCount);
			delete tmp;
			tmp = nullptr;
			Begin = Begin + BitCount;
		}
	}
	return K;
}

unsigned char * YangLiuAlgorithm::ToBitStream(size_t X, size_t N)
{
	unsigned char *K = new unsigned char[N];
	memset(K, '0', sizeof(unsigned char)* N);
	size_t i = 0;
	while (X > 0)
	{
		if ((X & 1) == 1)
		{
			K[i] = '1';
		}
		i = i + 1;
		X = X / 2;
	}
	return K;
}

size_t YangLiuAlgorithm::BitStreamTo(unsigned char *X, size_t N)
{
	size_t Result = 0;
	for (size_t i = N - 1; i != -1; --i)
	{
		if (X[i] == '0')
		{
			Result = 2 * Result;
		}
		else if (X[i] == '1')
		{
			Result = 2 * Result + 1;
		}
	}
	return Result;
}

size_t *YangLiuAlgorithm::UserGroup(unsigned char *Kn, \
	size_t Bits, size_t Limit, size_t length)
{
	size_t *Array = new size_t[length];
	memset(Array, 0, sizeof(size_t)* length);

	unsigned char *X = new unsigned char[Bits];
	memset(X, '0', sizeof(unsigned char)* Bits);

	for (size_t i = 0; i < length; ++i)
	{
		memcpy(X, Kn + i * Bits, sizeof(unsigned char)* Bits);
		Array[i] = BitStreamTo(X, Bits);
		Array[i] = Array[i] % Limit;
	}
	delete X;
	X = nullptr;
	return Array;
}

size_t * YangLiuAlgorithm::ReverseElement(size_t N)
{
	size_t *K = new size_t[N];
	memset(K, 0, sizeof(size_t)* N);
	K[0] = 0;
	K[1] = 1;
	for (size_t i = 2; i < N; ++i)
	{
		for (size_t j = 2; j < N; ++j)
		{
			if ((i*j) % N == 1)
			{
				K[i] = j;
				break;
			}
		}
	}
	return K;
}