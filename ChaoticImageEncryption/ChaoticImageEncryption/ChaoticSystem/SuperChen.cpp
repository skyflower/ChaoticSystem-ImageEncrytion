#include "stdafx.h"
#include "SuperChen.h"


SuperChen *SuperChen::m_pInstance = nullptr;
SuperChen::SuperChen()
{
}


SuperChen::~SuperChen()
{
}

// param : a b c d h
// InitValue : x y z w
vector<double*> * SuperChen::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	if (Param.empty() || InitValue.empty()||	\
		(Param.size() != 5) || (InitValue.size() != 4))
	{
		return nullptr;
	}
	std::vector< double* > * p = nullptr;
	double & a = Param[0];
	double & b = Param[1];
	double & c = Param[2];
	double & d = Param[3];
	double & h = Param[4];
	double & x = InitValue[0];
	double & y = InitValue[1];
	double & z = InitValue[2];
	double & w = InitValue[3];

	if ((!CheckValid(x)) || (!CheckValid(y)) || (!CheckValid(z)) || (!CheckValid(w)))
	{
		return p;
	}
	p = new std::vector< double * >;
	double *Xn = new double[N];
	memset(Xn, 0, sizeof(double)* N);
	
	double *Yn = new double[N];
	memset(Yn, 0, sizeof(double)* N);
	
	double *Zn = new double[N];
	memset(Zn, 0, sizeof(double)* N);
	
	double *Wn = new double[N];
	memset(Wn, 0, sizeof(double)* N);
	
	Xn[0] = x;
	Yn[0] = y;
	Zn[0] = z;
	Wn[0] = w;
	
	std::function< void(double, double, double, double, std::vector<double> &)>  ChenCompute = \
		[&](double x, double y, double z, double w, std::vector<double> &p)
	{
		p[0] = a * (y - x) + w;
		p[1] = c * x - x * z;
		p[2] = x * y - b * z;
		p[3] = d * w - y * z;
	};
	
	std::vector<double> tmpOneVec(4);
	std::vector<double> tmpTwoVec(4);
	std::vector<double> tmpThrVec(4);
	std::vector<double> tmpFouVec(4);
	for (size_t i = 1; i < N; ++i)
	{
		ChenCompute(Xn[i - 1], Yn[i - 1], Zn[i - 1], Wn[i - 1], tmpOneVec);
		ChenCompute(Xn[i - 1] + h * tmpOneVec[0] / 2, Yn[i - 1] + h * tmpOneVec[1] / 2, Zn[i - 1] + h * tmpOneVec[2] / 2, Wn[i - 1] + h * tmpOneVec[3] / 2, tmpTwoVec);
		ChenCompute(Xn[i - 1] + h * tmpTwoVec[0] / 2, Yn[i - 1] + h * tmpTwoVec[1] / 2, Zn[i - 1] + h * tmpTwoVec[2] / 2, Wn[i - 1] + h * tmpTwoVec[3] / 2, tmpThrVec);
		ChenCompute(Xn[i - 1] + h * tmpThrVec[0], Yn[i - 1] + h * tmpThrVec[1], Zn[i - 1] + h * tmpThrVec[2], Wn[i - 1] + h * tmpThrVec[3], tmpFouVec);
		for (size_t j = 0; j < 4; ++j)
		{
			tmpOneVec[j] = h * (tmpOneVec[j] + 2 * tmpTwoVec[j] + 2 * tmpThrVec[j] + tmpFouVec[j]) / 6;
		}
		Xn[i] = Xn[i - 1] + tmpOneVec[0];
		Yn[i] = Yn[i - 1] + tmpOneVec[1];
		Zn[i] = Zn[i - 1] + tmpOneVec[2];
		Wn[i] = Wn[i - 1] + tmpOneVec[3];
	}
	p->push_back(Xn);
	p->push_back(Yn);
	p->push_back(Zn);
	p->push_back(Wn);
	return p;
}

std::string SuperChen::GetName()
{
	return "SuperChen";
}


std::vector<double> & SuperChen::GetParam()
{
	Chaotic::m_Param.push_back(10);
	Chaotic::m_Param.push_back(8 / 3.0f);
	Chaotic::m_Param.push_back(16);
	Chaotic::m_Param.push_back(-0.7);
	Chaotic::m_Param.push_back(0.001);
	return Chaotic::m_Param;
}

std::vector<double> & SuperChen::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.823);
	Chaotic::m_InitValue.push_back(0.779);
	Chaotic::m_InitValue.push_back(0.3457);
	Chaotic::m_InitValue.push_back(0.3871);
	return Chaotic::m_InitValue;
}

SuperChen*& SuperChen::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SuperChen;
	}
	return m_pInstance;
}

size_t SuperChen::GetDimension()
{
	return 4;
}