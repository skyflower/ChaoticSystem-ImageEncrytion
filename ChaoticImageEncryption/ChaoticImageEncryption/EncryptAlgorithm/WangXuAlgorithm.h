/*

A novel image encryption scheme based on Brownian
motion and PWLCM chaotic system
XingyuanWang · Dahai Xu

Nonlinear Dyn (2014) 75:345–353
DOI 10.1007/s11071-013-1070-x

本算法是上述论文的改进算法

*/

#pragma once
#include "EncryptAlgorithm.h"
#include <iostream>
#include <vector>
#include <memory>

class WangXuAlgorithm :public EncryptAlgorithm
{
public:
	WangXuAlgorithm();
	virtual ~WangXuAlgorithm();


	/*
	Param:

	*/
	virtual std::unique_ptr<CImage> EnCode(CImage *pImage, \
		std::vector<double> Param, std::vector<double> KeyValue) override;

	virtual std::unique_ptr<CImage> DnCode(CImage *pImage, \
		std::vector<double> Param, std::vector<double> KeyValue) override;
};

