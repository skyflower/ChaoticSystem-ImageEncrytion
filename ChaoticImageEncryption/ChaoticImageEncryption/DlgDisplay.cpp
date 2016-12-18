// DlgDisplay.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChaoticImageEncryption.h"
#include "DlgDisplay.h"
#include "afxdialogex.h"


// CDlgDisplay �Ի���

IMPLEMENT_DYNAMIC(CDlgDisplay, CDialogEx)

CDlgDisplay::CDlgDisplay(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDisplay::IDD, pParent)
	, m_dMaxValue(0)
	, m_dMinValue(0)
{
	m_pImage = nullptr;
}

CDlgDisplay::~CDlgDisplay()
{
	if (m_stImage.m_hWnd != NULL)
	{
		m_stImage.DestroyWindow();
	}
	m_pImage = nullptr;
	m_dMaxValue = m_dMinValue = 0;
}

void CDlgDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ETMAXVALUE, m_dMaxValue);
	DDX_Text(pDX, IDC_ETMINVALUE, m_dMinValue);
	//  DDX_Control(pDX, IDC_STDISPLAYIMAGE, m_stImage);
}

void CDlgDisplay::SetData(CImage *pImage, double MaxValue, double MinValue)
{
	m_pImage = pImage;
	m_dMaxValue = MaxValue;
	m_dMinValue = MinValue;
}


BEGIN_MESSAGE_MAP(CDlgDisplay, CDialogEx)
	ON_WM_CREATE()
//	ON_WM_DRAWITEM()
ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgDisplay ��Ϣ�������


int CDlgDisplay::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (m_stImage.m_hWnd == NULL)
	{
		if (m_stImage.Create(L"", SS_BITMAP | SS_CENTERIMAGE | SS_REALSIZEIMAGE	\
			| SS_SUNKEN | WS_BORDER | WS_CHILD, RECT(), this))
		{
			TRACE("Create Static Text Success\n\n");
		}
		else
		{
			TRACE("Create Static Text Failed\n\n");
		}
	}
	// TODO:  �ڴ������ר�õĴ�������

	

	return 0;
}


//void CDlgDisplay::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	
//
//	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
//}


void CDlgDisplay::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������

	if (m_stImage.GetBitmap() != HBITMAP(*m_pImage))
	{
		m_stImage.SetBitmap(HBITMAP(*m_pImage));
	}
	
	m_stImage.MoveWindow(0, 0, m_pImage->GetWidth(), m_pImage->GetHeight());
	m_stImage.ShowWindow(true);
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}
