
#include "stdafx.h"
#include "math.h"
#include <iostream>
#include <vector>

using namespace std;

//const double EPS = 0.000001;
//const double PI = 3.1415926;

//template<typename type>
//void FreeArray(type *& Array)
//{
//	if (Array)
//	{
//		delete[] Array;
//		Array = nullptr;
//	}
//}
//
//template< typename Type>
//Type ** CreateMatrix(size_t Row, size_t Col)
//{
//	Type ** matrix = new Type *[Row];
//	for (size_t i = 0; i < Row; ++i)
//	{
//		*(matrix + i) = new Type[Col];
//	}
//	for (size_t i = 0; i < Row; ++i)
//	{
//		for (size_t j = 0; j < Col; ++j)
//		{
//			matrix[i][j] = Type();
//		}
//	}
//	return matrix;
//}
//
//template <typename Type>
//void FreeMatrix(Type **&matrix, size_t Row)
//{
//	if ((matrix == nullptr) || (Row < 1))
//	{
//		return;
//	}
//	for (size_t i = 0; i < Row; ++i)
//	{
//		delete[] * (matrix + i);
//		*(matrix + i) = nullptr;
//	}
//	delete[] matrix;
//	matrix = nullptr;
//}
//
//template<typename type>
//type * MatrixToSequence(type **Matrix, size_t Row, size_t Col)
//{
//	if ((matrix == nullptr) || (Row < 1) || (Col < 1))
//	{
//		return nullptr;
//	}
//	size_t L = Row * Col;
//	type * Array = new type[L];
//
//	size_t k = 0;
//	for (size_t i = 0; i < Row; ++i)
//	{
//		for (size_t j = 0; j < Col; ++j)
//		{
//			Array[k++] = Matrix[i][j];
//		}
//	}
//	return Array;
//}
//
//template<typename type>
//type ** SequenceToMatrix(type * Array, size_t Row, size_t Col)
//{
//	if ((Array == nullptr) || (Row < 1) || (Col < 1))
//	{
//		return nullptr;
//	}
//	type ** matrix = CreateMatrix(Row, Col);
//	size_t k = 0;
//	for (size_t i = 0; i < Row; ++i)
//	{
//		for (size_t j = 0; j < Col; ++j)
//		{
//			matrix[i][j] = Array[k++];
//		}
//	}
//	return matrix;
//}
//
//template<typename type>
//void Output(type *Array, size_t N)
//{
//	if ((Array == nullptr) || (N < 1))
//	{
//		return;
//	}
//	for (size_t i = 0; i < N; ++i)
//	{
//		cout << Array[i] << "\t";
//	}
//	cout << endl;
//}
//
//template<typename type>
//void Output(type **Matrix, size_t Row, size_t Col)
//{
//	if ((Matrix == nullptr) || (Row < 1) || (Col < 1))
//	{
//		return;
//	}
//	for (size_t i = 0; i < Row; ++i)
//	{
//		for (size_t j = 0; j < Col; ++j)
//		{
//			cout << Matrix[i][j] << "\t";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//
//
//
////  矩阵转置
//template<typename type>
//type ** Transposition(type ** Matrix, size_t Row, size_t Col)
//{
//	if ((Matrix == nullptr) || (Row < 1) || (Col < 1))
//	{
//		return nullptr;
//	}
//	type ** tmp = CreateMatrix(Col, Row);
//	for (size_t i = 0; i < Row; ++i)
//	{
//		for (size_t j = 0; j < Col; ++j)
//		{
//			tmp[j][i] = Matrix[i][j];
//		}
//	}
//	return tmp;
//}
//
//
//template<typename type>
//double AverageX(type *p, size_t L)
//{
//	if ((p == nullptr) || (L < 1))
//	{
//		return 0;
//	}
//	double Result = 0;
//	for (size_t i = 0; i< L; ++i)
//	{
//		Result += p[i];
//	}
//	return Result / (double)L;
//}
//
//template<typename type>
//double AverageX2(type *p, size_t L)
//{
//	if ((p == nullptr) || (L < 1))
//	{
//		return 0;
//	}
//	double Result = 0.0;
//	for (size_t i = 0; i < L; ++i)
//	{
//		Result += p[i] * p[i];
//	}
//	return Result / (double)L;
//}
//
//template<typename type>
//double Variant(type * X, size_t L)
//{
//	if ((X == nullptr) || (L < 1))
//	{
//		return 0;
//	}
//	double avgX = AverageX(X, L);
//	double avgX2 = AverageX2(X, L);
//	if (fabs(avgX) < EPS || fabs(avgX2) < EPS)
//	{
//		return 0;
//	}
//	return avgX2 - avgX * avgX;
//}
//
//
//template<typename type>
//double Cov(type * X, type *Y, size_t L)
//{
//	if ((X == nullptr) || (Y == nullptr) || (L < 1))
//	{
//		return 0;
//	}
//	double AvgX = AverageX(X, L);
//	double AvgY = AverageX(Y, L);
//	double * tmp = new double[L];
//	for (size_t i = 0; i < L; ++i)
//	{
//		tmp[i] = (X[i] - AvgX) * (Y[i] - AvgY);
//	}
//	return AverageX(tmp, L);
//}
//
////  两个随机变量的相关系数
//template<typename type>
//double Coef(type * First, type * Second, size_t L)
//{
//	if ((First == nullptr) || (Second == nullptr) || (L < 1))
//	{
//		return 0;
//	}
//	double CovNumber = Cov(First, Second, L);
//	double VariantX = Variant(First, X);
//	double VariantY = Variant(Second, Y);
//	if (fabs(CovNumber) < EPS || fabs(VariantX) < EPS || fabs(VariantY) < EPS)
//	{
//		return 0;
//	}
//	return CovNumber / (sqrt(VariantX) * sqrt(VariantY))
//}

