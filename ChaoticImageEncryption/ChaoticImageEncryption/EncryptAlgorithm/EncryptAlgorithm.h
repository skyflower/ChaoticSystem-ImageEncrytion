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
	function: 加密算法
	
	Param: 
		Param:		非密钥参数
		KeyValue:	密钥

	return :	加密图像
	*/
	virtual std::unique_ptr<CImage> EnCode(CImage *pImage, std::vector<double> Param, std::vector<double> KeyValue) = 0;
	
	/*
	function: 解密算法

	Param:
		Param:		非密钥参数
		KeyValue:	密钥

	return :	解密图像
	*/
	virtual std::unique_ptr<CImage> DnCode(CImage *pImage, std::vector<double> Param, std::vector<double> KeyValue) = 0;
protected:

	// 非密钥参数
	//std::vector<double> m_Param;

	// 密钥
	//std::vector<double> m_KeyValue;
};

