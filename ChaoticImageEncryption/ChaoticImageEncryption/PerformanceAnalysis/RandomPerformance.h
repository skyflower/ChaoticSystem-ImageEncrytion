

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
	function:	�����㷨��������

	Param:
		pImage:		����ͼ��
		algo:		�������ļ����㷨
		Param:		�����㷨����ķ���Կ����
		KeyValue:	�����㷨����Կ

	return:
	*/
	explicit PerformanceAnalysis(CImage *pImage, EncryptAlgorithm *algo,	\
		std::vector<double> &Param, std::vector<double> &KeyValue);

	CImage *GetEnImage();

	CImage *GetCipherImage(const CImage* pImage);

	~PerformanceAnalysis();

	/*
	function:	�������ֻ���ϵͳ����ͬ�����е��ٶ�

	Param:		����ϵͳ������

	return:
	*/
	static void ChaoticSystemSpeed(std::unordered_map<std::string, Chaotic*> *pChaoticSystem);

	static void AnalysisRandomPerformance(Chaotic *pChaotic,	\
		std::vector<double> Param, std::vector<double> InitValue, std::wstring FilePath);
	
	/*
	function:	�����㷨����Կ���ж�

	Param:	

	return:	ÿ����Կ������΢С�ı���Ӧ��NPCR��UACI
	*/
	std::vector<std::vector<double>>* KeySensitivity_NPCR_UACI();


	/*
	function:	�����㷨����Կ���ж�

	Param:

	
	return:	ÿ����Կ������΢С�ı��Ĵ�����Կ������ͼ����ܺ��ͼ���ͼ��ֱ��ͼ
	*/
	std::unordered_map<double, std::pair<CImage*, CImage*>>* KeySensitivity_Image_HistImage();
	
	/*
	function:	�����㷨���������ж�
	
	Param:

	return:	������ͼ����΢С�ı���Ӧ��NPCR��UACI,<��ɫͼ������ֵ��<NPCR,UACI>>
	*/
	std::unordered_map<size_t, std::vector<double>> * PlaintextSensitivity();

	//  ѡȡ�Ĵ�ɫͼ����ܺ������ͼ����Ϣ��<��ɫͼ������ֵ������ͼ����Ϣ��>
	std::unordered_map<size_t, double> * PureEncryptedImageEntropy();

	// �����еĴ�ɫ�Ҷ�ͼ��������ͼ����Ϣ��<��ɫͼ������ֵ, ����ͼ����Ϣ��>
	std::vector<double> * AllPureEncryptedImageEntropy();

	/*
	function:	�����д�ɫ�Ҷ�ͼ�������������ȷ���

	return:		
	*/
	std::tuple<CImage*, CImage*> AllGrayImagePlaintextSensitivity();


private:

	enum { MaxPlaintextSensitivity = 5};

	EncryptAlgorithm *m_pAlgo;			//	�������ļ����㷨
	std::vector<double> m_Param;		//	�����㷨�ķ���Կ����
	std::vector<double> m_KeyValue;		//	�����㷨����Կ

	CImage *m_pImage;					//	����ͼ��

};