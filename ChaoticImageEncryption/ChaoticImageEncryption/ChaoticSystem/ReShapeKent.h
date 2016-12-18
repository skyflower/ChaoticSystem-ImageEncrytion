#pragma once
#include "Chaotic.h"
class ReShapeKent :
	public Chaotic
{
public:
	ReShapeKent();
	virtual ~ReShapeKent();

	virtual vector<double*> * CreateSequence(vector<double> &Param, \
		vector<double> &InitValue, size_t N) override;

	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static ReShapeKent*& GetInstance();

	virtual size_t GetDimension();

private:
	static ReShapeKent *m_pInstance;
};

