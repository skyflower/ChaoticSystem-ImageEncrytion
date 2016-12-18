#include "stdafx.h"
#include "LogisticSine.h"


LogisticSine * LogisticSine::m_pInstance = nullptr;
LogisticSine::LogisticSine()
{
}


LogisticSine::~LogisticSine()
{
}


vector<double*> * LogisticSine::CreateSequence(vector<double> &Param, \
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
	double *Array = new double[N];
	memset(Array, 0, sizeof(double)* N);
	
	Array[0] = x;
	for (size_t i = 1; i < N; ++i)
	{
		double tmp = r * Array[i - 1] * (1 - Array[i - 1]) + (4 - r) * sin(3.1415926 * Array[i - 1]) / 4;
		Array[i] = tmp - static_cast<int>(tmp);
	}
	std::vector<double*> * tmp = new std::vector<double*>;
	tmp->push_back(Array);
	return tmp;
}

std::string LogisticSine::GetName()
{
	return "LogisticSine";
}


std::vector<double> & LogisticSine::GetParam()
{
	Chaotic::m_Param.push_back(2.9999);
	return Chaotic::m_Param;
}

std::vector<double> & LogisticSine::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	return Chaotic::m_InitValue;
}

LogisticSine*& LogisticSine::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new LogisticSine;
	}
	return m_pInstance;
}

size_t LogisticSine::GetDimension()
{
	return 1;
}