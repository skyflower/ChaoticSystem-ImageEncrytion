#pragma once
#include "afxwin.h"


// CDlgDisplay �Ի���

class CDlgDisplay : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDisplay)

public:
	CDlgDisplay(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDisplay();

	void SetData(CImage *pImage, double MaxValue, double MinValue);
// �Ի�������
	enum { IDD = IDD_DISPLAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	double m_dMaxValue;
	double m_dMinValue;
	CImage *m_pImage;
	CStatic m_stImage;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnPaint();
};
