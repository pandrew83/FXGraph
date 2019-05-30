
// MainFrm.cpp : ���������� ������ CMainFrame
//

#include "stdafx.h"
#include "FXGraph.h"

#include "MainFrm.h"
#include "FXGraphDoc.h"
#include "FXGraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
//	ON_UPDATE_COMMAND_UI ( ID_INDICATOR_COORD,OnUpdateCoord)
ON_UPDATE_COMMAND_UI(ID_INDICATOR_TICKS, &CMainFrame::OnUpdateIndicatorTicks)
ON_COMMAND(ID_INDICATOR_TICKS, &CMainFrame::OnIndicatorTicks)
ON_COMMAND(ID_CLASSVIEWMENU_WEBHELP, &CMainFrame::OnClassviewmenuWebhelp)
ON_COMMAND(ID_DEBUG_START, &CMainFrame::OnDebugStart)
ON_WM_TIMER()
ON_COMMAND(ID_DEBUG_STOP, &CMainFrame::OnDebugStop)
ON_COMMAND(ID_DEBUG_RESTART, &CMainFrame::OnDebugRestart)
ON_COMMAND(ID_DEBUG_STEP_OVER, &CMainFrame::OnDebugStepOver)
ON_COMMAND(ID_DEBUG_STEP_INTO, &CMainFrame::OnDebugStepInto)
ON_UPDATE_COMMAND_UI(ID_DEBUG_START, &CMainFrame::OnUpdateDebugStart)
ON_UPDATE_COMMAND_UI(ID_DEBUG_STEP_INTO, &CMainFrame::OnUpdateDebugStepInto)
ON_UPDATE_COMMAND_UI(ID_DEBUG_STEP_OVER, &CMainFrame::OnUpdateDebugStepOver)
ON_UPDATE_COMMAND_UI(ID_DEBUG_STOP, &CMainFrame::OnUpdateDebugStop)
ON_COMMAND(ID_DEBUG_PAUSE, &CMainFrame::OnDebugPause)
ON_UPDATE_COMMAND_UI(ID_DEBUG_PAUSE, &CMainFrame::OnUpdateDebugPause)
ON_UPDATE_COMMAND_UI(ID_PROJECT_SCENARIO, &CMainFrame::OnUpdateProjectScenario)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_TICKS,
	ID_INDICATOR_COORD,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// ��������/����������� CMainFrame
//void CMainFrame::OnUpdateCoord(CCmdUI *pCmdUI)
//{
//    CString strStatus;
//
//    strStatus.Format(ID_INDICATOR_COORD, time);
//
//    m_wndStatusBar.SetPaneText(
//		m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIME),
//		strStatus );
//}
CMainFrame::CMainFrame()
	: m_pDebugCurDoc(NULL)
{
	TracePrint(TRACE_LEVEL_1,"CMainFrame::CMainFrame");

	// TODO: �������� ��� ������������� �����
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}

