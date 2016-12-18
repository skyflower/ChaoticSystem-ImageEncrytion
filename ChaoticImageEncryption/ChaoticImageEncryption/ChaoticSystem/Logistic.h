#pragma once
#include "Chaotic.h"

class Logistic :
	public Chaotic
{
public:
	Logistic();
	virtual vector<double*> * Logistic::CreateSequence(std::vector<double> &Param, \
		std::vector<double> &InitValue, size_t N) override;
	virtual ~Logistic();

	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static Logistic*& GetInstance();

	virtual size_t GetDimension();

private:
	static Logistic *m_pInstance;
};

