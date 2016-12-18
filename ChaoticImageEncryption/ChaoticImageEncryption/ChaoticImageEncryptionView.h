// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// ChaoticImageEncryptionView.h : CChaoticImageEncryptionView ��Ľӿ�
//

#pragma once

#include "ChaoticImageEncryptionDoc.h"

class CChaoticImageEncryptionView : public CView
{
protected: // �������л�����
	CChaoticImageEncryptionView();
	DECLARE_DYNCREATE(CChaoticImageEncryptionView)

// ����
public:
	CChaoticImageEncryptionDoc* GetDocument() const;

// ����
public:

private:
	CStatic *m_pResultImage;
	size_t m_nResultImage;

	
	//CStatic m_DisplayPicture;			//	��ʾͼƬ�Ŀؼ�
	//CStatic m_PlainImageHist;			//	����ͼ��ֱ��ͼ
	//CStatic m_PlainImageRelative[3];	//	����ͼ���������������
	//CStatic m_CipherImageRelative[3];	//	����ͼ���������������
	//CStatic m_CipherImage;				//	����ͼ��
	//CStatic m_CipherImageHist;			//	����ͼ��ֱ��ͼ
	//
	//CStatic m_PureImageEntropy;			//	��ɫ�Ҷ�ͼ����Ϣ��


	//CStatic *m_pDisplayPicture;			//	ͼƬ��ʾ�ؼ�
	size_t m_nImageCount;
	POINT m_ShowPos;					//	ͼƬ��ʾ��λ��
	bool m_bReDrawImage;				//	�Ƿ���Ҫ������ʾͼƬ
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CChaoticImageEncryptionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:
private:

	/*
	function:	����ͼƬ��ʾ���������

	Param:
		Num:		in,Ҫ��ʾͼƬ������
		rowImage:	in,ͼƬ�Ŀ�
		colImage:	in,ͼƬ�ĸ�

	return:		ͼƬ�ڿͻ�����ʾ������
	*/
	POINT CalculateShowPos(size_t Num, size_t rowImage, size_t colImage);

	size_t CountDisplayImage();
	/*
	function:	����ͼƬ��ʾ��λ��
	
	Param:
		cx:		ͼƬ��ʾ�ڿͻ����������xֵ
		cy:		ͼƬ��ʾ�ڿͻ����������yֵ
	*/
	void SetImageShowPos(size_t cx, size_t cy);

	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	void UpdateScrollInfo(size_t cx, size_t cy);

	/*
	function:	��ʼ����������Ϣ
	*/
	void InitScrollInfo();

	enum {nRelativeImageCount = 3};
	enum {nDisplayNumPerRow = 4};

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // ChaoticImageEncryptionView.cpp �еĵ��԰汾
inline CChaoticImageEncryptionDoc* CChaoticImageEncryptionView::GetDocument() const
   { return reinterpret_cast<CChaoticImageEncryptionDoc*>(m_pDocument); }
#endif

