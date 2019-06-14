
// MainFrm.cpp : реализация класса CMainFrame
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

// создание/уничтожение CMainFrame
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
	// установите наглядный диспетчер и стиль на основе постоянного значения
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // другие доступные стили...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // установите значение FALSE, чтобы расположить кнопку \"Закрыть\" в правой части области вкладки
	mdiTabParams.m_bTabIcons = FALSE;    // установите значение TRUE, чтобы включить значки документов на вкладках MDI
	mdiTabParams.m_bAutoColor = TRUE;    // установите значение FALSE, чтобы отключить автоматическое выделение цветом вкладок MDI
	mdiTabParams.m_bDocumentMenu = TRUE; // включить меню документа на правой границе области вкладки
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Не удалось создать строку меню\n");
		return -1;      // не удалось создать
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// предотвращение фокусировки строки меню на активации 
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Не удалось создать панель инструментов\n");
		return -1;      // не удалось создать
	}
	if (!m_wndToolBarDebug.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarDebug.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_DEBUG : IDR_MAINFRAME))
	{
		TRACE0("Не удалось создать панель инструментов\n");
		return -1;      // не удалось создать
	}

	if (!m_wndToolBarAlign.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarAlign.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_ALIGN : IDR_MAINFRAME))
	{
		TRACE0("Не удалось создать панель инструментов\n");
		return -1;      // не удалось создать
	}

	if (!m_wndToolBarGrid.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarGrid.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_GRID : IDR_MAINFRAME))
	{
		TRACE0("Не удалось создать панель инструментов\n");
		return -1;      // не удалось создать
	}

	if (!m_wndToolBarProject.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarProject.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_PROJECT : IDR_MAINFRAME))
	{
		TRACE0("Не удалось создать панель инструментов\n");
		return -1;      // не удалось создать
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Разрешить операции с пользовательскими панелями инструментов:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Не удалось создать строку состояния\n");
		return -1;      // не удалось создать
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(m_wndStatusBar.CommandToIndex(ID_INDICATOR_COORD),ID_INDICATOR_COORD,0,100);

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

	// включить режим работы закрепляемых окон стилей Visual Studio 2005
	CDockingManager::SetDockingMode(DT_SMART);
	// включить режим работы автоматического скрытия закрепляемых окон стилей Visual Studio 2005
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Загрузить изображение элемента меню (не размещенное на каких-либо стандартных панелях инструментов):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// создать закрепляемые окна
	if (!CreateDockingWindows())
	{
		TRACE0("Не удалось создать закрепляемые окна\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndGraphView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	DockPane(&m_wndGraphView);
	CDockablePane* pTabbedBar = NULL;
	m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
//	m_wndClassView.AttachToTabWnd(&m_wndGraphView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);


	// Включить диалоговое окно расширенного управления окнами
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// Включить функцию замены меню панелей инструментов и закрепляемых окон 
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// включить быструю (Alt+перетаскивание) настройку панелей инструментов
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// загрузить изображения пользовательских панелей инструментов
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

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

	// Переключите порядок имени документа и имени приложения в заголовке окна. Это
	// повышает удобство использования панели задач, так как на эскизе отображается имя документа.
	ModifyStyle(0, FWS_PREFIXTITLE);
	m_pDebugCurDoc = NULL;
	m_bDebugRunning = false;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// Создать представление классов
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Не удалось создать окно \"Представление классов\"\n");
		return FALSE; // не удалось создать
	}

	// Создать представление файлов
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Не удалось создать окно \"Представление Параметров\"\n");
		return FALSE; // не удалось создать
	}
	// Создать представление графиков
	CString strGraphView;
	bNameValid = strGraphView.LoadStringW(IDS_GRAPH_VIEW);
	ASSERT(bNameValid);
	if (!m_wndGraphView.Create(strGraphView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_GRAPHVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI)) {
		TRACE0("Не удалось создать окно \"Представление графиков\"\n");
		return FALSE;
	}
	// Создать окно вывода
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Не удалось создать окно \"Вывод\"\n");
		return FALSE; // не удалось создать
	}

	// Создать окно свойств
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Не удалось создать окно \"Свойства\"\n");
		return FALSE; // не удалось создать
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

	HICON hGraphicViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_GRAPH_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndGraphView.SetIcon(hGraphicViewIcon, FALSE);
	UpdateMDITabbedBarsIcons();
}

// диагностика CMainFrame

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


// обработчики сообщений CMainFrame

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* сканировать меню*/);
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
	// базовый класс не работает

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// включить кнопку настройки для всех пользовательских панелей инструментов
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
}


void CMainFrame::OnClassviewmenuWebhelp()
{
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
	m_bDebugRunning = true;
	m_pDebugCurDoc->DebugRun();
	SetTimer(1,m_pDebugCurDoc->m_DebugTimer,0);
}

CFXGraphDoc* CMainFrame::GetCurDoc(void)
{
	TracePrint(TRACE_LEVEL_2,"CMainFrame::GetCurDoc");
	//CMDIChildWnd* pFrame = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
	//if (!pFrame)
	//	return NULL;
	//CFXGraphView* pView = (CFXGraphView*)pFrame->GetActiveView();
	//if (!pView)
	//	return NULL;
	//CFXGraphDoc* pDoc = (CFXGraphDoc*)pView->GetDocument();
	//return pDoc;
	return m_pCurDoc;
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	TracePrint(TRACE_LEVEL_1,"CMainFrame::OnTimer");
	if (m_pDebugCurDoc) {
		m_pDebugCurDoc->DebugRun();
	}
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
	}

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
}


void CMainFrame::OnDebugStepOver(){
	TracePrint(TRACE_LEVEL_1,"CMainFrame::OnDebugStepOver");
	if (m_pDebugCurDoc && m_pDebugCurDoc->m_bDebug){
		m_pDebugCurDoc->DebugStepOver();
	}
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
}


void CMainFrame::OnUpdateProjectScenario(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetCurDoc() && m_pDebugCurDoc == NULL);
}


void CMainFrame::OnDebugEndCycle(CFXGraphDoc* pDoc)
{
}


void CMainFrame::OnActiveDocument(CFXGraphDoc* pDoc)
{
	if (m_pCurDoc != pDoc) {
		// TODO: Need to update child windows
		m_wndFileView.UpdateView(pDoc);
		m_wndGraphView.UpdateView(pDoc);
	}
	m_pCurDoc = pDoc;
}
