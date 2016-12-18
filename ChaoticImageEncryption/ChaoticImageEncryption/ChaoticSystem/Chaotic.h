#pragma once
#include <iostream>
#include <vector>
#include "math.h"
#include <functional>


using namespace std;


class Chaotic
{
public:
	Chaotic();
	virtual vector<double*> * CreateSequence(vector<double> &Param,		\
		vector<double> &InitValue, size_t N) = 0;

	virtual std::string GetName() = 0;

	virtual std::vector<double> & GetParam() = 0;
	virtual std::vector<double> & GetInitValue() = 0;

	inline bool ValidRange(double x, double Left, double Right);

	bool CheckValid(double x);

	virtual ~Chaotic();

	static Chaotic *& GetInstance();

	virtual size_t GetDimension() = 0;

protected:

	std::vector<double> m_Param;
	std::vector<double> m_InitValue;

private:
	
	static Chaotic *m_pInstance;
};

