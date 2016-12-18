#pragma once
#include "EncryptAlgorithm.h"
class testAlgorithm :
	public EncryptAlgorithm
{
public:
	testAlgorithm();
	virtual ~testAlgorithm();

	virtual std::unique_ptr<CImage> EnCode(CImage *pImage,		\
		std::vector<double> Param, std::vector<double> KeyValue) override;

	virtual std::unique_ptr<CImage> DnCode(CImage *pImage,	\
		std::vector<double> Param, std::vector<double> KeyValue) override;
};

