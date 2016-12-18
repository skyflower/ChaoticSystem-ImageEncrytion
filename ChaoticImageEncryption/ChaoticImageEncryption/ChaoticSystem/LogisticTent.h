#pragma once
#include "Chaotic.h"
class LogisticTent :
	public Chaotic
{
public:
	LogisticTent();
	virtual ~LogisticTent();
	virtual vector<double*> * CreateSequence(vector<double> &Param, \
		vector<double> &InitValue, size_t N) override;

	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static LogisticTent*& GetInstance();

	size_t GetDimension();

private:
	static LogisticTent *m_pInstance;
};

