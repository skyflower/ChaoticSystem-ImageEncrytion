#include "stdafx.h"
#include "Logistic2D.h"

Logistic2D * Logistic2D::m_pInstance = nullptr;

Logistic2D::Logistic2D()
{
}


Logistic2D::~Logistic2D()
{
}


vector<double*> * Logistic2D::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	if (Param.empty() || InitValue.empty() || N < 1)
	{
		return nullptr;
	}
	double & a = Param[0];
	double & b = Param[1];
	double & c = Param[2];
	double & d = Param[3];
	double & x = InitValue[0];
	double & y = InitValue[1];
	if ((!CheckValid(x)) || (!CheckValid(y))||(!ValidRange(a, 2.75, 3.4))	\
		|| (!ValidRange(b, 2.75, 3.45) || (!ValidRange(c, 0.15, 0.21)) || (!ValidRange(d, 0.13, 0.15))) )
	{
		return nullptr;
	}
	std::vector<double*> *p = new std::vector<double*>;
	double *X = new double[N];
	double *Y = new double[N];
	memset(X, 0, sizeof(double)* N);
	memset(Y, 0, sizeof(double)* N);
	X[0] = x;
	Y[0] = y;
	for (size_t i = 1; i < N; ++i)
	{
		X[i] = a * X[i - 1] * (1 - X[i - 1]) + c * Y[i - 1] * Y[i - 1];
		Y[i] = b * Y[i - 1] * (1 - Y[i - 1]) + d * X[i - 1] * (X[i - 1] + Y[i - 1]);
	}
	p->push_back(X);
	p->push_back(Y);
	return p;
}

std::string Logistic2D::GetName()
{
	return "Logistic2D";
}

std::vector<double> & Logistic2D::GetParam()
{
	Chaotic::m_Param.push_back(2.9999);
	Chaotic::m_Param.push_back(3.299);
	Chaotic::m_Param.push_back(0.16);
	Chaotic::m_Param.push_back(0.14);
	return Chaotic::m_Param;
}

std::vector<double> & Logistic2D::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	Chaotic::m_InitValue.push_back(0.879);
	return Chaotic::m_InitValue;
}

Logistic2D*& Logistic2D::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Logistic2D;
	}
	return m_pInstance;
}

size_t Logistic2D::GetDimension()
{
	return 2;
}