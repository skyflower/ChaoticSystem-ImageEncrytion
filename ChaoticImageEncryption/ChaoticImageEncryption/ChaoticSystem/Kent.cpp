#include "stdafx.h"
#include "Kent.h"
#include "..\math\math.h"

Kent * Kent::m_pInstance = nullptr;
Kent::Kent()
{
}


Kent::~Kent()
{
}

std::string Kent::GetName()
{
	return "Kent";
}

vector<double*> * Kent::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	if (Param.empty() || InitValue.empty())
	{
		return nullptr;
	}
	double & x = InitValue[0];
	double & p = Param[0];
	double *Array = nullptr;
	if (N < 1 || !CheckValid(x) || fabs(p - x) < EPS || !ValidRange(p, 0, 1))
	{
		return nullptr;
	}
	Array = new double[N];
	memset(Array, 0, sizeof(double)* N);
	if (x < p)
	{
		Array[0] = x / p;
	}
	else
	{
		Array[0] = (1 - x) / (1 - p);
	}
	for (size_t i = 1; i < N; ++i)
	{
		if (Array[i - 1] < p)
		{
			Array[i] = Array[i - 1] / p;
		}
		else
		{
			Array[i] = (1 - Array[i - 1]) / (1 - p);
		}
	}
	std::vector<double*> * tmp = new std::vector<double*>;
	tmp->push_back(Array);
	return tmp;
}


std::vector<double> & Kent::GetParam()
{
	Chaotic::m_Param.push_back(0.567);
	return Chaotic::m_Param;
}

std::vector<double> & Kent::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.879);
	return Chaotic::m_InitValue;
}

Kent*& Kent::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Kent();
	}
	return m_pInstance;
}

size_t Kent::GetDimension()
{
	return 1;
}
