#include "stdafx.h"
#include "Henon.h"


Henon *Henon::m_pInstance = nullptr;

Henon::Henon()
{
}


Henon::~Henon()
{
}

std::vector<double*> *Henon::CreateSequence(std::vector<double> &Param, \
	std::vector<double> &InitValue, size_t N)
{
	if (Param.empty() || InitValue.empty())
	{
		return nullptr;
	}
	double & a = Param[0];
	double & b = Param[1];
	double & x = InitValue[0];
	double & y = InitValue[1];
	std::vector< double *> * p = nullptr;
	double TestResult = 1 - a * x * x + b;
	if (TestResult <= 0 || TestResult >= 1 || !CheckValid(x) || !CheckValid(y) || N < 1 \
		|| !ValidRange(a, 0, 1.4) || !ValidRange(b, 0.2, 0.314))
	{
		return p;
	}
	p = new std::vector< double *>;
	double *A = new double[N];
	memset(A, 0, sizeof(double)* N);
	
	double *B = new double[N];
	memset(B, 0, sizeof(double)* N);
	
	A[0] = x;
	B[0] = y;
	for (size_t i = 1; i < N; ++i)
	{
		A[i] = 1 - a * A[i - 1] * A[i - 1] + B[i - 1];
		B[i] = b * A[i - 1];
	}
	p->push_back(A);
	p->push_back(B);
	return p;
}

std::string Henon::GetName()
{
	return "Henon";
}

std::vector<double> & Henon::GetParam()
{
	Chaotic::m_Param.push_back(1);
	Chaotic::m_Param.push_back(0.3);
	return Chaotic::m_Param;
}
std::vector<double> & Henon::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.879);
	Chaotic::m_InitValue.push_back(0.1234);
	return Chaotic::m_InitValue;
}

Henon *&Henon::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Henon;
	}
	return m_pInstance;
}

size_t Henon::GetDimension()
{
	return 2;
}