CMainFrame::~CMainFrame()
{
	TracePrint(TRACE_LEVEL_1,"CMainFrame::~CMainFrame");
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// ���������� ��������� ��������� � ����� �� ������ ����������� ��������
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ������ ��������� �����...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // ���������� �������� FALSE, ����� ����������� ������ \"�������\" � ������ ����� ������� �������
	mdiTabParams.m_bTabIcons = FALSE;    // ���������� �������� TRUE, ����� �������� ������ ���������� �� �������� MDI
	mdiTabParams.m_bAutoColor = TRUE;    // ���������� �������� FALSE, ����� ��������� �������������� ��������� ������ ������� MDI
	mdiTabParams.m_bDocumentMenu = TRUE; // �������� ���� ��������� �� ������ ������� ������� �������
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("�� ������� ������� ������ ����\n");
		return -1;      // �� ������� �������
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// �������������� ����������� ������ ���� �� ��������� 
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("�� ������� ������� ������ ������������\n");
		return -1;      // �� ������� �������
	}
	if (!m_wndToolBarDebug.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarDebug.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_DEBUG : IDR_MAINFRAME))
	{
		TRACE0("�� ������� ������� ������ ������������\n");
		return -1;      // �� ������� �������
	}

	if (!m_wndToolBarAlign.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarAlign.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_ALIGN : IDR_MAINFRAME))
	{
		TRACE0("�� ������� ������� ������ ������������\n");
		return -1;      // �� ������� �������
	}

	if (!m_wndToolBarGrid.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarGrid.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_GRID : IDR_MAINFRAME))
	{
		TRACE0("�� ������� ������� ������ ������������\n");
		return -1;      // �� ������� �������
	}

	if (!m_wndToolBarProject.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarProject.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_PROJECT : IDR_MAINFRAME))
	{
		TRACE0("�� ������� ������� ������ ������������\n");
		return -1;      // �� ������� �������
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// ��������� �������� � ����������������� �������� ������������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("�� ������� ������� ������ ���������\n");
		return -1;      // �� ������� �������
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(m_wndStatusBar.CommandToIndex(ID_INDICATOR_COORD),ID_INDICATOR_COORD,0,100);

	// TODO: ������� ��� ���� �����, ���� ������ ������������ � ������ ���� �� ������ ���� �������������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarDebug.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarAlign.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarGrid.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarProject.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);
	DockPane(&m_wndToolBarDebug);
	DockPane(&m_wndToolBarGrid);
	DockPane(&m_wndToolBarAlign);
	DockPane(&m_wndToolBarProject);

	// �������� ����� ������ ������������ ���� ������ Visual Studio 2005
	CDockingManager::SetDockingMode(DT_SMART);
	// �������� ����� ������ ��������������� ������� ������������ ���� ������ Visual Studio 2005
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ��������� ����������� �������� ���� (�� ����������� �� �����-���� ����������� ������� ������������):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ������� ������������ ����
	if (!CreateDockingWindows())
	{
		TRACE0("�� ������� ������� ������������ ����\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
	m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);


	// �������� ���������� ���� ������������ ���������� ������
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// �������� ������� ������ ���� ������� ������������ � ������������ ���� 
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// �������� ������� (Alt+��������������) ��������� ������� ������������
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// ��������� ����������� ���������������� ������� ������������
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// �������� �������������� ���� (��������� �������������� �������)
	// TODO: ���������� ���� �������� ������� ���, ����� ������ �������������� ���� ��������� �� ������� ���� ���� �������� �������.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	// ����������� ������� ����� ��������� � ����� ���������� � ��������� ����. ���
	// �������� �������� ������������� ������ �����, ��� ��� �� ������ ������������ ��� ���������.
	ModifyStyle(0, FWS_PREFIXTITLE);
	m_pDebugCurDoc = NULL;
	m_bDebugRunning = false;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �������� ����� Window ��� ����� ����������� ���������
	//  CREATESTRUCT cs

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// ������� ������������� �������
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("�� ������� ������� ���� \"������������� �������\"\n");
		return FALSE; // �� ������� �������
	}

	// ������� ������������� ������
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("�� ������� ������� ���� \"������������� ������\"\n");
		return FALSE; // �� ������� �������
	}

	// ������� ���� ������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("�� ������� ������� ���� \"�����\"\n");
		return FALSE; // �� ������� �������
	}

	// ������� ���� �������
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("�� ������� ������� ���� \"��������\"\n");
		return FALSE; // �� ������� �������
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

// ����������� CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// ����������� ��������� CMainFrame

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ����������� ����*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
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
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// ������� ����� �� ��������

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// �������� ������ ��������� ��� ���� ���������������� ������� ������������
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CMDIFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


void CMainFrame::UpdatePropertiesWindow(void)
{
//	m_wndProperties.SendMessage(WM_COMMAND,ID_PROPERTIES1);
	CMDIChildWnd* pFrame = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
	CFXGraphView* pView = (CFXGraphView*)pFrame->GetActiveView();
	if (pView){
		pView->UpdatePropertiesWnd();
	}
}


void CMainFrame::Log(CFXMsgType type, CString str)
{
	m_wndOutput.AddString(type,str);
}


