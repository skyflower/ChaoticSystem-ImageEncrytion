/*

卢庆硕士学位毕业论文第四章算法

*/

#pragma once
#include "EncryptAlgorithm.h"
#include <iostream>
#include <vector>
#include <memory>
#include "..\ChaoticSystem\Henon.h"
#include "..\ChaoticSystem\SuperChen.h"

class LqGraduate :public EncryptAlgorithm
{
public:
	LqGraduate();
	virtual ~LqGraduate();


	/*
	Param:

	*/
	virtual std::unique_ptr<CImage> EnCode(CImage *pImage, \
		std::vector<double> Param, std::vector<double> KeyValue) override;

	virtual std::unique_ptr<CImage> DnCode(CImage *pImage, \
		std::vector<double> Param, std::vector<double> KeyValue) override;

private:
	unsigned char* GenerateChaticSeq(std::vector<double> Param, std::vector<double> InitValue);
};

