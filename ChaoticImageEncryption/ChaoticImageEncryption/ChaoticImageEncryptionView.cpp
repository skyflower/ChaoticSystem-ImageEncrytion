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

// ChaoticImageEncryptionView.cpp : CChaoticImageEncryptionView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CChaoticImageEncryptionView ����/����

CChaoticImageEncryptionView::CChaoticImageEncryptionView()
{
	// TODO:  �ڴ˴���ӹ������
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	
	return CView::PreCreateWindow(cs);
}

// CChaoticImageEncryptionView ����

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

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CChaoticImageEncryptionView ���

#ifdef _DEBUG
void CChaoticImageEncryptionView::AssertValid() const
{
	CView::AssertValid();
}

void CChaoticImageEncryptionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChaoticImageEncryptionDoc* CChaoticImageEncryptionView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChaoticImageEncryptionDoc)));
	return (CChaoticImageEncryptionDoc*)m_pDocument;
}
#endif //_DEBUG


// CChaoticImageEncryptionView ��Ϣ�������
void CChaoticImageEncryptionView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SCROLLINFO si;
	GetScrollInfo(SB_HORZ, &si);//��ȡ��������Ϣ
	int nMaxPos = si.nMax - si.nPage;//�ɹ�����Χ���ֵ
	int scrValue = 0;//����ֵ
	int LINESIZE = 10;
	switch (nSBCode)
	{
	case SB_LINELEFT://��ť��������һ��
		if (si.nPos != 0)//�����Թ���
		{
			if (si.nPos - LINESIZE < 0)//�ɹ������ز���LINESIZE
				scrValue = si.nPos;
			else scrValue = LINESIZE;
		}
		//else scrValue=0;
		break;
	case SB_LINERIGHT://�Ұ�ť��������һ��
		if (si.nPos != nMaxPos)//�����Թ���
		{
			if (nMaxPos - si.nPos < LINESIZE)//�ɹ������ز���LINESIZE
				scrValue = -(nMaxPos - si.nPos);//����ͼƬ���Ϲ���
			else scrValue = -LINESIZE;
		}
		break;
	case SB_PAGEUP: //��������ͨ����������һ��
		if (si.nPos != 0)//�����Թ���
		{
			if (si.nPos - (int)si.nPage < 0)//�ɹ������ز���si.nPage
				scrValue = si.nPos;
			else scrValue = si.nPage;
		}
		break;
	case SB_PAGEDOWN://��������ͨ����������һ��
		if (si.nPos != nMaxPos)//�����Թ���
		{
			if (nMaxPos - si.nPos < si.nPage) //�ɹ������ز���si.nPage
				scrValue = -(nMaxPos - si.nPos);
			else
			{
				int j = si.nPage;
				scrValue = -j;
			}
		}
		break;
	case SB_THUMBTRACK: //�϶�������������nPos����λ��
		scrValue = si.nPos - nPos;
		break;
	}
	si.fMask = SIF_POS;

	SetScrollPos(SB_HORZ, si.nPos - scrValue);//���ù�����λ��

	ScrollWindow(scrValue, 0);


	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CChaoticImageEncryptionView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ˴������Ϣ����������

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

	// TODO:  �ڴ������ר�õĴ�������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