BOOL CMainFrame::ValidateProperty(int nProperty, variant_t& value)
{
	CMDIChildWnd* pFrame = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
	CFXGraphView* pView = (CFXGraphView*)pFrame->GetActiveView();
	if (pView){
		CFXGraphDoc* pDoc = (CFXGraphDoc*)pView->GetDocument();
		bool valid = pView->OnUpdateProperty(nProperty,value);
		if (!valid)
			return false;
		pView->UpdatePropertiesWnd();
		// �������� �������� �����������
		// ����� ��������� ��������� �������� 
//		if (nProperty == PROP_CONST){
//			pView->UpdatePropertiesWnd();
////			bool v = !wcscmp(value.bstrVal,_T("True"));
//		}
//		if (nProperty == PROP_PARAM){
//			bool empty = value.bstrVal[0] == 0;
//			CFXPin* pPin = dynamic_cast<CFXPin*>(pView->m_pCur);
//			if (!empty){
//				pPin->m_bConst = false;
//			}
//		}
//		if (nProperty == PROP_VALUE){
//			CFXPin* pPin = dynamic_cast<CFXPin*>(pView->m_pCur);
//			bool valBool;
//			int valInt;
//			double valDbl;
//			if (pPin && pPin->m_Dir == Input && pPin->m_pParam){
//				switch(pPin->m_Type){
//					case Logical:
//						valBool	= !wcscmp(value.bstrVal,_T("True"));
//						pPin->m_pParam->m_Value = valBool;
//						break;
//					case Int:
//						valInt = _ttoi(value.bstrVal);
//						pPin->m_pParam->m_Value = valInt;
//						break;
//					case Float:
//						valDbl = _ttof(value.bstrVal);
//						pPin->m_pParam->m_Value = valDbl;
//						break;
//				}
//				pDoc->OnParameterUpdated(NULL);
//			}
//		}
//		pView->Invalidate(0);
		return valid;
	}
	else 
		return false;
}


void CMainFrame::OnUpdateIndicatorTicks(CCmdUI *pCmdUI)
{
	CMDIChildWnd* pFrame = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
	if (!pFrame)
		return;
	CFXGraphView* pView = (CFXGraphView*)pFrame->GetActiveView();
	if (pView){
		CFXGraphDoc* pDoc = (CFXGraphDoc*)pView->GetDocument();
		if (pDoc){
			CString str;
			if (pDoc->m_bDebug)
				str.Format(_T("Ticks: %d"),pDoc->m_SysTick);
			else
				str = _T("");
			m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_TICKS),str );

		}
	}
}


void CMainFrame::OnIndicatorTicks()
{
	// TODO: �������� ���� ��� ����������� ������
}


void CMainFrame::OnClassviewmenuWebhelp()
{
	// TODO: �������� ���� ��� ����������� ������
}

	
void CMainFrame::OnDebugStart()
{
	TracePrint(TRACE_LEVEL_1,"CMainFrame::OnDebugStart");
	if (!m_pDebugCurDoc){
		CFXGraphDoc* pDoc = GetCurDoc();
		if (pDoc){
			m_pDebugCurDoc = pDoc;
			if (!m_pDebugCurDoc->m_bDebug){
				m_pDebugCurDoc->DebugStart();
			}
			if (!m_pDebugCurDoc->m_bDebug){
				m_pDebugCurDoc = NULL;
				return;
			}
		}
	}
//	m_DataCollector.Initialize();
	m_bDebugRunning = true;
	m_pDebugCurDoc->DebugRun();
	SetTimer(1,m_pDebugCurDoc->m_DebugTimer,0);
}

//
//void CMainFrame::StartDebug(CFXGraphDoc* pDoc)
//{
//}


CFXGraphDoc* CMainFrame::GetCurDoc(void)
{
	TracePrint(TRACE_LEVEL_2,"CMainFrame::GetCurDoc");
	CMDIChildWnd* pFrame = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
	if (!pFrame)
		return NULL;
	CFXGraphView* pView = (CFXGraphView*)pFrame->GetActiveView();
	if (!pView)
		return NULL;
	CFXGraphDoc* pDoc = (CFXGraphDoc*)pView->GetDocument();
	return pDoc;
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	TracePrint(TRACE_LEVEL_1,"CMainFrame::OnTimer");
	if (m_pDebugCurDoc) {
		m_pDebugCurDoc->DebugRun();
	}
//	m_pDebugCurDoc->UpdateAllViews(NULL);
	CMDIFrameWndEx::OnTimer(nIDEvent);
}


