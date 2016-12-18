#include "stdafx.h"
#include "TentSine.h"


TentSine *TentSine::m_pInstance = nullptr;
TentSine::TentSine()
{
}


TentSine::~TentSine()
{
}


vector<double*> * TentSine::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	if (Param.empty() || InitValue.empty())
	{
		return nullptr;
	}
	double & r = Param[0];
	double & x = InitValue[0];
	if ((!ValidRange(r, 0, 4)) || (!CheckValid(x)) || (N < 1))
	{
		return nullptr;
	}
	double *p = new double[N];
	memset(p, 0, sizeof(double)* N);
		
	p[0] = x;
		
	for (size_t i = 1; i < N; ++i)
	{
		if (p[i - 1] < 0.5)
		{
			double tmp = r * p[i - 1] / 2 + (4 - r) * sin(3.1415926 * p[i - 1]) / 4;
			p[i] = tmp - static_cast<int>(tmp);
		}
		else
		{
			double tmp = r * (1 - p[i - 1]) / 2 + (4 - r) * sin(3.1415926 * p[i - 1]) / 4;
			p[i] = tmp - static_cast<int>(tmp);
		}
	}
	std::vector<double*> *tmp = new std::vector<double*>;
	tmp->push_back(p);
	return tmp;
}


std::string TentSine::GetName()
{
	return "TentSine";
}

std::vector<double> & TentSine::GetParam()
{
	Chaotic::m_Param.push_back(3.9999);
	return Chaotic::m_Param;
}

std::vector<double> & TentSine::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	return Chaotic::m_InitValue;
}

TentSine*& TentSine::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new TentSine;
	}
	return m_pInstance;
}

size_t TentSine::GetDimension()
{
	return 1;
}