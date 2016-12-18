#pragma once
#include <iostream>
#include <vector>
#include <memory>

class EncryptAlgorithm
{
public:
	EncryptAlgorithm();
	virtual ~EncryptAlgorithm();

	/*
	function: �����㷨
	
	Param: 
		Param:		����Կ����
		KeyValue:	��Կ

	return :	����ͼ��
	*/
	virtual std::unique_ptr<CImage> EnCode(CImage *pImage, std::vector<double> Param, std::vector<double> KeyValue) = 0;
	
	/*
	function: �����㷨

	Param:
		Param:		����Կ����
		KeyValue:	��Կ

	return :	����ͼ��
	*/
	virtual std::unique_ptr<CImage> DnCode(CImage *pImage, std::vector<double> Param, std::vector<double> KeyValue) = 0;
protected:

	// ����Կ����
	//std::vector<double> m_Param;

	// ��Կ
	//std::vector<double> m_KeyValue;
};

