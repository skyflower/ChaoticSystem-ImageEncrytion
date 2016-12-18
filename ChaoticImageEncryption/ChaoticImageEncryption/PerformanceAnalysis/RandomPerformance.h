

#pragma once
#include <iostream>
#include <unordered_map>
#include "..\ChaoticSystem\Chaotic.h"
#include "..\EncryptAlgorithm\EncryptAlgorithm.h"
#include <atlimage.h>
#include <tuple>


class PerformanceAnalysis
{
public:
	
	/*
	function:	构造算法分析对象

	Param:
		pImage:		明文图像
		algo:		被分析的加密算法
		Param:		加密算法所需的非密钥参数
		KeyValue:	加密算法的密钥

	return:
	*/
	explicit PerformanceAnalysis(CImage *pImage, EncryptAlgorithm *algo,	\
		std::vector<double> &Param, std::vector<double> &KeyValue);

	CImage *GetEnImage();

	CImage *GetCipherImage(const CImage* pImage);

	~PerformanceAnalysis();

	/*
	function:	分析各种混沌系统生成同等序列的速度

	Param:		混沌系统的容器

	return:
	*/
	static void ChaoticSystemSpeed(std::unordered_map<std::string, Chaotic*> *pChaoticSystem);

	static void AnalysisRandomPerformance(Chaotic *pChaotic,	\
		std::vector<double> Param, std::vector<double> InitValue, std::wstring FilePath);
	
	/*
	function:	分析算法的密钥敏感度

	Param:	

	return:	每个密钥参数做微小改变后对应的NPCR和UACI
	*/
	std::vector<std::vector<double>>* KeySensitivity_NPCR_UACI();


	/*
	function:	分析算法的密钥敏感度

	Param:

	
	return:	每个密钥参数做微小改变后的错误密钥对密文图像解密后的图像和图像直方图
	*/
	std::unordered_map<double, std::pair<CImage*, CImage*>>* KeySensitivity_Image_HistImage();
	
	/*
	function:	分析算法的明文敏感度
	
	Param:

	return:	对明文图像做微小改变后对应的NPCR和UACI,<纯色图像像素值，<NPCR,UACI>>
	*/
	std::unordered_map<size_t, std::vector<double>> * PlaintextSensitivity();

	//  选取的纯色图像加密后的密文图像信息熵<纯色图像像素值，密文图像信息熵>
	std::unordered_map<size_t, double> * PureEncryptedImageEntropy();

	// 对所有的纯色灰度图像后的密文图像信息上<纯色图像像素值, 密文图像信息熵>
	std::vector<double> * AllPureEncryptedImageEntropy();

	/*
	function:	对所有纯色灰度图像做明文灵敏度分析

	return:		
	*/
	std::tuple<CImage*, CImage*> AllGrayImagePlaintextSensitivity();


private:

	enum { MaxPlaintextSensitivity = 5};

	EncryptAlgorithm *m_pAlgo;			//	被分析的加密算法
	std::vector<double> m_Param;		//	加密算法的非密钥参数
	std::vector<double> m_KeyValue;		//	加密算法的密钥

	CImage *m_pImage;					//	明文图像

};