
#include "stdafx.h"
#include <cstdlib>
#include <cmath>
#include <memory>
#include <vector>
#include <functional>
#include "..\math\math.h"
#include "..\ChaoticSystem\ChaoticSystem.h"
using namespace std;

//extern const double EPS;
//extern const double PI;
//const double EPS = 0.00001;


inline bool ValidRange(double x, double Left, double Right)
{
	if (x> Left && x < Right)
	{
		return true;
	}
	return false;
}

bool CheckValid(double x)
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




//double * Sine(double u, double x, size_t N)
//{
//	double * Array = nullptr;
//	if (N < 1 || !CheckValid(u) || !CheckValid(x) || fabs(u - x) < EPS)
//	{
//		return Array;
//	}
//	Array = new double[N];
//	memset(Array, 0, sizeof(double)* N);
//
//	Array[0] = x;
//	for (size_t i = 1; i < N; ++i)
//	{
//		Array[i] = u * sin(PI * Array[i - 1]);
//	}
//	return Array;
//}

//std::vector< double *> * SLMM(double a, double b, double x, double y, size_t N)
//{
//	std::vector< double * > * p = nullptr;
//	if (!ValidRange(a, 0, 3) || !ValidRange(b, 0, 1) || !CheckValid(x) || !CheckValid(y) || N < 1)
//	{
//		return p;
//	}
//	p = new std::vector< double *>;
//	double * A = new double[N];
//	memset(A, 0, sizeof(double)* N);
//
//	double * B = new double[N];
//	memset(B, 0, sizeof(double)* N);
//
//	A[0] = x;
//	B[0] = y;
//	//const double pi = 3.1415926;
//	for (size_t i = 1; i < N; ++i)
//	{
//		A[i] = a * (sin(PI * B[i - 1]) + b) * A[i - 1] * (1 - A[i - 1]);
//		B[i] = a * (sin(PI * A[i]) + b) * B[i - 1] * (1 - B[i - 1]);
//	}
//	p->push_back(A);
//	p->push_back(B);
//	return p;
//}

//std::vector<double*> * ChenChaotic(double a, double b, double c, \
//	double d, double x, double y, double z, double w, double h, size_t N)
//{
//	std::vector< double* > * p = nullptr;
//	if ((!CheckValid(x)) || (!CheckValid(y)) || (!CheckValid(z)) || (!CheckValid(w)))
//	{
//		return p;
//	}
//	p = new std::vector< double * >;
//	double *Xn = new double[N];
//	memset(Xn, 0, sizeof(double)* N);
//
//	double *Yn = new double[N];
//	memset(Yn, 0, sizeof(double)* N);
//
//	double *Zn = new double[N];
//	memset(Zn, 0, sizeof(double)* N);
//
//	double *Wn = new double[N];
//	memset(Wn, 0, sizeof(double)* N);
//
//	Xn[0] = x;
//	Yn[0] = y;
//	Zn[0] = z;
//	Wn[0] = w;
//
//	std::function< void(double, double, double, double, std::vector<double> &)>  ChenCompute = \
//		[&](double x, double y, double z, double w, std::vector<double> &p)
//	{
//		p[0] = a * (y - x) + w;
//		p[1] = c * x - x * z;
//		p[2] = x * y - b * z;
//		p[3] = d * w - y * z;
//	};
//
//	std::vector<double> tmpOneVec(4);
//	std::vector<double> tmpTwoVec(4);
//	std::vector<double> tmpThrVec(4);
//	std::vector<double> tmpFouVec(4);
//	for (size_t i = 1; i < N; ++i)
//	{
//		ChenCompute(Xn[i - 1], Yn[i - 1], Zn[i - 1], Wn[i - 1], tmpOneVec);
//		ChenCompute(Xn[i - 1] + h *tmpOneVec[0] / 2, Yn[i - 1] + h*tmpOneVec[1] / 2, Zn[i - 1] + h*tmpOneVec[2] / 2, Wn[i - 1] + h*tmpOneVec[3] / 2, tmpTwoVec);
//		ChenCompute(Xn[i - 1] + h *tmpTwoVec[0] / 2, Yn[i - 1] + h*tmpTwoVec[1] / 2, Zn[i - 1] + h*tmpTwoVec[2] / 2, Wn[i - 1] + h*tmpTwoVec[3] / 2, tmpThrVec);
//		ChenCompute(Xn[i - 1] + h * tmpThrVec[0], Yn[i - 1] + h * tmpThrVec[1], Zn[i - 1] + h * tmpThrVec[2], Wn[i - 1] + h * tmpThrVec[3], tmpFouVec);
//		for (size_t j = 0; j < 4; ++j)
//		{
//			tmpOneVec[j] = h * (tmpOneVec[j] + 2 * tmpTwoVec[j] + 2 * tmpThrVec[j] + tmpFouVec[j]) / 6;
//		}
//		Xn[i] = Xn[i - 1] + tmpOneVec[0];
//		Yn[i] = Yn[i - 1] + tmpOneVec[1];
//		Zn[i] = Zn[i - 1] + tmpOneVec[2];
//		Wn[i] = Wn[i - 1] + tmpOneVec[3];
//	}
//	p->push_back(Xn);
//	p->push_back(Yn);
//	p->push_back(Zn);
//	p->push_back(Wn);
//	return p;
//}


