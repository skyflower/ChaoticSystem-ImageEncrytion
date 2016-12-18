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

// ChaoticImageEncryptionView.cpp : CChaoticImageEncryptionView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ChaoticImageEncryption.h"
#endif

#include "ChaoticImageEncryptionDoc.h"
#include "ChaoticImageEncryptionView.h"
#include "MainFrm.h"

#include "math\math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChaoticImageEncryptionView

IMPLEMENT_DYNCREATE(CChaoticImageEncryptionView, CView)

BEGIN_MESSAGE_MAP(CChaoticImageEncryptionView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_CREATE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CChaoticImageEncryptionView 构造/析构

CChaoticImageEncryptionView::CChaoticImageEncryptionView()
{
	// TODO:  在此处添加构造代码
	m_ShowPos.x = m_ShowPos.y = 0;
	m_bReDrawImage = true;
	
	
	//m_DisplayPicture.Create(L"PictureControl", WS_CHILD | WS_VISIBLE, RECT(), this);
}

CChaoticImageEncryptionView::~CChaoticImageEncryptionView()
{
	if (m_nResultImage != 0)
	{
		for (size_t i = 0; i < m_nResultImage; ++i)
		{
			m_pResultImage[i].DestroyWindow();
		}
		delete[] m_pResultImage;
		m_pResultImage = nullptr;
	}
}

BOOL CChaoticImageEncryptionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	return CView::PreCreateWindow(cs);
}

// CChaoticImageEncryptionView 绘制

void CChaoticImageEncryptionView::OnDraw(CDC* /*pDC*/)
{
	CChaoticImageEncryptionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	TRACE0("CChaoticImageEncryptionView::OnDraw(CDC*)\n");
	CMainFrame *pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (pMainFrame == nullptr)
	{
		return;
	}
	size_t tmpImageCount = 0;
	//m_nImageCount = 0;
	CImage **pImage = pMainFrame->GetCurrentDisplayImage(tmpImageCount);
	if (tmpImageCount == 0)
	{
		return;
	}
	if (m_nResultImage > 0)
	{
		if ((m_pResultImage[0].GetBitmap() != (HBITMAP)(*pImage[0]))	\
			|| (tmpImageCount != m_nImageCount))
		{
			m_nImageCount = tmpImageCount;
			m_bReDrawImage = true;
		}
	}
	size_t rowImage = pImage[0]->GetWidth();
	size_t colImage = pImage[0]->GetHeight();

	m_ShowPos = CalculateShowPos(m_nImageCount, rowImage, colImage);
	
	if ((m_nImageCount > 0) && (m_bReDrawImage == true))
	{
		for (size_t i = 0; i < m_nResultImage; ++i)
		{
			m_pResultImage[i].ShowWindow(FALSE);
		}
		size_t MaxXLabel = (rowImage + DisplayInterval) * (m_nImageCount >= nDisplayNumPerRow ? nDisplayNumPerRow : m_nImageCount) - DisplayInterval;
		size_t MaxYLabel = (colImage + DisplayInterval) * ((m_nImageCount - 1) / nDisplayNumPerRow + 1) - DisplayInterval;
		UpdateScrollInfo(MaxXLabel, MaxYLabel);
		for (size_t i = 0; i < m_nImageCount; ++i)
		{
			size_t x = (rowImage + DisplayInterval) * (i % nDisplayNumPerRow);
			size_t y = (colImage + DisplayInterval) * (i / nDisplayNumPerRow);
			m_pResultImage[i].SetBitmap((HBITMAP)(*pImage[i]));
			m_pResultImage[i].ShowWindow(true);
			m_pResultImage[i].MoveWindow(x + m_ShowPos.x, y + m_ShowPos.y, rowImage, colImage);
		}
		m_bReDrawImage = false;
	}
	delete[] pImage;
	pImage = nullptr;

	// TODO:  在此处为本机数据添加绘制代码
}

void CChaoticImageEncryptionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CChaoticImageEncryptionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CChaoticImageEncryptionView 诊断

#ifdef _DEBUG
void CChaoticImageEncryptionView::AssertValid() const
{
	CView::AssertValid();
}

void CChaoticImageEncryptionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChaoticImageEncryptionDoc* CChaoticImageEncryptionView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChaoticImageEncryptionDoc)));
	return (CChaoticImageEncryptionDoc*)m_pDocument;
}
#endif //_DEBUG


