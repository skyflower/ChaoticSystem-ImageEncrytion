#pragma once

#include <iostream>
#include <vector>
#include "Chaotic.h"

using namespace std;

class OCML : public Chaotic
{
public:
	virtual vector<double*> * CreateSequence(std::vector<double> &Param,	\
		std::vector<double> &InitValue, size_t N);
	OCML();
	virtual ~OCML();
	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static OCML*& GetInstance();

private:
	static OCML *m_pInstance;

};

