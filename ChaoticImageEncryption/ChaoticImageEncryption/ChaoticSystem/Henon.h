#pragma once
#include "Chaotic.h"
class Henon : public Chaotic
{
public:
	Henon();
	virtual ~Henon();
	virtual std::string GetName() override;

	virtual std::vector<double> & GetParam() override;
	virtual std::vector<double> & GetInitValue() override;

	static Henon*& GetInstance();

	//  0 < x,y < 1
	//  0 < a < 1.4  0.2 < b <= 0.314
	virtual vector<double*> * CreateSequence(vector<double> &Param,		\
		vector<double> &InitValue, size_t N) override;

	virtual size_t GetDimension();
private:
	static Henon *m_pInstance;
	
};

