#pragma once
#include "Chaotic.h"
class LogisticSine :
	public Chaotic
{
public:
	LogisticSine();
	virtual ~LogisticSine();

	virtual vector<double*> * CreateSequence(vector<double> &Param, \
		vector<double> &InitValue, size_t N) override;

	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static LogisticSine*& GetInstance();

	virtual size_t GetDimension();

private:
	static LogisticSine *m_pInstance;
};

