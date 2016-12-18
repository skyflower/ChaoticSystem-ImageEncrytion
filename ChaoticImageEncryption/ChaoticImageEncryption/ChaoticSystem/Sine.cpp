#include "stdafx.h"
#include "Sine.h"
#include "..\math\math.h"


Sine *Sine::m_pInstance = nullptr;
Sine::Sine()
{
}


Sine::~Sine()
{
}


vector<double*> * Sine::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	if (Param.empty() || InitValue.empty())
	{
		return nullptr;
	}
	double & u = Param[0];
	double & x = InitValue[0];
	if (N < 1 || !CheckValid(u) || !CheckValid(x) || fabs(u - x) < EPS)
	{
		return nullptr;
	}
	double *Array = new double[N];
	memset(Array, 0, sizeof(double)* N);
	
	Array[0] = x;
	for (size_t i = 1; i < N; ++i)
	{
		Array[i] = u * sin(PI * Array[i - 1]);
	}
	std::vector<double*> *tmp = new std::vector<double*>;
	tmp->push_back(Array);
	return tmp;
}

std::string Sine::GetName()
{
	return "Sine";
}

std::vector<double> & Sine::GetParam()
{
	Chaotic::m_Param.push_back(0.99999);
	return Chaotic::m_Param;
}

std::vector<double> & Sine::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	return Chaotic::m_InitValue;
}

Sine*& Sine::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Sine;
	}
	return m_pInstance;
}

size_t Sine::GetDimension()
{
	return 1;
}