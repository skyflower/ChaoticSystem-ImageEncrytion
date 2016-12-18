#pragma once
#include "Chaotic.h"
class TentSine :
	public Chaotic
{
public:
	TentSine();
	virtual ~TentSine();
	virtual vector<double*> * CreateSequence(vector<double> &Param, \
		vector<double> &InitValue, size_t N) override;

	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static TentSine*& GetInstance();

	virtual size_t GetDimension();

private:
	static TentSine *m_pInstance;
};

