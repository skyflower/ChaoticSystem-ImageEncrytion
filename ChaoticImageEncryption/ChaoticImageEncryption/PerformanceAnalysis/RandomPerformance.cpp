
#include <stdafx.h>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <set>
#include "..\math\math.h"
#include "..\ChaoticSystem\SuperChen.h"
#include <ctime>
#include <memory>
#include "..\PerformanceAnalysis\RandomPerformance.h"
#include "..\Image\Image.h"

using namespace std;


void PerformanceAnalysis::AnalysisRandomPerformance(Chaotic *pChaotic,	\
	std::vector<double> Param, std::vector<double> InitValue, std::wstring FilePath)
{
	const size_t N = 10000000;
	const size_t M = 10000;
	const size_t BitCount = N * sizeof(char)* 8;
	unsigned char * Array = new unsigned char[N];
	memset(Array, 0, sizeof(unsigned char)* N);
	
	size_t Begin = 0;
	
	while (Begin < N)
	{
		std::vector<double*> *tmp = pChaotic->CreateSequence(Param, InitValue, M);
		memset(Array, 0, sizeof(unsigned char)* N);
		if ((tmp == nullptr) || (tmp->empty()))
		{
			FreeVec(tmp);
			break;
		}
		for (size_t j = 0; j < tmp->size(); ++j)
		{
			double *& tmpArray = *(tmp->data() + j);
			for (size_t i = 0; i < M && Begin < N; ++i)
			{
				size_t k = static_cast<size_t>(tmpArray[i] * 1000000);
				k = k % 256;
				
				Array[Begin++] = (k > 128 ? 49 : 48);	//(tmpArray[i] > 0.5 ? 49 : 48 );
			}
			FreeArray(tmpArray);
		}
		FreeVec(tmp);
		if (Begin == N)
		{
			break;
		}
	}
	FILE *fp = nullptr;

	errno_t OpenFlag = _wfopen_s(&fp, FilePath.c_str(), L"wb");

	if (!OpenFlag)
	{
		if (fwrite(Array, sizeof(unsigned char), N, fp) != N)
		{
			//cout << "Saved TXT File Failed" << endl;
		}
		fflush(fp);
		fclose(fp);
	}
	FreeArray(Array);
}


void PerformanceAnalysis::ChaoticSystemSpeed(std::unordered_map<std::string, Chaotic*> *pChaoticSystem)
{
	const size_t N = 10000000;
	for (std::unordered_map<std::string, Chaotic*>::const_iterator iter = pChaoticSystem->cbegin();	\
		iter != pChaoticSystem->cend(); ++iter)
	{
		Chaotic *p = iter->second;
		clock_t StartTime = clock();
		std::vector<double*> *SeqVec = p->CreateSequence(p->GetParam(), p->GetInitValue(), N / p->GetDimension());
		clock_t EndTime = clock();
		
		TRACE2(" %S Generate Time = %f\n\n", p->GetName().c_str(), (static_cast<double>(EndTime - StartTime)) / CLOCKS_PER_SEC);
		
		FreeVec(SeqVec);
	}
}


PerformanceAnalysis::PerformanceAnalysis(CImage *pImage, EncryptAlgorithm *algo,	\
	std::vector<double> &Param, std::vector<double> &KeyValue) : m_pAlgo(algo), m_pImage(pImage)
{
	m_Param = Param;
	m_KeyValue = KeyValue;
}

PerformanceAnalysis::~PerformanceAnalysis()
{
	
}

CImage *PerformanceAnalysis::GetEnImage()
{
	std::unique_ptr<CImage> pImage = m_pAlgo->EnCode(m_pImage, m_Param, m_KeyValue);
	return pImage.release();
}

CImage *PerformanceAnalysis::GetCipherImage(const CImage* pImage)
{
	std::unique_ptr<CImage> tmpImage = m_pAlgo->EnCode(const_cast<CImage*>(pImage), m_Param, m_KeyValue);
	return tmpImage.release();
}

