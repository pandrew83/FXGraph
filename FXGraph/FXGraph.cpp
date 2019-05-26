
// FXGraph.cpp : ���������� ��������� ������� ��� ����������.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "FXGraph.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "FXGraphDoc.h"
#include "FXGraphView.h"
#include "FXObject.h"
#include "GridDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define TRACE_LEVEL TRACE_LEVEL_1

void FXGRaphTerminate(){

}

void TracePrint(int level, const char* format,...){
	if (level & TRACE_LEVEL){
		va_list args;
		va_start(args,format);
		char str[1024];
		char eol[10];
		eol[0]='\n';
		eol[1]=0;
		vsprintf(str,format,args);
		va_end(args);
		strcat(str,eol);
		TRACE(str);
	}		
}
// CFXGraphApp

BEGIN_MESSAGE_MAP(CFXGraphApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CFXGraphApp::OnAppAbout)
	// ����������� ������� �� ������ � ������� ����������
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ����������� ������� ��������� ������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_GRID, &CFXGraphApp::OnGrid)
//	ON_COMMAND(ID_CLASSVIEWMENU_WEBHELP, &CFXGraphApp::OnClassviewmenuWebhelp)
END_MESSAGE_MAP()


// �������� CFXGraphApp

CFXGraphApp::CFXGraphApp()
	: m_GridStep(0)
	, m_GridState(false)
	, m_GridStyle(0)
{
	m_bHiColorIcons = TRUE;

	// ��������� ���������� ������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���� ���������� ��������� � ���������� ����� Common Language Runtime (/clr):
	//     1) ���� �������������� �������� ��������� ��� ���������� ��������� ������ ���������� ������������.
	//     2) � ����� ������� ��� ���������� ���������� �������� ������ �� System.Windows.Forms.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: �������� ���� ������ �������������� ���������� ������� ����������� ��������������; �������������
	// ������ ��� ������: �����������.�����������.����������.���������������
	SetAppID(_T("FXGraph.AppID.NoVersion"));

	// TODO: �������� ��� ��������,
	// ��������� ���� ������ ��� ������������� � InitInstance
}

// ������������ ������ CFXGraphApp

CFXGraphApp theApp;


// ������������� CFXGraphApp

