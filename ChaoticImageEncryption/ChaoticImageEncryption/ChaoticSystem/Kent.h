#pragma once
#include "Chaotic.h"
class Kent : public Chaotic
{
public:
	Kent();
	virtual ~Kent();

	virtual std::string GetName() override;

	virtual vector<double*> * CreateSequence(vector<double> &Param,		\
		vector<double> &InitValue, size_t N) override;


	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static Kent*& GetInstance();

	virtual size_t GetDimension();

private:
	static Kent *m_pInstance;

};