//  0 < r < 4,0 < x < 1, type(N) is size_t
//double * LogisticTent(double r, double x, size_t N)
//{
//	double * p = nullptr;
//	if (!ValidRange(r, 0, 4) || (!CheckValid(x)) || (N < 1))
//	{
//		return p;
//	}
//	p = new double[N];
//	memset(p, 0, sizeof(double)* N);
//
//	p[0] = x;
//	for (size_t i = 1; i < N; ++i)
//	{
//		if (p[i - 1] < 0.5)
//		{
//			double tmp = r * p[i - 1] * (1 - p[i - 1]) + (4 - r) * p[i - 1] / 2;
//			p[i] = tmp - static_cast<int>(tmp);
//		}
//		else
//		{
//			double tmp = r * p[i - 1] * (1 - p[i - 1]) + (4 - r) * (1 - p[i - 1]) / 2;
//			p[i] = tmp - static_cast<int>(tmp);
//		}
//	}
//	return p;
//}

// 0 < r < 4, 0 < x < 1, type(N) is int
//double * LogisticSine(double r, double x, size_t N)
//{
//	if ((!ValidRange(r, 0, 4)) || (!CheckValid(x)) || (N < 1))
//	{
//		return nullptr;
//	}
//	double *Array = new double[N];
//	memset(Array, 0, sizeof(double)* N);
//
//	Array[0] = x;
//	for (size_t i = 1; i < N; ++i)
//	{
//		double tmp = r * Array[i - 1] * (1 - Array[i - 1]) + (4 - r) * sin(3.1415926 * Array[i - 1]) / 4;
//		Array[i] = tmp - static_cast<int>(tmp);
//	}
//	return Array;
//}

// 
//double *TentSine(double r, double x, size_t N)
//{
//	if ((!ValidRange(r, 0, 4)) || (!CheckValid(x)) || (N < 1))
//	{
//		return nullptr;
//	}
//	double *p = new double[N];
//	memset(p, 0, sizeof(double)* N);
//
//	p[0] = x;
//
//	for (size_t i = 1; i < N; ++i)
//	{
//		if (p[i - 1] < 0.5)
//		{
//			double tmp = r * p[i - 1] / 2 + (4 - r) * sin(3.1415926 * p[i - 1]) / 4;
//			p[i] = tmp - static_cast<int>(tmp);
//		}
//		else
//		{
//			double tmp = r * (1 - p[i - 1]) / 2 + (4 - r) * sin(3.1415926 * p[i - 1]) / 4;
//			p[i] = tmp - static_cast<int>(tmp);
//		}
//	}
//	return p;
//}