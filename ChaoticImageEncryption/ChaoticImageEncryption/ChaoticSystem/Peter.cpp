#include "stdafx.h"
#include "Peter.h"

Peter *Peter::m_pInstance = nullptr;
Peter::Peter()
{
}


Peter::~Peter()
{
}

vector<double*> * Peter::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	if (Param.empty() || InitValue.empty())
	{
		return nullptr;
	}
	std::vector< double * > * p = nullptr;
	double & a = Param[0];
	double & b = Param[1];
	double & c = Param[2];
	double & d = Param[3];
	double & x = InitValue[0];
	double & y = InitValue[1];
	if (N < 1 || !ValidRange(a, 0, 1) || !ValidRange(b, 0, 1) || \
		!ValidRange(c, 0, 1) || !ValidRange(d, 0, 1))
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
		A[i] = sin(a * B[i - 1]) - cos(b * A[i - 1]);
		B[i] = sin(c * A[i - 1]) - cos(d * B[i - 1]);
	}
	p->push_back(A);
	p->push_back(B);
	return p;
}

std::string Peter::GetName()
{
	return "Peter";
}

std::vector<double> & Peter::GetParam()
{
	Chaotic::m_Param.push_back(0.9999);
	Chaotic::m_Param.push_back(0.789);
	Chaotic::m_Param.push_back(0.9163);
	Chaotic::m_Param.push_back(0.8174);
	return Chaotic::m_Param;
}

std::vector<double> & Peter::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	Chaotic::m_InitValue.push_back(0.5879);
	return Chaotic::m_InitValue;
}

Peter*& Peter::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Peter;
	}
	return m_pInstance;
}

size_t Peter::GetDimension()
{
	return 2;
}