BOOL CFXGraphApp::InitInstance()
{
	// InitCommonControlsEx() ��������� ��� Windows XP, ���� ��������
	// ���������� ���������� ComCtl32.dll ������ 6 ��� ����� ������� ������ ��� ���������
	// ������ �����������. � ��������� ������ ����� ��������� ���� ��� �������� ������ ����.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �������� ���� �������� ��� ��������� ���� ����� ������� ����������, ������� ���������� ������������
	// � ����� ����������.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ������������� ��������� OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// ��� ������������� �������� ���������� RichEdit ��������� ����� AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ����������� �������������
	// ���� ��� ����������� �� ������������ � ���������� ��������� ������
	// ��������� ������������ �����, ���������� ������� �� ����������
	// ���������� ��������� �������������, ������� �� ���������
	// �������� ������ �������, � ������� �������� ���������
	// TODO: ������� �������� ��� ������ �� ���-������ ����������,
	// �������� �� �������� �����������
	SetRegistryKey(_T("FXGraph"));
	m_GridState = (bool)GetProfileInt(_T("Settings"),_T("GridState"),0);
	m_GridStep = GetProfileInt(_T("Settings"),_T("GridStep"),5);
	m_GridStyle = GetProfileInt(_T("Settings"),_T("GridStyle"),0);
	m_GridBind = (bool)GetProfileInt(_T("Settings"),_T("GridBind"),0);
	int r = GetProfileInt(_T("Settings"),_T("GridColorR"),0);
	int g = GetProfileInt(_T("Settings"),_T("GridColorG"),0);
	int b = GetProfileInt(_T("Settings"),_T("GridColorB"),0);
	m_GridColor = RGB(r,g,b);
	LoadStdProfileSettings(4);  // ��������� ����������� ��������� INI-����� (������� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ��������������� ������� ���������� ����������. ������� ����������
	//  ��������� � ���� ���������� ����� �����������, ������ ����� � ���������������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_FXGraphTYPE,
		RUNTIME_CLASS(CFXGraphDoc),
		RUNTIME_CLASS(CChildFrame), // ������������� �������� ����� MDI
		RUNTIME_CLASS(CFXGraphView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	//pDocTemplate = new CMultiDocTemplate(IDR_FXGraphTYPE,
	//	RUNTIME_CLASS(CFXGraphDoc),
	//	RUNTIME_CLASS(CChildFrame),
	//	RUNTIME_CLASS(CFXGraphViewScenario));
	//AddDocTemplate(pDocTemplate);
	// �������� ������� ���� ����� MDI
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// ����� DragAcceptFiles ������ ��� ������� ��������
	//  � ���������� MDI ��� ������ ��������� ����� ����� ������� m_pMainWnd
	// �������� �������� ��������������
	m_pMainWnd->DragAcceptFiles();

	// �������������� ������ ��������� ������ �� ����������� ������� ��������, DDE, �������� ������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �������� �������� ���������� DDE
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// ������� ���������������, ��������� � ��������� ������. �������� FALSE ����� ����������, ����
	// ���������� ���� �������� � ���������� /RegServer, /Register, /Unregserver ��� /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// ������� ���� ���� ����������������, ������� ���������� � �������� ���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CFXGraphApp::ExitInstance()
{
	//TODO: ����������� �������������� �������, ������� ����� ���� ���������
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// ����������� ��������� CFXGraphApp


// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ������ ����������� ����
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ������� ���������� ��� ������� �������
void CFXGraphApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CFXGraphApp ��������� ������� �������� � ����������

void CFXGraphApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
	bNameValid = strName.LoadString(IDS_MENU_BLOCK);
	GetContextMenuManager()->AddMenu(strName, IDR_BLOCK);
	bNameValid = strName.LoadStringW(IDS_MENU_PIN);
	GetContextMenuManager()->AddMenu(strName, IDR_PIN);
	bNameValid = strName.LoadStringW(IDS_MENU_LINK);
	GetContextMenuManager()->AddMenu(strName, IDR_LINK);

	
}

void CFXGraphApp::LoadCustomState()
{
}

void CFXGraphApp::SaveCustomState()
{
}

// ����������� ��������� CFXGraphApp





void CFXGraphApp::OnGrid()
{
	CGridDlg dlg;
	dlg.m_Step = m_GridStep;
	dlg.m_Grid_On = m_GridState;
	dlg.m_GridStyle = m_GridStyle;
	dlg.m_GridBind = m_GridBind;
	dlg.m_GridColor.SetColor(m_GridColor);
	if (dlg.DoModal() == IDOK){
		m_GridStep = dlg.m_Step;
		m_GridState = dlg.m_Grid_On;
		m_GridStyle = dlg.m_GridStyle;
		m_GridBind = dlg.m_GridBind;
		m_GridColor = dlg.m_GridColor.GetColor();
		WriteProfileInt(_T("Settings"),_T("GridState"),m_GridState);
		WriteProfileInt(_T("Settings"),_T("GridStyle"),m_GridStyle);
		WriteProfileInt(_T("Settings"),_T("GridStep"),m_GridStep);
		WriteProfileInt(_T("Settings"),_T("GridBind"),m_GridBind);
		WriteProfileInt(_T("Settings"),_T("GridColorR"),GetRValue(m_GridColor));
		WriteProfileInt(_T("Settings"),_T("GridColorG"),GetGValue(m_GridColor));
		WriteProfileInt(_T("Settings"),_T("GridColorB"),GetBValue(m_GridColor));
		CMainFrame* pMainFrame = (CMainFrame*)m_pMainWnd;
		CView* pView = pMainFrame->GetActiveFrame()->GetActiveView();
		if (pView != NULL)
			pView->Invalidate(0);
	}
}



int CFXGraphApp::Run()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphApp:Run");
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	try{
		return CWinAppEx::Run();
	}
	catch(CFXException &ex){
		TracePrint(TRACE_LEVEL_1,"CFXGraphApp:Run: Exception");
	}
	catch(CException &ex){
		TracePrint(TRACE_LEVEL_1,"CFXGraphApp:Run: Exception");
	}
	catch(CException* pEx){
		TracePrint(TRACE_LEVEL_1,"CFXGraphApp:Run: Exception");
	}
	catch(...){
		TracePrint(TRACE_LEVEL_1,"Unknown exception");
	}
	return CWinApp::Run();
}
