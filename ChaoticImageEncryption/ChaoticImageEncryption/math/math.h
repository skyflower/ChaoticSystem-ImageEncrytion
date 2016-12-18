

#pragma once

#include <iostream>
#include <vector>

using namespace std;

const double EPS = 0.000001;
const double Delta = 0.000000000000001;	//	10^-15
const double PI = 3.1415926;
const size_t GrayImageBits = 8;
const size_t GrayImageLevel = 256;
const size_t ColorImageBits = 24;
const size_t ColorImageLevel = 16777216;
const size_t DisplayInterval = 20;


template<typename type>
void FreeArray(type *& Array)
{
	if (Array)
	{
		delete[] Array;
		Array = nullptr;
	}
}

template< typename Type>
Type ** CreateMatrix(size_t Row, size_t Col)
{
	Type ** matrix = new Type *[Row];
	for (size_t i = 0; i < Row; ++i)
	{
		*(matrix + i) = new Type[Col];
	}
	for (size_t i = 0; i < Row; ++i)
	{
		for (size_t j = 0; j < Col; ++j)
		{
			matrix[i][j] = Type();
		}
	}
	return matrix;
}

template <typename Type>
void FreeMatrix(Type **&matrix, size_t Row)
{
	if ((matrix == nullptr) || (Row < 1))
	{
		return;
	}
	for (size_t i = 0; i < Row; ++i)
	{
		delete[] * (matrix + i);
		*(matrix + i) = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;
}

template<typename Type>
void FreeVec(std::vector<Type*> *&SeqVec)
{
	if (SeqVec && (!SeqVec->empty()) )
	{
		size_t nSize = SeqVec->size();
		for (size_t i = 0; i < nSize; ++i)
		{
			Type *&p = *(SeqVec->data() + i);
			delete p;
			p = nullptr;
		}
		delete SeqVec;
		SeqVec = nullptr;
	}
}

template<typename type>
type * MatrixToSequence(type **Matrix, size_t Row, size_t Col)
{
	if ((matrix == nullptr) || (Row < 1) || (Col < 1))
	{
		return nullptr;
	}
	size_t L = Row * Col;
	type * Array = new type[L];

	size_t k = 0;
	for (size_t i = 0; i < Row; ++i)
	{
		for (size_t j = 0; j < Col; ++j)
		{
			Array[k++] = Matrix[i][j];
		}
	}
	return Array;
}

template<typename type>
type ** SequenceToMatrix(type * Array, size_t Row, size_t Col)
{
	if ((Array == nullptr) || (Row < 1) || (Col < 1))
	{
		return nullptr;
	}
	type ** matrix = CreateMatrix<type>(Row, Col);
	size_t k = 0;
	for (size_t i = 0; i < Row; ++i)
	{
		for (size_t j = 0; j < Col; ++j)
		{
			matrix[i][j] = Array[k++];
		}
	}
	return matrix;
}

template<typename type>
void Output(type *Array, size_t N)
{
	if ((Array == nullptr) || (N < 1))
	{
		return;
	}
	for (size_t i = 0; i < N; ++i)
	{
		cout << Array[i] << "\t";
	}
	cout << endl;
}

template<typename type>
void Output(type **Matrix, size_t Row, size_t Col)
{
	if ((Matrix == nullptr) || (Row < 1) || (Col < 1))
	{
		return;
	}
	for (size_t i = 0; i < Row; ++i)
	{
		for (size_t j = 0; j < Col; ++j)
		{
			cout << Matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}



//  矩阵转置
template<typename type>
type ** Transposition(type ** Matrix, size_t Row, size_t Col)
{
	if ((Matrix == nullptr) || (Row < 1) || (Col < 1))
	{
		return nullptr;
	}
	type ** tmp = CreateMatrix<type>(Col, Row);
	for (size_t i = 0; i < Row; ++i)
	{
		for (size_t j = 0; j < Col; ++j)
		{
			tmp[j][i] = Matrix[i][j];
		}
	}
	return tmp;
}


template<typename type>
double AverageX(type *p, size_t L)
{
	if ((p == nullptr) || (L < 1))
	{
		return 0;
	}
	double Result = 0;
	for (size_t i = 0; i< L; ++i)
	{
		Result += p[i];
	}
	return Result / (double)L;
}

template<typename type>
double AverageX2(type *p, size_t L)
{
	if ((p == nullptr) || (L < 1))
	{
		return 0;
	}
	double Result = 0.0;
	for (size_t i = 0; i < L; ++i)
	{
		Result += p[i] * p[i];
	}
	return Result / (double)L;
}

template<typename type>
double Variant(type * X, size_t L)
{
	if ((X == nullptr) || (L < 1))
	{
		return 0;
	}
	double avgX = AverageX(X, L);
	double avgX2 = AverageX2(X, L);
	if (fabs(avgX) < EPS || fabs(avgX2) < EPS)
	{
		return 0;
	}
	return avgX2 - avgX * avgX;
}


template<typename type>
double Cov(type * X, type *Y, size_t L)
{
	if ((X == nullptr) || (Y == nullptr) || (L < 1))
	{
		return 0;
	}
	double AvgX = AverageX(X, L);
	double AvgY = AverageX(Y, L);
	double * tmp = new double[L];
	for (size_t i = 0; i < L; ++i)
	{
		tmp[i] = (X[i] - AvgX) * (Y[i] - AvgY);
	}
	return AverageX(tmp, L);
}

//  两个随机变量的相关系数
template<typename type>
double Coef(type * First, type * Second, size_t L)
{
	if ((First == nullptr) || (Second == nullptr) || (L < 1))
	{
		return 0;
	}
	double CovNumber = Cov(First, Second, L);
	double VariantX = Variant(First, L);
	double VariantY = Variant(Second, L);
	if (fabs(CovNumber) < EPS || fabs(VariantX) < EPS || fabs(VariantY) < EPS)
	{
		return 0;
	}
	return CovNumber / (sqrt(VariantX) * sqrt(VariantY));
}


void CharToInt(char *& Src, int *& Des, size_t L);

void CharToInt(char **&Src, int **&Des, size_t Row, size_t Col);

/*
function:	将二进制序列，按照每nBitCount位转化成一个整数的方式，转化成Mode个整数序列，每个整数最大值nLimitValue

Param:
	pBitsArray:		in,二进制序列 pBitsArray[i] = { 0, 1}
	nBitSize:		in,pBitsArray的长度
	nLimitValue:	in,转化后整数的最大值,若超过最大值，则执行模运算
	nLength:		in,整数序列的长度
	Mode:			in,整数序列的个数
	整数区间为[0, nLimitValue - 1]

return:		转化正确返回Mode个整数序列，错误则返回nullptr;
*/
std::vector<unsigned int*>* GroupByToInt(unsigned char *pBitsArray, unsigned int nBitSize, \
	unsigned int nBitCount, unsigned int nLimitValue, unsigned int nLength, unsigned int Mode);

unsigned int BitStreamToInt(unsigned char *pBits, unsigned int nSize);

unsigned char * IntToBitStream(unsigned long X, unsigned int N);

