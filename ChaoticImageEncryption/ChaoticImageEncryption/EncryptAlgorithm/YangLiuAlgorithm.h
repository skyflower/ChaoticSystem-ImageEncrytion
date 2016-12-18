

/*

%   Image encryption algorithm based on hyper-chaotic system and dynamic S-box
%   Yang Liu, Xiaojun Tong, Jing Ma
%
%   Multimed Tools Appl
%   DOI 10.1007/s11042-015-2691-5

*/

#pragma once
#include "EncryptAlgorithm.h"
#include "..\math\math.h"

class YangLiuAlgorithm :public EncryptAlgorithm
{
public:
	YangLiuAlgorithm();
	virtual ~YangLiuAlgorithm();
	/*
	function: 加密算法

	Param:
		Param:		非密钥参数
		KeyValue:	密钥

	return :	加密图像
	*/
	virtual std::unique_ptr<CImage> EnCode(CImage *pImage, std::vector<double> Param, std::vector<double> KeyValue) override;

	/*
	function: 解密算法

	Param:
		Param:		非密钥参数
		KeyValue:	密钥

	return :	解密图像
	*/
	virtual std::unique_ptr<CImage> DnCode(CImage *pImage, std::vector<double> Param, std::vector<double> KeyValue) override;

private:

	/*
	function:	将tmpVec内double *序列转化成的整数末尾BitCount位组合成子节流

	Param:
		tmpVec:		混沌序列
		N:			tmpVec内double数组长度
		BitCount:	组合成的位数
		Precision:	计算精度
	
	return:		返回组合的子节流
	*/
	unsigned char * Combinate(std::vector<double*> *& tmpVec, size_t N, size_t BitCount, size_t Precision);

	/*
	function:	将整数X转化成N个比特位的子节流

	Param:
		X:		将要被转化的整数
		N:		需要被转化的位数

	return:		返回子节流的指针
	*/
	unsigned char * ToBitStream(size_t X, size_t N);

	/*
	function:	将数组长度为N的子节流X转化成整数

	Param:
		X:		将要被转化的子节流
		N:		子节流数组的长度

	return:		整数
	*/
	size_t BitStreamTo(unsigned char *X, size_t N);

	/*
	function:		将Kn子节流序列每Bits位分组，并将每个分组专程整数，输出整数数组指针

	Param:
		Kn：			被转化的子节流指针
		Bits:		分组的位数
		Limits:		转化到的区间[0, Limits - 1]
		length:		分组的数量，以及整数数组的长度

	return:		整数数组的指针
	*/
	size_t *UserGroup(unsigned char *Kn, size_t Bits, size_t Limit, size_t length);


	/*
	function:		计算模N剩余类的乘法逆元素

	Param:	
		N:		
	*/
	size_t * ReverseElement(size_t N);

};

