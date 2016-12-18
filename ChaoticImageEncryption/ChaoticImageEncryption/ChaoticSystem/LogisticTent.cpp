#include "stdafx.h"
#include "LogisticTent.h"

LogisticTent *LogisticTent::m_pInstance = nullptr;
LogisticTent::LogisticTent()
{
}


LogisticTent::~LogisticTent()
{
}


vector<double*> * LogisticTent::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	if (Param.empty() || InitValue.empty())
	{
		return nullptr;
	}
	double * p = nullptr;
	double & r = Param[0];
	double & x = InitValue[0];
	if (!ValidRange(r, 0, 4) || (!CheckValid(x)) || (N < 1))
	{
		return nullptr;
	}
	p = new double[N];
	memset(p, 0, sizeof(double)* N);
	
	p[0] = x;
	for (size_t i = 1; i < N; ++i)
	{
		if (p[i - 1] < 0.5)
		{
			double tmp = r * p[i - 1] * (1 - p[i - 1]) + (4 - r) * p[i - 1] / 2;
			p[i] = tmp - static_cast<int>(tmp);
		}
		else
		{
			double tmp = r * p[i - 1] * (1 - p[i - 1]) + (4 - r) * (1 - p[i - 1]) / 2;
			p[i] = tmp - static_cast<int>(tmp);
		}
	}
	std::vector<double*> *tmp = new std::vector<double*>;
	tmp->push_back(p);
	return tmp;
}

std::string LogisticTent::GetName()
{
	return "LogisticTent";
}

std::vector<double> & LogisticTent::GetParam()
{
	Chaotic::m_Param.push_back(3.999);
	return Chaotic::m_Param;
}


std::vector<double> & LogisticTent::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	return Chaotic::m_InitValue;
}

LogisticTent*& LogisticTent::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new LogisticTent;
	}
	return m_pInstance;
}

size_t LogisticTent::GetDimension()
{
	return 1;
}