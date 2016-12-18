#pragma once
#include "Chaotic.h"
class Peter :
	public Chaotic
{
public:
	Peter();
	virtual ~Peter();
	virtual vector<double*> * CreateSequence(vector<double> &Param, \
		vector<double> &InitValue, size_t N) override;

	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static Peter*& GetInstance();

	virtual size_t GetDimension();
private:
	static Peter *m_pInstance;
};

