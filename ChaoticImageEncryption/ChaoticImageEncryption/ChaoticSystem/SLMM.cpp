#include "stdafx.h"
#include "SLMM.h"
#include "..\math\math.h"


SLMM *SLMM::m_pInstance = nullptr;
SLMM::SLMM()
{
}


SLMM::~SLMM()
{
}


vector<double*> * SLMM::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	std::vector< double * > * p = nullptr;
	if (Param.empty() || InitValue.empty())
	{
		return nullptr;
	}
	double & a = Param[0];
	double & b = Param[1];
	double & x = InitValue[0];
	double & y = InitValue[1];

	if (!ValidRange(a, 0, 3) || !ValidRange(b, 0, 1) || !CheckValid(x) || !CheckValid(y) || N < 1)
	{
		return p;
	}
	p = new std::vector< double *>;
	double * A = new double[N];
	memset(A, 0, sizeof(double)* N);
	
	double * B = new double[N];
	memset(B, 0, sizeof(double)* N);
	
	A[0] = x;
	B[0] = y;
	//const double pi = 3.1415926;
	for (size_t i = 1; i < N; ++i)
	{
		A[i] = a * (sin(PI * B[i - 1]) + b) * A[i - 1] * (1 - A[i - 1]);
		B[i] = a * (sin(PI * A[i]) + b) * B[i - 1] * (1 - B[i - 1]);
	}
	p->push_back(A);
	p->push_back(B);
	return p;
}

std::string SLMM::GetName()
{
	return "SLMM";
}

std::vector<double> & SLMM::GetParam()
{
	Chaotic::m_Param.push_back(2.9999);
	Chaotic::m_Param.push_back(0.8799);
	return Chaotic::m_Param;
}

std::vector<double> & SLMM::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	Chaotic::m_InitValue.push_back(0.879);
	return Chaotic::m_InitValue;
}

SLMM*& SLMM::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SLMM;
	}
	return m_pInstance;
}

size_t SLMM::GetDimension()
{
	return 2;
}