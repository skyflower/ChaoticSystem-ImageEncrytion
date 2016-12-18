#pragma once
#include "Chaotic.h"
class PWLCM :
	public Chaotic
{
public:
	PWLCM();
	virtual ~PWLCM();
public:

	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static PWLCM*& GetInstance();

	//  0 < x < 1
	//  0 < a < 1
	virtual vector<double*> * CreateSequence(vector<double> &Param, \
		vector<double> &InitValue, size_t N) override;

	virtual size_t GetDimension();
private:
	static PWLCM *m_pInstance;

	double func(double x, double p);
};