std::vector<std::vector<double>>* PerformanceAnalysis::KeySensitivity_NPCR_UACI()
{
	std::vector<std::vector<double>>* Result = nullptr;
	size_t Length = m_KeyValue.size();
	std::unique_ptr<CImage> EnImage = m_pAlgo->EnCode(m_pImage, m_Param, m_KeyValue);

	for (size_t i = 0; i < Length; ++i)
	{
		std::vector<double> _KeyValue = m_KeyValue;
		if (fabs(round(_KeyValue[i]) - _KeyValue[i]) < EPS)
		{
			_KeyValue[i] += 1;
		}
		else
		{
			_KeyValue[i] += Delta;
		}
		std::unique_ptr<CImage> EnTwo = m_pAlgo->EnCode(m_pImage, m_Param, _KeyValue);
		std::vector<double> && NPCR_UACI = ChaoticEncrypt::Image::NPCR_UACI(EnImage.get(), EnTwo.get());
		Result->push_back(NPCR_UACI);
	}
	return Result;
}

std::unordered_map<double, std::pair<CImage*, CImage*>>* PerformanceAnalysis::KeySensitivity_Image_HistImage()
{
	std::unordered_map<double, std::pair<CImage*, CImage*>> * KeySensitivity = nullptr;

	//std::vector<std::vector<double>> Result;
	size_t Length = m_KeyValue.size();
	std::unique_ptr<CImage> EnImage = m_pAlgo->EnCode(m_pImage, m_Param, m_KeyValue);

	for (size_t i = 0; i < Length; ++i)
	{
		std::vector<double> _KeyValue = m_KeyValue;
		double tmp = _KeyValue[i];
		if (fabs(round(_KeyValue[i]) - _KeyValue[i]) < EPS)
		{
			_KeyValue[i] += 1;
		}
		else
		{
			_KeyValue[i] += Delta;
		}
		std::unique_ptr<CImage> DnImage = m_pAlgo->DnCode(EnImage.get(), m_Param, _KeyValue);
		CImage* DnImageHist = ChaoticEncrypt::Image::HistFromImage(DnImage.get());
		if (KeySensitivity == nullptr)
		{
			KeySensitivity = new std::unordered_map<double, std::pair<CImage*, CImage*>>;
		}
		KeySensitivity->insert(std::make_pair(tmp, std::make_pair(DnImage.release(), DnImageHist)));
	}
	return KeySensitivity;
}


std::unordered_map<size_t, std::vector<double>>* PerformanceAnalysis::PlaintextSensitivity()
{
	std::unordered_map<size_t, std::vector<double>>* Result = new unordered_map<size_t, std::vector<double>>;

	size_t PlaintextCount = 0;
	std::set<unsigned char> PlaintextSet;
	PlaintextSet.insert(255);
	PlaintextSet.insert(0);
	while (PlaintextCount < MaxPlaintextSensitivity)
	{
		size_t k = rand() % GrayImageLevel;
		if (PlaintextSet.find(k) == PlaintextSet.end())
		{
			PlaintextSet.insert(k);
		}
	}
	
	CImage *pImage = new CImage;
	pImage->Create(GrayImageLevel, GrayImageLevel, GrayImageBits);
	ChaoticEncrypt::Image::InitGrayImageColorTable(pImage);

	for (std::set<unsigned char>::const_iterator iter = PlaintextSet.begin();	\
		iter != PlaintextSet.end(); ++iter)
	{
		for (size_t i = 0; i < GrayImageLevel; ++i)
		{
			for (size_t j = 0; j < GrayImageLevel; ++j)
			{
				pImage->SetPixelRGB(i, j, *iter, *iter, *iter);
			}
		}
		std::unique_ptr<CImage> EnFirst = m_pAlgo->EnCode(pImage, m_Param, m_KeyValue);
		size_t cx = rand() % GrayImageLevel;
		size_t cy = rand() % GrayImageLevel;
		size_t Pixel = pImage->GetPixel(cx, cy);
		Pixel = Pixel % GrayImageLevel;
		unsigned char tmp = 1 << (rand() % (GrayImageBits - 1));
		if ((Pixel & tmp) != 0)
		{
			Pixel = (~tmp) & Pixel;
		}
		else
		{
			Pixel = tmp ^ Pixel;
		}
		pImage->SetPixelRGB(cx, cy, Pixel, Pixel, Pixel);
		std::unique_ptr<CImage> EnSecond = m_pAlgo->EnCode(pImage, m_Param, m_KeyValue);
		std::vector<double> SensitivityResult = ChaoticEncrypt::Image::NPCR_UACI(EnFirst.release(), EnSecond.release());
		Result->insert(std::make_pair(*iter, SensitivityResult));
		
	}
	return Result;
}

