#include "stdafx.h"
#include "PWLCM.h"


PWLCM *PWLCM::m_pInstance = nullptr;

PWLCM::PWLCM()
{
}


PWLCM::~PWLCM()
{
}

std::string PWLCM::GetName()
{
	return "PWLCM";
}

std::vector<double> & PWLCM::GetParam()
{
	Chaotic::m_Param.push_back(0.5);
	return Chaotic::m_Param;
}

std::vector<double> & PWLCM::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	return Chaotic::m_InitValue;
}


PWLCM*& PWLCM::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new PWLCM;
	}
	return m_pInstance;
}

//  0 < x < 1
//  0 < a < 1
vector<double*> * PWLCM::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	if (Param.empty() || InitValue.empty())
	{
		return nullptr;
	}
	double & a = Param[0];
	
	double & x = InitValue[0];
	
	std::vector< double *> * p = nullptr;
	
	if (!CheckValid(x) || N < 1 || !ValidRange(a, 0, 1))
	{
		return p;
	}
	p = new std::vector< double *>;
	double *A = new double[N];
	memset(A, 0, sizeof(double)* N);
	x = func(x, a);
	A[0] = x;
	for (size_t i = 1; i < N; ++i)
	{
		A[i] = func(A[i - 1], a);
	}
	p->push_back(A);
	return p;
}

size_t PWLCM::GetDimension()
{
	return 1;
}

double PWLCM::func(double x, double p)
{
	if (x > 0 && x < p)
	{
		return x / p;
	}
	else if (x >= p&&x < 0.5)
	{
		return (x - p) / (0.5 - p);
	}
	else if (x >= 0.5 && x < 1)
	{
		return func(1 - x, p);
	}
	return 0;
}
