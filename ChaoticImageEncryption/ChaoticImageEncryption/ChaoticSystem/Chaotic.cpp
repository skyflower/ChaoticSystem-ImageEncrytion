#include "stdafx.h"
#include "Chaotic.h"
#include "..\math\math.h"

Chaotic *Chaotic::m_pInstance = nullptr;
Chaotic::Chaotic()
{
}


Chaotic::~Chaotic()
{
}

vector<double*> * Chaotic::CreateSequence(vector<double> &Param, \
	vector<double> &InitValue, size_t N)
{
	return nullptr;
}


bool Chaotic::ValidRange(double x, double Left, double Right)
{
	if (x> Left && x < Right)
	{
		return true;
	}
	return false;
}

bool Chaotic::CheckValid(double x)
{
	return true;
	if (ValidRange(x, 0, 1))
	{
		double t = 1 / x;
		size_t i = 1;
		size_t j = 0;

		while (t > i && j < sizeof(size_t)* 8 - 1)
		{
			i = i << 1;
			++j;
		}
		if (j == sizeof(size_t)* 8 - 1)
		{
			return false;
		}
		if (fabs(t - i) < EPS || fabs(t - i / 2) < EPS)
		{
			return false;
		}
		return true;
	}
	return false;
}

std::string Chaotic::GetName()
{
	return "";
}

Chaotic *& Chaotic::GetInstance()
{
	return m_pInstance;
}
