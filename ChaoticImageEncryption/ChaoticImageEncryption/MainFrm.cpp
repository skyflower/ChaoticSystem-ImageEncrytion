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

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "ChaoticImageEncryption.h"
#include "ChaoticImageEncryptionView.h"

#include "MainFrm.h"

#include <memory>
#include "math\math.h"
#include "Image\Image.h"
#include "ImageTitle.h"
#include "DlgDisplay.h"


#include "ChaoticSystem\Henon.h"
#include "ChaoticSystem\Kent.h"
#include "ChaoticSystem\Logistic.h"
#include "ChaoticSystem\Logistic2D.h"
#include "ChaoticSystem\LogisticSine.h"
#include "ChaoticSystem\LogisticTent.h"
#include "ChaoticSystem\OCML.h"
#include "ChaoticSystem\Peter.h"
#include "ChaoticSystem\ReShapeKent.h"
#include "ChaoticSystem\Sine.h"
#include "ChaoticSystem\SLMM.h"
#include "ChaoticSystem\SuperChen.h"
#include "ChaoticSystem\TentSine.h"
#include "ChaoticSystem\PWLCM.h"

#include "EncryptAlgorithm\testAlgorithm.h"
#include "EncryptAlgorithm\YangLiuAlgorithm.h"
#include "EncryptAlgorithm\WangXuAlgorithm.h"
#include <fstream>





#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(IDB_LOGISTICMAP, &CMainFrame::OnLogisticMap)
	ON_COMMAND(IDB_KENTMAP, &CMainFrame::OnKent)
	ON_COMMAND(IDB_HENONMAP, &CMainFrame::OnHenon)
	ON_COMMAND(IDB_IEONE, &CMainFrame::OnImageEncryptionOne)
	ON_COMMAND(IDB_TEST, &CMainFrame::OnTest)
	ON_COMMAND(IDB_ANALYSIS, &CMainFrame::OnAnalysis)
	ON_COMMAND(IDB_ENCRYPTION, &CMainFrame::OnEncryption)
	ON_COMMAND(IDB_IMAGEENTROPY, &CMainFrame::OnImageEntropy)
	ON_COMMAND(IDB_YANGLIU, &CMainFrame::OnYangLiuAlgo)
	ON_COMMAND(IDB_WangXuAlgorithm, &CMainFrame::OnWangXuAlgorithm)
	ON_UPDATE_COMMAND_UI(IDB_IEONE, &CMainFrame::OnUpdateIEOne)
	ON_UPDATE_COMMAND_UI(IDB_YANGLIU, &CMainFrame::OnUpdateYangLiu)
	ON_UPDATE_COMMAND_UI(IDB_WangXuAlgorithm, &CMainFrame::OnUpdateWangXuAlgorithm)
	ON_UPDATE_COMMAND_UI(IDB_ENCRYPTION, &CMainFrame::OnUpdateEncryption)
