

#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <vector>
#include <functional>
#include "math.h"
using namespace std;

//extern const double EPS;
//extern const double PI;
//const double EPS = 0.00001;

template<typename type>
void FreeVec(std::vector< type * > *& SeqVec)
{
	if (SeqVec)
	{
		for (size_t i = 0; i < SeqVec->size(); ++i)
		{
			type *& p = *(SeqVec->data() + i);
			delete[] p;
			p = nullptr;
		}
		delete SeqVec;
		SeqVec = nullptr;
	}
}


inline bool ValidRange(double x, double Left, double Right);


bool CheckValid(double x);


//double * ReShapeKent(double a, double p, double x, size_t N);


//double * Sine(double u, double x, size_t N);

//std::vector< double *> * SLMM(double a, double b, double x, double y, size_t N);

//std::vector<double*> * ChenChaotic(double a, double b, double c, \
	double d, double x, double y, double z, double w, double h, size_t N);


//  0 < r < 4,0 < x < 1, type(N) is size_t
//double * LogisticTent(double r, double x, size_t N);

// 0 < r < 4, 0 < x < 1, type(N) is int
//double * LogisticSine(double r, double x, size_t N);

// 
//double *TentSine(double r, double x, size_t N);