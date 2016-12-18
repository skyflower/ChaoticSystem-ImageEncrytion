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

// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include <iostream>
#include <functional>
#include <unordered_map>
#include ".\ChaoticSystem\Chaotic.h"
#include "EncryptAlgorithm\EncryptAlgorithm.h"
#include "PerformanceAnalysis\RandomPerformance.h"


class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

private:
	BOOL m_bLoadImageFlag;				//  �Ƿ����ͼ��
	CImage *m_pImage;					//	 ��ǰ���ص�ͼ��
	EncryptAlgorithm *m_pCurrentAlgo;	//	��ǰ�����㷨

	//	�������ͼ��<���ƣ�ͼ��>
	std::unordered_map<std::string, CImage*> *m_pAnalysisResult;		

	//	������Կ����ͼ���Լ�����ͼ���ֱ��ͼ
	std::unordered_map<double, std::pair<CImage*, CImage*>> *m_WrongKeyDnImage;

	
public:

	const CImage * GetCurrentImage() const;

	CImage ** GetCurrentDisplayImage(size_t &Num) const;
	
	//POINT m_ShowPos;
private:
	PerformanceAnalysis *m_pAnalysis;

	CProgressCtrl *m_pProgCtrl;

	//	����ϵͳ������<����ϵͳ����,����ϵͳָ��>
	std::unordered_map<std::string, Chaotic*> *m_pChaoticSystem;

	

private:

	/*
	function:	���÷�������Ĳ���

	Param:
		pAlgo:		���������㷨ָ��
		Param:		�����㷨�ķ���Կ����
		KeyValue:	�����㷨����Կ

	return��
	*/
	void SetAnalysisParam(EncryptAlgorithm *pAlgo, std::vector<double> &Param, std::vector<double> &KeyValue);

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
public:

	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLogisticMap();
	afx_msg void OnKent();
	afx_msg void OnHenon();
	afx_msg void OnImageEncryptionOne();
	afx_msg void OnTest();
	afx_msg void OnAnalysis();
	afx_msg void OnEncryption();
	afx_msg void OnImageEntropy();
	afx_msg void OnYangLiuAlgo();
	afx_msg void OnWangXuAlgorithm();
	afx_msg void OnUpdateIEOne(CCmdUI *pCmdUI);
	afx_msg void OnUpdateYangLiu(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWangXuAlgorithm(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEncryption(CCmdUI *pCmdUI);
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


