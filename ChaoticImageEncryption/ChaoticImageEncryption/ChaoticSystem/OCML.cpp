#include "stdafx.h"
#include "OCML.h"
#include "math.h"

extern const double EPS;
extern const double PI;

OCML *OCML::m_pInstance = nullptr;
OCML::OCML()
{
}


OCML::~OCML()
{
}

vector<double*> * OCML::CreateSequence(std::vector<double> &Param, \
	std::vector<double> &InitValue, size_t N)
{
	std::vector<double*> *p = nullptr;
	if (Param.empty() || InitValue.empty())
	{
		return p;
	}
	return nullptr;
}

std::string OCML::GetName()
{
	return "OCML";
}

std::vector<double> & OCML::GetParam()
{
	Chaotic::m_Param.push_back(2.9999);
	Chaotic::m_Param.push_back(3.299);
	Chaotic::m_Param.push_back(0.16);
	Chaotic::m_Param.push_back(0.14);
	return Chaotic::m_Param;
}

std::vector<double> & OCML::GetInitValue()
{
	Chaotic::m_InitValue.push_back(0.123);
	Chaotic::m_InitValue.push_back(0.879);
	return Chaotic::m_InitValue;
}

OCML*& OCML::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		//m_pInstance = new OCML;
	}
	return m_pInstance;
}