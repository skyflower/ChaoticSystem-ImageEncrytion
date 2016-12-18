#pragma once
#include "Chaotic.h"
class Sine :
	public Chaotic
{
public:
	Sine();
	virtual ~Sine();

	virtual vector<double*> * CreateSequence(vector<double> &Param, \
		vector<double> &InitValue, size_t N) override;

	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static Sine*& GetInstance();

	virtual size_t GetDimension();

private:
	static Sine *m_pInstance;
};

