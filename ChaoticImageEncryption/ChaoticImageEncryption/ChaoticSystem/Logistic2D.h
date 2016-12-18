#pragma once
#include "Chaotic.h"
class Logistic2D :
	public Chaotic
{
public:
	Logistic2D();
	virtual ~Logistic2D();
	//Param : 2.75 < r1 < 3.4 2.75 < r2 < 3.45, 
	//			0.15 < s1 < 0.21, 0.13 < s2 < 0.15
	// InitValue: 0 < x ,y < 1
	virtual vector<double*> * CreateSequence(vector<double> &Param, \
		vector<double> &InitValue, size_t N);

	virtual std::string GetName();

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static Logistic2D*& GetInstance();

	virtual size_t GetDimension();

private:
	static Logistic2D *m_pInstance;
};