//	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);

	m_pImage = nullptr;
	m_bLoadImageFlag = FALSE;
	m_pCurrentAlgo = nullptr;
	m_pAnalysis = nullptr;
	m_WrongKeyDnImage = nullptr;
	m_pAnalysisResult = nullptr;
	m_pProgCtrl = nullptr;
	

	//m_ShowPos.x = m_ShowPos.y = 0;
	m_pChaoticSystem = new std::unordered_map<std::string, Chaotic*>;
	m_pChaoticSystem->insert(std::make_pair(Henon::GetInstance()->GetName(), Henon::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(Kent::GetInstance()->GetName(), Kent::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(Logistic::GetInstance()->GetName(), Logistic::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(Logistic2D::GetInstance()->GetName(), Logistic2D::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(LogisticSine::GetInstance()->GetName(), LogisticSine::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(LogisticTent::GetInstance()->GetName(), LogisticTent::GetInstance()));
	//m_pChaoticSystem->insert(std::make_pair(OCML::GetInstance()->GetName(), OCML::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(Peter::GetInstance()->GetName(), Peter::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(ReShapeKent::GetInstance()->GetName(), ReShapeKent::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(Sine::GetInstance()->GetName(), Sine::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(SLMM::GetInstance()->GetName(), SLMM::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(SuperChen::GetInstance()->GetName(), SuperChen::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(TentSine::GetInstance()->GetName(), TentSine::GetInstance()));
	m_pChaoticSystem->insert(std::make_pair(PWLCM::GetInstance()->GetName(), PWLCM::GetInstance()));
}

CMainFrame::~CMainFrame()
{
	if (m_pChaoticSystem)
	{
		if (!m_pChaoticSystem->empty())
		{
			for (std::unordered_map<std::string, Chaotic*>::iterator iter = m_pChaoticSystem->begin();	\
				iter != m_pChaoticSystem->end(); ++iter)
			{
				Chaotic *&p = iter->second;
				delete p;
				p = nullptr;
			}
		}
		
		delete m_pChaoticSystem;
		m_pChaoticSystem = nullptr;
	}
	if (m_pImage)
	{
		delete m_pImage;
		m_pImage = nullptr;
	}
	if (m_pCurrentAlgo)
	{
		delete m_pCurrentAlgo;
		m_pCurrentAlgo = nullptr;
	}
	if (m_pAnalysis)
	{
		delete m_pAnalysis;
		m_pAnalysis = nullptr;
	}
	if (m_pAnalysisResult)
	{
		if (!m_pAnalysisResult->empty())
		{
			for (std::unordered_map<std::string, CImage*>::iterator iter = m_pAnalysisResult->begin();	\
				iter != m_pAnalysisResult->end(); ++iter)
			{
				CImage *& p = iter->second;
				delete p;
				p = nullptr;
			}
		}
		
		delete m_pAnalysisResult;
		m_pAnalysisResult = nullptr;
	}
	if (m_WrongKeyDnImage)
	{
		if (!m_WrongKeyDnImage->empty())
		{
			for (std::unordered_map<double, std::pair<CImage*, CImage*>>::iterator iter = m_WrongKeyDnImage->begin();	\
				iter != m_WrongKeyDnImage->end(); ++iter)
			{
				std::pair<CImage*, CImage*> &p = iter->second;
				delete p.first;
				p.first = nullptr;
				delete p.second;
				p.second = nullptr;
			}
		}
		
		delete m_WrongKeyDnImage;
		m_WrongKeyDnImage = nullptr;
	}

	if (m_pProgCtrl != nullptr)
	{
		m_pProgCtrl->DestroyWindow();
		delete m_pProgCtrl;
		m_pProgCtrl = nullptr;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	if (m_pProgCtrl == nullptr)
	{
		m_pProgCtrl = new CProgressCtrl;
	}
	m_pProgCtrl->Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH, CRect(10, 10, 200, 30), \
		this, IDC_PROGRESSCTRL);
	m_pProgCtrl->SetRange(0, 100);
	m_pProgCtrl->ShowWindow(FALSE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnFileOpen()
{
	//TRACE0("CMainFrame::OnFileOpen()\n\n");
	wchar_t szFilter[] = L"BMP Files (*.bmp)|*.bmp|JPG Files (*.jpg;*.jpeg;*.jpe)|*.jpg;*.jpeg;*.jpe|PNG Files (*.png)|*.png|TIF Files(*.tif;*.tiff)|*.tif;*.tiff|GIF Files (*.gif)|*.gif|DIB Files(*.dib)|*.dib| All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE, (LPCTSTR)"BMP", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if (dlg.DoModal() == IDOK)
	{
		if (m_bLoadImageFlag == TRUE)
		{
			//Invalidate();
			m_pImage->Detach();
			//m_pImage->LoadFromResource
			m_bLoadImageFlag = FALSE;
		}

		//这块儿填写打开文件后对文件相应的操作  
		CString FilePath = dlg.GetPathName();
		CString FileExtName = dlg.GetFileExt();
		CString filename = dlg.GetFileName();
		this->SetWindowTextW(L"Image-" + filename);
		FileExtName.MakeLower();
		if ((FileExtName == "bmp") || (FileExtName == "jpeg") || (FileExtName == "jpe") || (FileExtName == "jpg") || \
			(FileExtName == "png") || (FileExtName == "dib") || (FileExtName == "tif") || (FileExtName == "tiff") || (FileExtName == "gif"))
		{
			//displayimage();
			if (m_bLoadImageFlag == FALSE)
			{
				if (m_pImage == nullptr)
				{
					m_pImage = new CImage;
				}
				else if ((m_pAnalysisResult != nullptr) || (m_WrongKeyDnImage != nullptr))
				{
					if (m_pAnalysisResult)
					{
						if (!m_pAnalysisResult->empty())
						{
							for (std::unordered_map<std::string, CImage*>::iterator iter = m_pAnalysisResult->begin();	\
								iter != m_pAnalysisResult->end(); ++iter)
							{
								CImage *& p = iter->second;
								delete p;
								p = nullptr;
							}
						}

						delete m_pAnalysisResult;
						m_pAnalysisResult = nullptr;
					}
					if (m_WrongKeyDnImage)
					{
						if (!m_WrongKeyDnImage->empty())
						{
							for (std::unordered_map<double, std::pair<CImage*, CImage*>>::iterator iter = m_WrongKeyDnImage->begin();	\
								iter != m_WrongKeyDnImage->end(); ++iter)
							{
								std::pair<CImage*, CImage*> &p = iter->second;
								delete p.first;
								p.first = nullptr;
								delete p.second;
								p.second = nullptr;
							}
						}

						delete m_WrongKeyDnImage;
						m_WrongKeyDnImage = nullptr;
					}
					CMainFrame *pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
					if (pMainFrame != nullptr)
					{
						CChaoticImageEncryptionView *pView = dynamic_cast<CChaoticImageEncryptionView*>(pMainFrame->GetActiveView());
						if (pView)
						{
							pView->Invalidate();
						}
					}
				}
				m_pImage->Load(FilePath);
				m_bLoadImageFlag = TRUE;
				
				Invalidate(TRUE);
				
			}
		}
		else
		{
			AfxMessageBox(L"cannot open this file");
		}
	}
}

void CMainFrame::OnFileNew()
{
	
}

void CMainFrame::SetAnalysisParam(EncryptAlgorithm *pAlgo,	\
	std::vector<double> &Param, std::vector<double> &KeyValue)
{
	if (m_pCurrentAlgo)
	{
		delete m_pCurrentAlgo;
		m_pCurrentAlgo = nullptr;
	}
	m_pCurrentAlgo = pAlgo;
	if (m_pAnalysis)
	{
		delete m_pAnalysis;
		m_pAnalysis = nullptr;
	}
	m_pAnalysis = new PerformanceAnalysis(m_pImage, m_pCurrentAlgo, Param, KeyValue);
}


void CMainFrame::OnLogisticMap()
{
	TRACE0("void CMainFrame::OnLogisticMap()\n\n");
	// TODO:  在此添加命令处理程序代码
}


void CMainFrame::OnKent()
{
	// TODO:  在此添加命令处理程序代码
	TRACE0("void CMainFrame::OnKent()\n\n");
}


void CMainFrame::OnHenon()
{
	// TODO:  在此添加命令处理程序代码
	TRACE0("void CMainFrame::OnHenon()\n\n");
}

// Encryption Algorithm button
void CMainFrame::OnImageEncryptionOne()
{
	testAlgorithm *algo = new testAlgorithm;
	std::vector<double> Param{3.999};
	std::vector<double> KeyValue{0.123};
	SetAnalysisParam(algo, Param, KeyValue);
}


void CMainFrame::OnTest()
{
	// TODO:  在此添加命令处理程序代码
	TRACE0("CMainFrame::OnTest()\n\n");
	if (m_pAnalysis == nullptr)
	{
		return;
	}
	if (m_pImage && !m_pImage->IsNull())
	{
		//return;
		//YangLiuAlgorithm algo;
		//std::vector<double> Param{ 10, 8 / 3, 16, -0.7, 0.01, 10000, 15 };
		//std::vector<double> KeyValue{ 0.123, 0.879, 0.543, 0.9159, 0.173, 0.8731, 0.59301, 0.98591 };
		//std::unique_ptr<CImage> pImage = algo.EnCode(m_pImage, Param, KeyValue);

		CImage *PureImage = new CImage;
		PureImage->Create(GrayImageLevel, GrayImageLevel, GrayImageBits);
		ChaoticEncrypt::Image::InitGrayImageColorTable(PureImage);
		
		CImage *ChangeImage = new CImage;
		ChangeImage->Create(GrayImageLevel, GrayImageLevel, GrayImageBits);
		std::vector<double> PlainText(2 * GrayImageLevel + 2);
		clock_t AllStartTime = clock();
		double LocalTime = 0;
		m_pProgCtrl->ShowWindow(TRUE);
		size_t ResultPerRand = 3;
		for (size_t i = 0; i < GrayImageLevel; ++i)
		{
			ChaoticEncrypt::Image::InitGrayImageToPureImage(PureImage, i);
			ChaoticEncrypt::Image::InitGrayImageToPureImage(ChangeImage, i);
			CImage *pEnOne = m_pAnalysis->GetCipherImage(PureImage);// algo.EnCode(PureImage, Param, KeyValue);
			//CImage *pEnOne = EnOne.release();
			double tmpNPCR = 0.00001;
			double tmpUACI = 0.00001;
			clock_t tmpStartTime = clock_t();
			m_pProgCtrl->SetPos(i / static_cast<double>(GrayImageLevel)* 100);
			for (size_t j = 0; j < ResultPerRand; ++j)
			{
				size_t tmpX = (static_cast<size_t>(rand())) % GrayImageLevel;
				size_t tmpY = (static_cast<size_t>(rand())) % GrayImageLevel;
				size_t tmp = ChangeImage->GetPixel(tmpX, tmpY) % GrayImageLevel;
				tmp = (tmp + 1) % GrayImageLevel;
				ChangeImage->SetPixelRGB(tmpX, tmpY, tmp, tmp, tmp);
				CImage *pEnTwo = m_pAnalysis->GetCipherImage(ChangeImage); //algo.EnCode(ChangeImage, Param, KeyValue);
				//CImage *pEnTwo = EnTwo.release();
				std::vector<double> &&Result = ChaoticEncrypt::Image::NPCR_UACI(pEnOne, pEnTwo);
				tmpNPCR += Result[0];
				tmpUACI += Result[1];
				delete pEnTwo;
				pEnTwo = nullptr;
				ChangeImage->SetPixelRGB(tmpX, tmpY, i, i, i);
			}
			clock_t tmpEndTime = clock_t();
			LocalTime += static_cast<double>(tmpEndTime - tmpStartTime) / CLOCKS_PER_SEC;
			PlainText[2 * i] = tmpNPCR / ResultPerRand;
			PlainText[2 * i + 1] = tmpUACI / ResultPerRand;
			delete pEnOne;
			pEnOne = nullptr;
		}
		clock_t AllEndTime = clock();
		PlainText[2 * GrayImageLevel] = static_cast<double>(AllEndTime - AllStartTime) / CLOCKS_PER_SEC;
		PlainText[2 * GrayImageLevel + 1] = LocalTime;
		delete PureImage;
		PureImage = nullptr;

		delete ChangeImage;
		ChangeImage = nullptr;

		std::ofstream fw;
		fw.open("C:\\Users\\Administrator\\Desktop\\a.txt");
		if (fw.is_open())
		{
			for (size_t i = 0; i < PlainText.size(); i = i + 2)
			{
				fw << PlainText[i] << "\t" << PlainText[i + 1] << "\n";
			}
		}
		fw.flush();

		fw.clear();
		fw.close();

		//delete m_pImage;
		//m_pImage = pImage.release();
		TRACE1("Pixel Bits = %d\n\n", m_pImage->GetBPP());
		CMainFrame *pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		if (pMainFrame != nullptr)
		{
			CChaoticImageEncryptionView *pView = dynamic_cast<CChaoticImageEncryptionView*>(pMainFrame->GetActiveView());
			if (pView)
			{
				pView->Invalidate();
				//pView->m_bReDrawImage = true;
			}
		}
	}

}


void CMainFrame::OnAnalysis()
{
	// TODO:  在此添加命令处理程序代码
	if (m_pAnalysis && m_pCurrentAlgo && m_pImage)
	{
		return ;
		//	明文图像水平方向相邻像素
		CImage *p = ChaoticEncrypt::Image::HorzRelative(m_pImage);
		m_pAnalysisResult->insert(std::make_pair("HorizontalOrgImage", p));
		
		//	明文图像垂直方向相邻像素
		p = ChaoticEncrypt::Image::VertRelative(m_pImage);
		m_pAnalysisResult->insert(std::make_pair("VerticalOrgImage", p));

		//	明文图像直方图
		p = ChaoticEncrypt::Image::HistFromImage(m_pImage);
		m_pAnalysisResult->insert(std::make_pair("OrgImageHist", p));

		//密文图像
		CImage *EnImage = m_pAnalysis->GetEnImage();
		m_pAnalysisResult->insert(std::make_pair("EncryptedImage", EnImage));

		//	密文图像水平方向相邻像素
		p = ChaoticEncrypt::Image::HorzRelative(EnImage);
		m_pAnalysisResult->insert(std::make_pair("HorizontalEncryptedImage", p));

		//	密文图像垂直方向相邻像素
		p = ChaoticEncrypt::Image::VertRelative(EnImage);
		m_pAnalysisResult->insert(std::make_pair("VerticalEncryptedImage", p));

		//	密文图像直方图
		p = ChaoticEncrypt::Image::HistFromImage(EnImage);
		m_pAnalysisResult->insert(std::make_pair("EncryptedImageHist", p));

		double EnImageEntropy = ChaoticEncrypt::Image::GrayImageEntropy(EnImage);

		//	Plain Image 图像信号的相关系数
		// 水平方向，垂直方向，对角线方向
		std::vector<double> && PlainImageCoef = ChaoticEncrypt::Image::CorrelationCoefficient(m_pImage);

		//	密文图像信号的相关系数
		// 水平方向，垂直方向，对角线方向
		std::vector<double> && EnImageCoef = ChaoticEncrypt::Image::CorrelationCoefficient(EnImage);

		// 密钥灵敏度NPCR和UACI
		std::vector<std::vector<double>> * KeySense = m_pAnalysis->KeySensitivity_NPCR_UACI();

		m_WrongKeyDnImage = m_pAnalysis->KeySensitivity_Image_HistImage();

		std::unordered_map<size_t, double> * EncryptedImageEntropy = m_pAnalysis->PureEncryptedImageEntropy();
		
	}
}


//  加密解密测试
void CMainFrame::OnEncryption()
{
	// TODO:  在此添加命令处理程序代码
	
	if (m_pImage == nullptr)
	{
		return;
	}
	if (m_pAnalysis == nullptr)
	{
		return;
	}
	if (m_pImage == nullptr)
	{
		return;
	}
	m_pProgCtrl->ShowWindow(TRUE);
	m_pProgCtrl->SetPos(0);

	
	CImage *tmpImage = nullptr;
	tmpImage = ChaoticEncrypt::Image::HistFromImage(m_pImage);

	if (m_pAnalysisResult == nullptr)
	{
		m_pAnalysisResult = new std::unordered_map<std::string, CImage*>;
	}
	m_pAnalysisResult->insert(std::make_pair(StrPlainHist, tmpImage));

	m_pProgCtrl->SetPos(10);
	
	CImage *CipherImage = m_pAnalysis->GetEnImage();
	m_pAnalysisResult->insert(std::make_pair(StrCipherImage, CipherImage));
	m_pProgCtrl->SetPos(20);

	tmpImage = ChaoticEncrypt::Image::HistFromImage(CipherImage);
	m_pAnalysisResult->insert(std::make_pair(StrCipherHist, tmpImage));
	m_pProgCtrl->SetPos(30);

	std::vector<CImage*> *tmpVec = ChaoticEncrypt::Image::ImageRelative(m_pImage);
	if (tmpVec != nullptr)
	{
		m_pAnalysisResult->insert(std::make_pair(StrPlainHorz, tmpVec->at(0)));
		m_pAnalysisResult->insert(std::make_pair(StrPlainVert, tmpVec->at(1)));
		m_pAnalysisResult->insert(std::make_pair(StrPlainDiag, tmpVec->at(2)));
		delete tmpVec;
		tmpVec = nullptr;
	}
	m_pProgCtrl->SetPos(60);

	tmpVec = ChaoticEncrypt::Image::ImageRelative(CipherImage);
	if (tmpVec != nullptr)
	{
		m_pAnalysisResult->insert(std::make_pair(StrCipherHorz, tmpVec->at(0)));
		m_pAnalysisResult->insert(std::make_pair(StrCipherVert, tmpVec->at(1)));
		m_pAnalysisResult->insert(std::make_pair(StrCipherDiag, tmpVec->at(2)));
		delete tmpVec;
		tmpVec = nullptr;
	}
	m_pProgCtrl->SetPos(90);

	CMainFrame *pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CChaoticImageEncryptionView *pView = dynamic_cast<CChaoticImageEncryptionView*>(pMainFrame->GetActiveView());
	if (pView)
	{
		pView->Invalidate();
	}
	m_pProgCtrl->SetPos(100);
	m_pProgCtrl->ShowWindow(FALSE);
	m_pProgCtrl->SetPos(0);

}

// 信息熵分析  对纯色图像的信息熵
void CMainFrame::OnImageEntropy()
{
	// TODO:  在此添加命令处理程序代码
	if (m_pAnalysis != nullptr)
	{

		CImage *CipherImage = m_pAnalysis->GetEnImage();
		if (CipherImage == nullptr)
		{
			return;
		}
		std::vector<size_t> &&Hist = ChaoticEncrypt::Image::StatisticsPixel(CipherImage);
		std::pair<decltype(Hist.begin()), decltype(Hist.end())> MaxMin = std::minmax_element(Hist.begin(), Hist.end());
		CImage *CipherHist = ChaoticEncrypt::Image::CreateImageFromData(&Hist[0], Hist.size(), 100, 400);
		//CImage *
		CDlgDisplay tmp(this);
		//tmp.SetWindowTextW(L"CipherImage");
		
		tmp.SetData(CipherHist, *MaxMin.second, *MaxMin.first);
		if (tmp.DoModal() == IDOK)
		{

		}
		else
		{
			TRACE0("DoModal IDCANCEL\n\n");
		}
		delete CipherImage;
		CipherImage = nullptr;

		delete CipherHist;
		CipherHist = nullptr;
		return;

		std::vector<double> *Result = m_pAnalysis->AllPureEncryptedImageEntropy();

		//std::string tmpFilePath = "C:\\Users\\Administrator\\Desktop\\a.txt";
		//ChaoticEncrypt::Image::SaveToFile(&(*Result)[0], Result->size(), tmpFilePath);
		delete Result;
		Result = nullptr;
	}
	
}


void CMainFrame::OnYangLiuAlgo()
{
	// TODO:  在此添加命令处理程序代码
	std::vector<double> Param{ 10, 8 / 3.0f, 16, -0.7, 0.01, 10000, 15 };
	std::vector<double> KeyValue{ 0.123, 0.879, 0.543, 0.9159, 0.173, 0.8731, 0.59301, 0.98591 };
	YangLiuAlgorithm *algo = new YangLiuAlgorithm;
	SetAnalysisParam(algo, Param, KeyValue);
}


void CMainFrame::OnWangXuAlgorithm()
{
	// TODO:  在此添加命令处理程序代码
	WangXuAlgorithm *algo = new WangXuAlgorithm;
	std::vector<double> Param;
	std::vector<double> KeyValue{ 0.2, 0.2, 0.2, 0.3, 10, 100 };
	SetAnalysisParam(algo, Param, KeyValue);
}

const CImage * CMainFrame::GetCurrentImage() const
{
	return m_pImage;
}

CImage ** CMainFrame::GetCurrentDisplayImage(size_t &Num) const
{
	Num = 0;
	Num += (m_pImage != nullptr) ? 1 : 0;
	if (m_pAnalysisResult != nullptr)
	{
		Num = Num + m_pAnalysisResult->size();
	}

	if (m_WrongKeyDnImage != nullptr)
	{
		Num = Num + m_WrongKeyDnImage->size();
	}
	if (Num == 0)
	{
		return nullptr;
	}
	CImage ** tmp = new CImage*[Num];
	size_t i = 0;
	tmp[i++] = m_pImage;
	if (m_pAnalysisResult != nullptr)
	{
		for (std::unordered_map<std::string, CImage*>::iterator iter = m_pAnalysisResult->begin();	\
			iter != m_pAnalysisResult->end(); ++iter)
		{
			tmp[i++] = iter->second;
		}
	}

	if (m_WrongKeyDnImage != nullptr)
	{
		for (std::unordered_map<double, std::pair<CImage*, CImage*>>::iterator iter = m_WrongKeyDnImage->begin();	\
			iter != m_WrongKeyDnImage->end(); ++iter)
		{
			tmp[i++] = iter->second.first;
			tmp[i++] = iter->second.second;
		}
	}
	
	return tmp;
}

void CMainFrame::OnUpdateIEOne(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_pImage == nullptr)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
	}

}


void CMainFrame::OnUpdateYangLiu(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_pImage == nullptr)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);

	}
}

void CMainFrame::OnUpdateWangXuAlgorithm(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_pImage == nullptr)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);

	}
}

// 加解密测试按钮
void CMainFrame::OnUpdateEncryption(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_pImage == nullptr)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);

	}
}



//BOOL CMainFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	TRACE2("nFlags = %u\tzDelta = %d\n\n", nFlags, zDelta);
//	TRACE2("pt.x = %u\tpt.y = %u\n\n", pt.x, pt.y);
//	size_t nCount = zDelta / WHEEL_DELTA;
//
//	return CFrameWndEx::OnMouseWheel(nFlags, zDelta, pt);
//}
