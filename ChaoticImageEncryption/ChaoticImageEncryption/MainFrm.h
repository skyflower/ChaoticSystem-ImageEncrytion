// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.h : CMainFrame 类的接口
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
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

private:
	BOOL m_bLoadImageFlag;				//  是否加载图像
	CImage *m_pImage;					//	 当前加载的图像
	EncryptAlgorithm *m_pCurrentAlgo;	//	当前加密算法

	//	分析结果图像<名称，图像>
	std::unordered_map<std::string, CImage*> *m_pAnalysisResult;		

	//	错误密钥解密图像以及解密图像的直方图
	std::unordered_map<double, std::pair<CImage*, CImage*>> *m_WrongKeyDnImage;

	
public:

	const CImage * GetCurrentImage() const;

	CImage ** GetCurrentDisplayImage(size_t &Num) const;
	
	//POINT m_ShowPos;
private:
	PerformanceAnalysis *m_pAnalysis;

	CProgressCtrl *m_pProgCtrl;

	//	混沌系统的容器<混沌系统名称,混沌系统指针>
	std::unordered_map<std::string, Chaotic*> *m_pChaoticSystem;

	

private:

	/*
	function:	设置分析对象的参数

	Param:
		pAlgo:		被分析的算法指针
		Param:		加密算法的非密钥参数
		KeyValue:	加密算法的密钥

	return：
	*/
	void SetAnalysisParam(EncryptAlgorithm *pAlgo, std::vector<double> &Param, std::vector<double> &KeyValue);

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
public:

	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();

// 生成的消息映射函数
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


