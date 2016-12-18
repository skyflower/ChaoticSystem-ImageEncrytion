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

// ChaoticImageEncryptionView.h : CChaoticImageEncryptionView 类的接口
//

#pragma once

#include "ChaoticImageEncryptionDoc.h"

class CChaoticImageEncryptionView : public CView
{
protected: // 仅从序列化创建
	CChaoticImageEncryptionView();
	DECLARE_DYNCREATE(CChaoticImageEncryptionView)

// 特性
public:
	CChaoticImageEncryptionDoc* GetDocument() const;

// 操作
public:

private:
	CStatic *m_pResultImage;
	size_t m_nResultImage;

	
	//CStatic m_DisplayPicture;			//	显示图片的控件
	//CStatic m_PlainImageHist;			//	明文图像直方图
	//CStatic m_PlainImageRelative[3];	//	明文图像相邻像素相关性
	//CStatic m_CipherImageRelative[3];	//	密文图像相邻像素相关性
	//CStatic m_CipherImage;				//	密文图像
	//CStatic m_CipherImageHist;			//	密文图像直方图
	//
	//CStatic m_PureImageEntropy;			//	纯色灰度图像信息熵


	//CStatic *m_pDisplayPicture;			//	图片显示控件
	size_t m_nImageCount;
	POINT m_ShowPos;					//	图片显示的位置
	bool m_bReDrawImage;				//	是否需要重新显示图片
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CChaoticImageEncryptionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:
private:

	/*
	function:	计算图片显示区域的坐标

	Param:
		Num:		in,要显示图片的数量
		rowImage:	in,图片的宽
		colImage:	in,图片的高

	return:		图片在客户区显示的坐标
	*/
	POINT CalculateShowPos(size_t Num, size_t rowImage, size_t colImage);

	size_t CountDisplayImage();
	/*
	function:	设置图片显示的位置
	
	Param:
		cx:		图片显示在客户区域的坐标x值
		cy:		图片显示在客户区域的坐标y值
	*/
	void SetImageShowPos(size_t cx, size_t cy);

	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	void UpdateScrollInfo(size_t cx, size_t cy);

	/*
	function:	初始化滚动条信息
	*/
	void InitScrollInfo();

	enum {nRelativeImageCount = 3};
	enum {nDisplayNumPerRow = 4};

// 生成的消息映射函数
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

#ifndef _DEBUG  // ChaoticImageEncryptionView.cpp 中的调试版本
inline CChaoticImageEncryptionDoc* CChaoticImageEncryptionView::GetDocument() const
   { return reinterpret_cast<CChaoticImageEncryptionDoc*>(m_pDocument); }
#endif

