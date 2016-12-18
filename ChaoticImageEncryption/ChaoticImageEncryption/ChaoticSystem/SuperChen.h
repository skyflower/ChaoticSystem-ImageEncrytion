#pragma once
#include "Chaotic.h"
class SuperChen :
	public Chaotic
{
public:
	SuperChen();
	virtual ~SuperChen();
	virtual vector<double*> * CreateSequence(vector<double> &Param, \
		vector<double> &InitValue, size_t N);

	virtual std::string GetName();

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static SuperChen*& GetInstance();

	virtual size_t GetDimension();

private:
	static SuperChen *m_pInstance;
};