void CharToInt(char *& Src, int *& Des, size_t L)
{
	if ((Src == nullptr) || (L < 1))
	{
		return;
	}
	if (Des == nullptr)
	{
		Des = new int[L];
		memset(Des, 0, sizeof(int)* L);
	}
	for (size_t i = 0; i < L; ++i)
	{
		Des[i] = Src[i];
	}
}

void CharToInt(char **&Src, int **&Des, size_t Row, size_t Col)
{
	if ((Src == nullptr) || (Row < 1) || (Col < 1))
	{
		return;
	}
	if (Des == nullptr)
	{
		Des = CreateMatrix<int>(Row, Col);
	}
	for (size_t i = 0; i < Row; ++i)
	{
		for (size_t j = 0; j < Col; ++j)
		{
			Des[i][j] = Src[i][j];
		}
	}
}


std::vector<unsigned int *>* GroupByToInt(unsigned char *pBitsArray, unsigned int nBitSize,\
	unsigned int nBitCount, unsigned int nLimitValue, unsigned int nLength, unsigned int nMode)
{
	if (nBitSize < nBitCount * nLength * nMode)
	{
		return nullptr;
	}
	std::vector<unsigned int*> * Result = new std::vector<unsigned int*>(nMode);
	for (unsigned int i = 0; i < nMode; ++i)
	{
		unsigned int * Seq = new unsigned int[nLength];
		memset(Seq, 0, sizeof(unsigned int)* nLength);
		Result->push_back(Seq);
	}
	for (unsigned int i = 0; i < nLength; ++i)
	{
		for (unsigned int j = 0; j < nMode; ++j)
		{
			unsigned int *pCurSeq = *(Result->data() + j);
			unsigned tmp = BitStreamToInt(pBitsArray + (nMode * i + j) * nBitCount, nBitCount);
			tmp = tmp % nLimitValue;
			*(pCurSeq + i) = tmp;
		}
	}
	return Result;
}


unsigned int BitStreamToInt(unsigned char *pBits, unsigned int nSize)
{
	unsigned int Result = 0;
	for (int i = nSize - 1; i > -1 ; --i)
	{
		Result = 2 * Result + pBits[i];
	}
	return Result;
}

unsigned char * IntToBitStream(unsigned long X, unsigned int N)
{
	unsigned char *Array = new unsigned char[N];
	memset(Array, 0, sizeof(unsigned char)* N);

	for (unsigned int i = 0; X > 0; ++i)
	{
		if ((X & 1) == 0)
		{
			Array[i] = 0;
		}
		else
		{
			Array[i] = 1;
		}
		X = X / 2;
	}
	return Array;
}


