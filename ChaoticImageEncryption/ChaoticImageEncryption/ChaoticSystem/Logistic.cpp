#include "stdafx.h"
#include "Logistic.h"

Logistic * Logistic::m_pInstance = nullptr;
Logistic::Logistic()
{
}


Logistic::~Logistic()
{
}


vector<double*> * Logistic::CreateSequence(std::vector<double> &Param, \
	std::vector<double> &InitValue, size_t N)
{
	vector<double*> * p = nullptr;
	double *Array = nullptr;
	if (Param.empty() || InitValue.empty())
	{
		return nullptr;
	}

	if (N < 1 || !Chaotic::CheckValid(InitValue[0]) || !Chaotic::ValidRange(Param[0], 3.57, 4))
	{
		return p;
	}
	Array = new double[N];
	memset(Array, 0, sizeof(double)* N);
	Array[0] = InitValue[0];
	for (size_t i = 1; i < N; ++i)
	{
		Array[i] = Param[0] * Array[i - 1] * (1 - Array[i - 1]);
	}
	p = new vector<double*>;
	p->push_back(Array);
	return p;
}

std::string Logistic::GetName()
{
	return "Logistic";
}

std::vector<double> & Logistic::GetParam()
{
	Chaotic::m_Param.push_back(3.99999);
	return Chaotic::m_Param;
}

std::vector<double> & Logistic::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	return Chaotic::m_InitValue;
}

Logistic*& Logistic::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Logistic;
	}
	return m_pInstance;
}

size_t Logistic::GetDimension()
{
	return 1;
}