// CChaoticImageEncryptionView 消息处理程序
void CChaoticImageEncryptionView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SCROLLINFO si;
	GetScrollInfo(SB_HORZ, &si);//获取滚动条信息
	int nMaxPos = si.nMax - si.nPage;//可滚动范围最大值
	int scrValue = 0;//滚动值
	int LINESIZE = 10;
	switch (nSBCode)
	{
	case SB_LINELEFT://左按钮被单击了一下
		if (si.nPos != 0)//还可以滚动
		{
			if (si.nPos - LINESIZE < 0)//可滚动像素不够LINESIZE
				scrValue = si.nPos;
			else scrValue = LINESIZE;
		}
		//else scrValue=0;
		break;
	case SB_LINERIGHT://右按钮被单击了一下
		if (si.nPos != nMaxPos)//还可以滚动
		{
			if (nMaxPos - si.nPos < LINESIZE)//可滚动像素不够LINESIZE
				scrValue = -(nMaxPos - si.nPos);//负数图片向上滚动
			else scrValue = -LINESIZE;
		}
		break;
	case SB_PAGEUP: //滚动条左通道被单击了一下
		if (si.nPos != 0)//还可以滚动
		{
			if (si.nPos - (int)si.nPage < 0)//可滚动像素不够si.nPage
				scrValue = si.nPos;
			else scrValue = si.nPage;
		}
		break;
	case SB_PAGEDOWN://滚动条右通道被单击了一下
		if (si.nPos != nMaxPos)//还可以滚动
		{
			if (nMaxPos - si.nPos < si.nPage) //可滚动像素不够si.nPage
				scrValue = -(nMaxPos - si.nPos);
			else
			{
				int j = si.nPage;
				scrValue = -j;
			}
		}
		break;
	case SB_THUMBTRACK: //拖动滚动条滑柄，nPos保存位置
		scrValue = si.nPos - nPos;
		break;
	}
	si.fMask = SIF_POS;

	SetScrollPos(SB_HORZ, si.nPos - scrValue);//设置滚动条位置

	ScrollWindow(scrValue, 0);


	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CChaoticImageEncryptionView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si);
	int nMaxPos = si.nMax - si.nPage;
	int scrValue = 0;
	int LINESIZE = 10;
	switch (nSBCode)
	{
	case SB_LINEUP:
		if (si.nPos != 0)
		{
			if (si.nPos < LINESIZE)
			{
				scrValue = si.nPos;
			}
			else scrValue = LINESIZE;
		}
		break;
	case SB_LINEDOWN:
		if (si.nPos != nMaxPos)
		{
			if (nMaxPos - si.nPos < LINESIZE)
			{
				scrValue = si.nPos - nMaxPos;
			}
			else scrValue = -LINESIZE;
		}
		break;
	case SB_PAGEUP:
		if (si.nPos != 0)
		{
			if (si.nPos - (int)si.nPage < 0)
				scrValue = si.nPos;
			else scrValue = si.nPage;
		}
		break;
	case SB_PAGEDOWN:
		if (si.nPos != nMaxPos)
		{
			if (nMaxPos - si.nPos < si.nPage)
				scrValue = -(nMaxPos - si.nPos);
			else
			{
				int j = si.nPage;
				scrValue = -j;
			}
		}
		break;
	case SB_THUMBTRACK:
		scrValue = si.nPos - nPos;
		break;
	}

	SetScrollPos(SB_VERT, si.nPos - scrValue);
	ScrollWindow(0, scrValue);

	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CChaoticImageEncryptionView::UpdateScrollInfo(size_t cx, size_t cy)
{
	CRect rect;
	GetClientRect(&rect);

	SCROLLINFO si;
	si.fMask = SIF_ALL;
	si.nPos = 0;
	//ShowScrollBar(SB_BOTH, FALSE);
	GetScrollInfo(SB_VERT, &si);
	si.nPage = rect.Height();
	si.nMax = cy;
	SetScrollInfo(SB_VERT, &si);

	if (rect.Height() < cy)
	{
		ShowScrollBar(SB_VERT, TRUE);
	}
	else
	{
		ShowScrollBar(SB_VERT, FALSE);
	}
	
	GetScrollInfo(SB_HORZ, &si);
	si.nPage = rect.Width();
	si.nMax = cx;
	SetScrollInfo(SB_HORZ, &si);
	if (rect.Width() < cx)
	{
		ShowScrollBar(SB_HORZ, TRUE);
	}
	else
	{
		ShowScrollBar(SB_HORZ, FALSE);
	}
	
}


void CChaoticImageEncryptionView::InitScrollInfo()
{
	static bool bInitScrollFlag = false;
	if (bInitScrollFlag == true)
	{
		return;
	}
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.nMin = 0;
	si.nMax = 100;
	si.nPage = 10;
	si.nPos = 0;
	si.fMask = SIF_ALL;
	SetScrollInfo(SB_VERT, &si);
	si.nPage = 60;
	SetScrollInfo(SB_HORZ, &si);
	ShowScrollBar(SB_BOTH, FALSE);
	bInitScrollFlag = true;
}

