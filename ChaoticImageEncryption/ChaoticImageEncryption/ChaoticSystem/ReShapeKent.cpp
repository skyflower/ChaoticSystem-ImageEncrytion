#include "stdafx.h"
#include "ReShapeKent.h"
#include "..\math\math.h"


ReShapeKent *ReShapeKent::m_pInstance = nullptr;
ReShapeKent::ReShapeKent()
{
}


ReShapeKent::~ReShapeKent()
{
}

vector<double*> * ReShapeKent::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	double * Array = nullptr;
	if (Param.empty() || InitValue.empty())
	{
		return nullptr;
	}
	double & a = Param[0];
	double & p = Param[1];
	double & x = InitValue[0];
	if (!ValidRange(a, 0, 4) || !ValidRange(p, 0, 1) || \
		!ValidRange(x, 0, 1) || !CheckValid(x) || N < 1 \
		|| !CheckValid(p) || fabs(p - x) < EPS)
	{
		return nullptr;
	}
	Array = new double[N];
	memset(Array, 0, sizeof(double)* N);
	Array[0] = x;
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
		p = a * p * (1 - p);
	}
	vector<double*> * tmp = new vector< double *>;
	tmp->push_back(Array);
	return tmp;
}

std::string ReShapeKent::GetName()
{
	return "ReShapeKent";
}

std::vector<double> & ReShapeKent::GetParam()
{
	Chaotic::m_Param.push_back(3.9999);
	Chaotic::m_Param.push_back(0.789);
	return Chaotic::m_Param;
}

std::vector<double> & ReShapeKent::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	return Chaotic::m_InitValue;
}

ReShapeKent*& ReShapeKent::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ReShapeKent;
	}
	return m_pInstance;
}

size_t ReShapeKent::GetDimension()
{
	return 1;
}