std::unordered_map<size_t, double> * PerformanceAnalysis::PureEncryptedImageEntropy()
{
	std::unordered_map<size_t, double> *Result = new std::unordered_map<size_t, double>;

	size_t PlaintextCount = 0;
	std::set<unsigned char> PlaintextSet;
	while (PlaintextCount < MaxPlaintextSensitivity)
	{
		size_t tmp = rand() % GrayImageLevel;
		if (PlaintextSet.find(tmp) == PlaintextSet.end())
		{
			PlaintextSet.insert(tmp);
		}
		++PlaintextCount;
	}

	CImage *pImage = new CImage;
	pImage->Create(GrayImageLevel, GrayImageLevel, GrayImageBits);
	ChaoticEncrypt::Image::InitGrayImageColorTable(pImage);
	for (std::set<unsigned char>::const_iterator iter = PlaintextSet.begin();	\
		iter != PlaintextSet.end(); ++iter)
	{
		for (size_t i = 0; i < GrayImageLevel; ++i)
		{
			for (size_t j = 0; j < GrayImageLevel; ++j)
			{
				pImage->SetPixelRGB(i, j, *iter, *iter, *iter);
			}
		}
		std::unique_ptr<CImage> EnImage = m_pAlgo->EnCode(pImage, m_Param, m_KeyValue);
		double EnImageEntropy = ChaoticEncrypt::Image::GrayImageEntropy(EnImage.get());
		Result->insert(std::make_pair(*iter, EnImageEntropy));
	}
	delete pImage;
	return Result;
}