void CMainFrame::OnDebugStop()
{
	TracePrint(TRACE_LEVEL_1,"CMainFrame::OnDebugStop");
	if (m_pDebugCurDoc){
		KillTimer(1);
		m_pDebugCurDoc->DebugStop();
		m_pDebugCurDoc = NULL;
		m_bDebugRunning = false;
//		m_SysTick = 0;
//		UpdateAllViews(NULL);

//		m_DataCollector.Excel(_T("asd.xls"));
	}

	// TODO: �������� ���� ��� ����������� ������
}


void CMainFrame::OnDebugBreakPoint(CFXGraphDoc* pDoc){
	m_bDebugRunning = false;
	KillTimer(1);
}


void CMainFrame::OnDebugRestart(){
	TracePrint(TRACE_LEVEL_1,"CMainFrame::OnDebugRestart");
	if (m_pDebugCurDoc && m_pDebugCurDoc->m_bDebug){
		m_pDebugCurDoc->DebugStart();
	}
//	 TODO: �������� ���� ��� ����������� ������
}


void CMainFrame::OnDebugStepOver(){
	TracePrint(TRACE_LEVEL_1,"CMainFrame::OnDebugStepOver");
	if (m_pDebugCurDoc && m_pDebugCurDoc->m_bDebug){
		m_pDebugCurDoc->DebugStepOver();
	}
//		do {
//			if (!m_pDebugCur->Calc()){
//				m_bDebug = false;
//				Log(Debug,_T("������ ������� �����"));
//				return;
//			}
//			m_pDebugCur->UpdateConnectedPins();
//			m_pDebugCur = m_pDebugCur->m_pNextBlock;
//			if (!m_pDebugCur){
//				// �������� ����� �������
//				// ��������� �� ������
//				// �������� ������� �������� �� ������ �������
//				OnDebugCycleEnd();
//			}
//		}
//		while (!m_pDebugCur->m_bCalc);
//		UpdateAllViews(NULL);
//	}
//	// TODO: �������� ���� ��� ����������� ������
}


void CMainFrame::OnDebugStepInto()
{
	TracePrint(TRACE_LEVEL_1,"CMainFrame::OnDebugStepInto");
	if (m_pDebugCurDoc && m_pDebugCurDoc->m_bDebug){
		m_pDebugCurDoc->DebugStep();
	}
}


void CMainFrame::OnUpdateDebugStart(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetCurDoc() && !m_bDebugRunning);
	// TODO: �������� ���� ��� ����������� �� ���������� ������
}


void CMainFrame::OnUpdateDebugStepInto(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pDebugCurDoc!=NULL && !m_bDebugRunning);
}


void CMainFrame::OnUpdateDebugStepOver(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pDebugCurDoc!=NULL && !m_bDebugRunning);
}


void CMainFrame::OnUpdateDebugStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pDebugCurDoc!=NULL);
}


void CMainFrame::OnDebugPause()
{
	TracePrint(TRACE_LEVEL_1,"CMainFrame::OnDebugPause");
	if (m_pDebugCurDoc && m_pDebugCurDoc->m_bDebug && m_bDebugRunning){
		KillTimer(1);
		m_bDebugRunning = false;
		m_pDebugCurDoc->DebugPause();
	}
}


void CMainFrame::OnUpdateDebugPause(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pDebugCurDoc!=NULL && m_bDebugRunning);
	// TODO: �������� ���� ��� ����������� �� ���������� ������
}


void CMainFrame::OnUpdateProjectScenario(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetCurDoc() && m_pDebugCurDoc == NULL);
	// TODO: �������� ���� ��� ����������� �� ���������� ������
}


void CMainFrame::OnDebugEndCycle(CFXGraphDoc* pDoc)
{
//	m_DataCollector.Collect(pDoc->m_SysTick, pDoc->m_pBlock);
	// TODO: �������� ���� ��� ����������.
}