POINT CChaoticImageEncryptionView::CalculateShowPos(size_t Num, size_t ImageWidth, size_t ImageHeight)
{
	CRect rect;
	POINT pt{ 0, 0 };
	GetClientRect(&rect);

	ImageWidth = (ImageWidth + DisplayInterval) * (Num >= nDisplayNumPerRow ? nDisplayNumPerRow : Num) - DisplayInterval;
	ImageHeight = (ImageWidth + DisplayInterval) *((Num - 1) / nDisplayNumPerRow + 1) - DisplayInterval;

	if (rect.Width() >= ImageWidth && rect.Height() >= ImageHeight)
	{
		int i = (rect.Height() - ImageHeight) / 2;
		int j = (rect.Width() - ImageWidth) / 2;
		pt.x = rect.left + j;
		pt.y = rect.top + i;
	}
	else if (rect.Width() < ImageWidth && rect.Height() >= ImageHeight)
	{
		int i = (rect.Height() - ImageHeight) / 2;
		pt.x = 0;
		pt.y = i;
	}
	else if (rect.Width() > ImageWidth && rect.Height() < ImageHeight)
	{
		int j = (rect.Width() - ImageWidth) / 2;
		pt.x = j;
		pt.y = 0;
	}
	return pt;
}

void CChaoticImageEncryptionView::SetImageShowPos(size_t cx, size_t cy)
{
	CMainFrame *pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (pMainFrame == nullptr)
	{
		return ;
	}
	const CImage *pImage = pMainFrame->GetCurrentImage();
	if (pImage == nullptr)
	{
		return ;
	}
	m_pResultImage[0].MoveWindow(cx, cy, pImage->GetWidth(), pImage->GetHeight());
	
}

void CChaoticImageEncryptionView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	// TODO:  在此处添加消息处理程序代码

	TRACE0("CChaoticImageEncryptionView::OnSize(UINT nType, int cx, int cy)\n");
	TRACE2("WindowSize = %d * %d\n\n", cx, cy);

	CMainFrame *pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (pMainFrame == nullptr)
	{
		return;
	}

	const CImage *pImage = pMainFrame->GetCurrentImage();
	if (pImage == nullptr)
	{
		return;
	}

	size_t rowImage = pImage->GetWidth();
	size_t colImage = pImage->GetHeight();

	m_ShowPos = CalculateShowPos(m_nImageCount, rowImage, colImage);
	if (m_nImageCount > 0)
	{
		size_t MaxXLabel = (rowImage + DisplayInterval) * (m_nImageCount >= nDisplayNumPerRow ? nDisplayNumPerRow : m_nImageCount) - DisplayInterval;
		size_t MaxYLabel = (colImage + DisplayInterval) * ((m_nImageCount - 1) / nDisplayNumPerRow + 1) - DisplayInterval;
		UpdateScrollInfo(MaxXLabel, MaxYLabel);
		for (size_t i = 0; i < m_nImageCount; ++i)
		{
			size_t x = (rowImage + DisplayInterval) * (i % nDisplayNumPerRow);
			size_t y = (colImage + DisplayInterval) * (i / nDisplayNumPerRow);
			//m_pResultImage[i].SetBitmap((HBITMAP)(*pImage[i]));
			m_pResultImage[i].MoveWindow(x + m_ShowPos.x, y + m_ShowPos.y, rowImage, colImage);
		}
	}
}



int CChaoticImageEncryptionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	InitScrollInfo();
	DWORD tmpShowStyle = SS_BITMAP | SS_CENTERIMAGE | SS_REALSIZEIMAGE | SS_SUNKEN | WS_BORDER | WS_CHILD;
	
	m_nResultImage = 20;
	m_pResultImage = new CStatic[m_nResultImage];

	for (size_t i = 0; i < m_nResultImage; ++i)
	{
		m_pResultImage[i].Create(L"", tmpShowStyle, RECT(), this);
		m_pResultImage[i].ShowWindow(true);
	}

	return 0;
}


size_t CChaoticImageEncryptionView::CountDisplayImage()
{

	return 0;
}

BOOL CChaoticImageEncryptionView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int nCount = zDelta / WHEEL_DELTA;

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si);
	int nMaxPos = si.nMax - si.nPage;
	const size_t PerCount = 5;
	int CurPos = 0;
	CurPos = nCount / static_cast<double>(PerCount)*si.nPage;
	if (si.nPos - CurPos >= nMaxPos)
	{
		CurPos = nMaxPos;
	}
	else if (si.nPos - CurPos <= 0)
	{
		CurPos = 0;
	}
	else
	{
		CurPos = si.nPos - CurPos;
	}
	CurPos = CurPos - si.nPos;
	SetScrollPos(SB_VERT, CurPos + si.nPos);
	ScrollWindow(0, -CurPos);
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