std::tuple<CImage*, CImage*> PerformanceAnalysis::AllGrayImagePlaintextSensitivity()
{
	CImage *PureImage = new CImage;
	PureImage->Create(GrayImageLevel, GrayImageLevel, GrayImageBits);
	ChaoticEncrypt::Image::InitGrayImageColorTable(PureImage);

	CImage *ChangeImage = new CImage;
	ChangeImage->Create(GrayImageLevel, GrayImageLevel, GrayImageBits);
	std::vector<double> PlainText(2 * GrayImageLevel);
	
	for (size_t i = 0; i < GrayImageLevel; ++i)
	{
		ChaoticEncrypt::Image::InitGrayImageToPureImage(PureImage, i);
		std::unique_ptr<CImage> EnOne = m_pAlgo->EnCode(PureImage, m_Param, m_KeyValue);
		CImage *pEnOne = EnOne.release();
		double tmpNPCR = 0.00001;
		double tmpUACI = 0.00001;
		clock_t tmpStartTime = clock_t();

		for (size_t j = 0; j < GrayImageBits; ++j)
		{
			ChaoticEncrypt::Image::InitGrayImageToPureImage(ChangeImage, i);
			size_t tmpX = (static_cast<size_t>(rand())) % GrayImageLevel;
			size_t tmpY = (static_cast<size_t>(rand())) % GrayImageLevel;
			size_t tmp = ChangeImage->GetPixel(tmpX, tmpY) % GrayImageLevel;
			tmp = (tmp + 1) % GrayImageLevel;
			ChangeImage->SetPixelRGB(tmpX, tmpY, tmp, tmp, tmp);
			std::unique_ptr<CImage> EnTwo = m_pAlgo->EnCode(ChangeImage, m_Param, m_KeyValue);
			CImage *pEnTwo = EnTwo.release();
			std::vector<double> &&Result = ChaoticEncrypt::Image::NPCR_UACI(pEnOne, pEnTwo);
			tmpNPCR += Result[0];
			tmpUACI += Result[1];
			delete pEnTwo;
			pEnTwo = nullptr;
		}
		
		PlainText[2 * i] = tmpNPCR / GrayImageBits;
		PlainText[2 * i + 1] = tmpUACI / GrayImageBits;
		delete pEnOne;
		pEnOne = nullptr;
	}
	
	delete PureImage;
	PureImage = nullptr;

	delete ChangeImage;
	ChangeImage = nullptr;

	CImage *NPCR_Image = nullptr;
	
	CImage *UACI_Image = nullptr;
	
	double tmpMax = 0;
	double tmpMin = 1;
	for (size_t i = 0; i < 2 * GrayImageLevel; i = i + 2)
	{
		tmpMax = tmpMax > PlainText[i] ? tmpMax : PlainText[i];
		tmpMin = tmpMin > PlainText[i] ? PlainText[i] : tmpMin;
	}

	std::function<void(CImage *, size_t, size_t)> ImageSetPixel =		\
		[](CImage *pImage, size_t i, size_t j)
	{
		if (pImage && (pImage->GetWidth() > i) && (pImage->GetHeight() > j) )
		{
			pImage->SetPixelRGB(i, j, 0, 0, 255);
			if (i > 0)
			{
				pImage->SetPixelRGB(i - 1, j, 0, 0, 255);
			}
			if (i < pImage->GetWidth() - 1)
			{
				pImage->SetPixelRGB(i + 1, j, 0, 0, 255);
			}
		}
	};
	const double NPCRMax = 0.999;
	const double NPCRMin = 0.99;
	if ((tmpMax < NPCRMax) && (tmpMin > NPCRMin))
	{
		NPCR_Image = new CImage;
		NPCR_Image->Create(GrayImageLevel, GrayImageLevel, ColorImageBits);
		ChaoticEncrypt::Image::InitColorImage(NPCR_Image, 0, 0, 255);
		for (size_t i = 0; i < 2 * GrayImageLevel; i = i + 2)
		{
			int tmp = (GrayImageLevel - 1) * (PlainText[i] - NPCRMin) / (NPCRMax - NPCRMin);
			if (tmp>0 && tmp < GrayImageLevel)
			{
				ImageSetPixel(NPCR_Image, i / 2, tmp);
			}
		}
	}

	tmpMax = 0;
	tmpMin = 1;
	for (size_t i = 1; i < 2 * GrayImageLevel; i = i + 2)
	{
		tmpMax = tmpMax > PlainText[i] ? tmpMax : PlainText[i];
		tmpMin = tmpMin > PlainText[i] ? PlainText[i] : tmpMin;
	}

	const double UACIMax = 0.339;
	const double UACIMin = 0.33;

	if ((tmpMax < UACIMax) && (tmpMin > UACIMin))
	{
		UACI_Image = new CImage;
		UACI_Image->Create(GrayImageLevel, GrayImageLevel, ColorImageBits);
		ChaoticEncrypt::Image::InitColorImage(UACI_Image, 0, 0, 255);
		for (size_t i = 1; i < 2 * GrayImageLevel; i = i + 2)
		{
			int tmp = (GrayImageLevel - 1) * (PlainText[i] - UACIMin) / (UACIMax - UACIMin);
			if (tmp>0 && tmp < GrayImageLevel)
			{
				ImageSetPixel(UACI_Image, i / 2, tmp);
			}
		}
	}
	return std::make_tuple(NPCR_Image, UACI_Image);
}

std::vector<double> * PerformanceAnalysis::AllPureEncryptedImageEntropy()
{
	std::vector<double> *Result = new std::vector<double>(GrayImageLevel);
	CImage *pImage = new CImage;
	pImage->Create(GrayImageLevel, GrayImageLevel, GrayImageBits);
	ChaoticEncrypt::Image::InitGrayImageColorTable(pImage);
	for (size_t nPixel = 0; nPixel < GrayImageLevel; ++nPixel)
	{
		for (size_t i = 0; i < GrayImageLevel; ++i)
		{
			for (size_t j = 0; j < GrayImageLevel; ++j)
			{
				pImage->SetPixelRGB(i, j, nPixel, nPixel, nPixel);
			}
		}
		std::unique_ptr<CImage> EnImage = m_pAlgo->EnCode(pImage, m_Param, m_KeyValue);
		double EnImageEntropy = ChaoticEncrypt::Image::GrayImageEntropy(EnImage.get());
		*(Result->data() + nPixel) = EnImageEntropy;
		//Result->insert(std::make_pair(nPixel, EnImageEntropy));
	}
	delete pImage;
	pImage = nullptr;
	return Result;
}