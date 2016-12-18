

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
	function: �����㷨

	Param:
		Param:		����Կ����
		KeyValue:	��Կ

	return :	����ͼ��
	*/
	virtual std::unique_ptr<CImage> EnCode(CImage *pImage, std::vector<double> Param, std::vector<double> KeyValue) override;

	/*
	function: �����㷨

	Param:
		Param:		����Կ����
		KeyValue:	��Կ

	return :	����ͼ��
	*/
	virtual std::unique_ptr<CImage> DnCode(CImage *pImage, std::vector<double> Param, std::vector<double> KeyValue) override;

private:

	/*
	function:	��tmpVec��double *����ת���ɵ�����ĩβBitCountλ��ϳ��ӽ���

	Param:
		tmpVec:		��������
		N:			tmpVec��double���鳤��
		BitCount:	��ϳɵ�λ��
		Precision:	���㾫��
	
	return:		������ϵ��ӽ���
	*/
	unsigned char * Combinate(std::vector<double*> *& tmpVec, size_t N, size_t BitCount, size_t Precision);

	/*
	function:	������Xת����N������λ���ӽ���

	Param:
		X:		��Ҫ��ת��������
		N:		��Ҫ��ת����λ��

	return:		�����ӽ�����ָ��
	*/
	unsigned char * ToBitStream(size_t X, size_t N);

	/*
	function:	�����鳤��ΪN���ӽ���Xת��������

	Param:
		X:		��Ҫ��ת�����ӽ���
		N:		�ӽ�������ĳ���

	return:		����
	*/
	size_t BitStreamTo(unsigned char *X, size_t N);

	/*
	function:		��Kn�ӽ�������ÿBitsλ���飬����ÿ������ר�������������������ָ��

	Param:
		Kn��			��ת�����ӽ���ָ��
		Bits:		�����λ��
		Limits:		ת����������[0, Limits - 1]
		length:		������������Լ���������ĳ���

	return:		���������ָ��
	*/
	size_t *UserGroup(unsigned char *Kn, size_t Bits, size_t Limit, size_t length);


	/*
	function:		����ģNʣ����ĳ˷���Ԫ��

	Param:	
		N:		
	*/
	size_t * ReverseElement(size_t N);

};

