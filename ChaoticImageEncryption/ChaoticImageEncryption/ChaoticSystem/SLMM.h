#pragma once
#include "Chaotic.h"
class SLMM :
	public Chaotic
{
public:
	SLMM();
	virtual ~SLMM();
	virtual vector<double*> * CreateSequence(vector<double> &Param, \
		vector<double> &InitValue, size_t N) override;

	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static SLMM*& GetInstance();

	virtual size_t GetDimension();

private:
	static SLMM *m_pInstance;
};

