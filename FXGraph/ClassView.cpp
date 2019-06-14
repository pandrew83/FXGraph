
#include "stdafx.h"
#include "MainFrm.h"
#include "ClassView.h"
#include "Resource.h"
#include "FXGraph.h"
#include "FXObject.h"

class CClassViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CClassView;

	DECLARE_SERIAL(CClassViewMenuButton)

public:
	CClassViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// Создание и удаление
//////////////////////////////////////////////////////////////////////

CClassView::CClassView()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
	m_bDragging = false;
	m_pDragDropImages = NULL;
}

CClassView::~CClassView()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
}

BEGIN_MESSAGE_MAP(CClassView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
//	ON_WM_LBUTTONDOWN()
//	ON_WM_MOUSEMOVE()
ON_COMMAND(ID_CLASSVIEWMENU_WEBHELP, &CClassView::OnClassviewmenuWebhelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// обработчики сообщений CClassView

int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Создание представлений:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndClassView.Create(dwViewStyle, rectDummy, this,2))
	{
		TRACE0("Не удалось создать представление классов\n");
		return -1;      // не удалось создать
	}
	m_wndClassView.m_bAllowDragDrop = true;
	// Загрузка изображений:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* Заблокирован */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// Все команды будут перенаправлены через этот элемент управления, а не через родительскую рамку:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CClassViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}
	
	// Введите некоторые данные статического представления в виде дерева (пустой код, ничего более)
	FillClassView();
	SetCapture();
	return 0;
}

void CClassView::OnSize(UINT nType, int cx, int cy)
{
	TracePrint(TRACE_LEVEL_2,__FUNCTION__);
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CClassView::InsertBlock(HTREEITEM hRoot, CString name, int data){
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	HTREEITEM hItem = m_wndClassView.InsertItem(name,hRoot,0);
	m_wndClassView.SetItemData(hItem,data);
}

void CClassView::FillClassView()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	HTREEITEM hClass;
	HTREEITEM hClass1;
	HTREEITEM hRoot = m_wndClassView.InsertItem(L"Блоки",0,0);
	m_wndClassView.SetItemState(hRoot,TVIS_BOLD,TVIS_BOLD);
	hClass = m_wndClassView.InsertItem(_T("Разное"),hRoot,0);
		InsertBlock(hClass,L"Комментарий",BLOCK_COMMENT);
		m_wndClassView.Expand(hClass,TVE_EXPAND);
	hClass = m_wndClassView.InsertItem(_T("Функциональные блоки"),hRoot,0);
		InsertBlock(hClass,_T("Функциональный блок"),BLOCK_FUNCTIONAL);
		m_wndClassView.Expand(hClass,TVE_EXPAND);
	hClass = m_wndClassView.InsertItem(_T("Математика"),hRoot,0);
		hClass1 = m_wndClassView.InsertItem(_T("Целочисленная"),hClass,0);
			InsertBlock(hClass1,_T("Сложение"),BLOCK_MATH_INT_ADD);
			InsertBlock(hClass1,_T("Вычитание"),BLOCK_MATH_INT_SUB);
			InsertBlock(hClass1,_T("Умножение"),BLOCK_MATH_INT_MUL);
			InsertBlock(hClass1,_T("Деление"),BLOCK_MATH_INT_DIV);
			InsertBlock(hClass1,_T("Остаток от деления"),BLOCK_MATH_INT_MOD);
			InsertBlock(hClass1,_T("Равно"),BLOCK_MATH_INT_EQUAL);
			InsertBlock(hClass1,_T("Больше"),BLOCK_MATH_INT_GREAT);
			InsertBlock(hClass1,_T("Больше равно"),BLOCK_MATH_INT_GREATEQUAL);
			InsertBlock(hClass1,_T("Меньше"),BLOCK_MATH_INT_LESS);
			InsertBlock(hClass1,_T("Меньше равно"),BLOCK_MATH_INT_LESSEQUAL);
			InsertBlock(hClass1,_T("Не равно"),BLOCK_MATH_INT_NOTEQUAL);
			InsertBlock(hClass1,_T("Модуль числа"),BLOCK_MATH_INT_ABS);
			m_wndClassView.Expand(hClass1,TVE_EXPAND);
		hClass1 = m_wndClassView.InsertItem(_T("Вещественная"),hClass,0);
			InsertBlock(hClass1,_T("Сложение"),BLOCK_MATH_FLOAT_ADD);
			InsertBlock(hClass1,_T("Вычитание"),BLOCK_MATH_FLOAT_SUB);
			InsertBlock(hClass1,_T("Умножение"),BLOCK_MATH_FLOAT_MUL);
			InsertBlock(hClass1,_T("Деление"),BLOCK_MATH_FLOAT_DIV);
			InsertBlock(hClass1,_T("Больше"),BLOCK_MATH_FLOAT_GREAT);
			InsertBlock(hClass1,_T("Больше равно"),BLOCK_MATH_FLOAT_GREATEQUAL);
			InsertBlock(hClass1,_T("Меньше"),BLOCK_MATH_FLOAT_LESS);
			InsertBlock(hClass1,_T("Меньше равно"),BLOCK_MATH_FLOAT_LESSEQUAL);
			InsertBlock(hClass1,_T("Равно"),BLOCK_MATH_FLOAT_EQUAL);
			InsertBlock(hClass1,_T("Не равно"),BLOCK_MATH_FLOAT_NOTEQUAL);
			InsertBlock(hClass1,_T("Модуль числа"),BLOCK_MATH_FLOAT_ABS);
			InsertBlock(hClass1,_T("Floor"),BLOCK_MATH_FLOAT_FLOOR);
			InsertBlock(hClass1,_T("Round"),BLOCK_MATH_FLOAT_ROUND);
			InsertBlock(hClass1,_T("Cos"),BLOCK_MATH_COS);
			InsertBlock(hClass1,_T("Sin"),BLOCK_MATH_SIN);
			InsertBlock(hClass1,_T("Tan"),BLOCK_MATH_TAN);
			InsertBlock(hClass1,_T("Sqrt"),BLOCK_MATH_SQRT);
			InsertBlock(hClass1,_T("Pow"),BLOCK_MATH_POW);
			InsertBlock(hClass1,_T("Log"),BLOCK_MATH_LOG);
			InsertBlock(hClass1,_T("Log10"),BLOCK_MATH_LOG10);
			InsertBlock(hClass1,_T("Acos"),BLOCK_MATH_ACOS);
			InsertBlock(hClass1,_T("Asin"),BLOCK_MATH_ASIN);
			InsertBlock(hClass1,_T("Atan"),BLOCK_MATH_ATAN);
			InsertBlock(hClass1,_T("Exp"),BLOCK_MATH_EXP);
			m_wndClassView.Expand(hClass1,TVE_EXPAND);
		hClass1 = m_wndClassView.InsertItem(_T("Битовая"),hClass,0);
			InsertBlock(hClass1,_T("Битовое И"),BLOCK_MATH_BITWISE_AND);
			InsertBlock(hClass1,_T("Битовое ИЛИ"),BLOCK_MATH_BITWISE_OR);
			InsertBlock(hClass1,_T("Битовое XOR"),BLOCK_MATH_BITWISE_XOR);
			InsertBlock(hClass1,_T("Битовое НЕ"),BLOCK_MATH_BITWISE_NOT);
			InsertBlock(hClass1,_T("Сдвиг влево"),BLOCK_MATH_BITWISE_SHIFT_LEFT);
			InsertBlock(hClass1,_T("Сдвиг вправо"),BLOCK_MATH_BITWISE_SHIFT_RIGHT);
			InsertBlock(hClass1,_T("Кодирование"),BLOCK_MATH_BITWISE_PACK);
			InsertBlock(hClass1,_T("Декодирование"),BLOCK_MATH_BITWISE_UNPACK);
			m_wndClassView.Expand(hClass1,TVE_EXPAND);
		hClass1 = m_wndClassView.InsertItem(_T("Преобразование типов"),hClass,0);
			InsertBlock(hClass1,_T("Вещественное к целому"),BLOCK_MATH_CAST_FLOAT_INT);
			InsertBlock(hClass1,_T("Целое к вещественному"),BLOCK_MATH_CAST_INT_FLOAT);
			m_wndClassView.Expand(hClass1,TVE_EXPAND);
	m_wndClassView.Expand(hClass,TVE_EXPAND);
	
	hClass = m_wndClassView.InsertItem(_T("Компараторы"),hRoot,0);
		InsertBlock(hClass,_T("Компаратор нижнего уровня"),BLOCK_COMPARATOR_DOWN);
		InsertBlock(hClass,_T("Компаратор верхнего уровня"),BLOCK_COMPARATOR_UP);
		m_wndClassView.Expand(hClass,TVE_EXPAND);

	hClass = m_wndClassView.InsertItem(_T("Логика"),hRoot,0);
		InsertBlock(hClass,_T("Логическое И"),BLOCK_LOGICAL_AND);
		InsertBlock(hClass,_T("Логическое ИЛИ"),BLOCK_LOGICAL_OR);
		InsertBlock(hClass,_T("Логическое НЕ"),BLOCK_LOGICAL_NOT);
		InsertBlock(hClass,_T("Логическое XOR"),BLOCK_LOGICAL_XOR);
		InsertBlock(hClass,_T("Восходящий фронт"),BLOCK_LOGICAL_RISING_EDGE);
		InsertBlock(hClass,_T("Нисходящий фронт"),BLOCK_LOGICAL_FALLING_EDGE);
		InsertBlock(hClass,_T("Фронты"),BLOCK_LOGICAL_FRONTS);
		m_wndClassView.Expand(hClass1, TVE_EXPAND);
		m_wndClassView.Expand(hClass,TVE_EXPAND);

	hClass = m_wndClassView.InsertItem(_T("Задержки"), hRoot, 0);
		InsertBlock(hClass, _T("Дребезг"), BLOCK_ANTIBOUNCE);
		InsertBlock(hClass, _T("Задержка включения"), BLOCK_DELAY_ON);
		InsertBlock(hClass, _T("Задержка выключения"), BLOCK_DELAY_OFF);
		m_wndClassView.Expand(hClass1, TVE_EXPAND);
		m_wndClassView.Expand(hClass, TVE_EXPAND);

	hClass = m_wndClassView.InsertItem(_T("Счетчики, триггеры"),hRoot,0);
		InsertBlock(hClass,_T("Счетчик"),BLOCK_COUNTER);
		hClass1 = m_wndClassView.InsertItem(_T("Триггеры"),hClass,0);
		InsertBlock(hClass1,_T("RS-триггер"),BLOCK_LOGICAL_TRIGGER_RS);
		InsertBlock(hClass1,_T("SR-триггер"),BLOCK_LOGICAL_TRIGGER_SR);
		InsertBlock(hClass1,_T("RS-триггер по передним фронтам"),BLOCK_LOGICAL_TRIGGER_RS_RE);
		m_wndClassView.Expand(hClass1,TVE_EXPAND);
		m_wndClassView.Expand(hClass,TVE_EXPAND);

	hClass = m_wndClassView.InsertItem(_T("Контроллеры"),hRoot,0);
		InsertBlock(hClass,_T("Контроллер NiMod-01"),BLOCK_CONTROLLER_NIMOD01);
		InsertBlock(hClass,_T("Модуль расширения NiMod-A01"),BLOCK_EXTENSION_NIMODA01);
		m_wndClassView.Expand(hClass,TVE_EXPAND);
	hClass = m_wndClassView.InsertItem(_T("Датчики"), hRoot, 0);
		hClass1 = m_wndClassView.InsertItem(_T("Термосопротивления 2-проводные"), hClass, 0);
			InsertBlock(hClass1, _T("М50"), BLOCK_SENSOR_TRD_2W_M50);
			InsertBlock(hClass1, _T("М100"), BLOCK_SENSOR_TRD_2W_M100);
			InsertBlock(hClass1, _T("P50"), BLOCK_SENSOR_TRD_2W_P50);
			InsertBlock(hClass1, _T("P100"), BLOCK_SENSOR_TRD_2W_P100);
			InsertBlock(hClass1, _T("Pt100"), BLOCK_SENSOR_TRD_2W_PT100);
			InsertBlock(hClass1, _T("Pt500"), BLOCK_SENSOR_TRD_2W_PT500);
			InsertBlock(hClass1, _T("Pt1000"), BLOCK_SENSOR_TRD_2W_PT1000);
			m_wndClassView.Expand(hClass1, TVE_EXPAND);
		hClass1 = m_wndClassView.InsertItem(_T("Термосопротивления 3-проводные"), hClass, 0);
			InsertBlock(hClass1, _T("М50"), BLOCK_SENSOR_TRD_3W_M50);
			InsertBlock(hClass1, _T("М100"), BLOCK_SENSOR_TRD_3W_M100);
			InsertBlock(hClass1, _T("P50"), BLOCK_SENSOR_TRD_3W_P50);
			InsertBlock(hClass1, _T("P100"), BLOCK_SENSOR_TRD_3W_P100);
			InsertBlock(hClass1, _T("Pt100"), BLOCK_SENSOR_TRD_3W_PT100);
			InsertBlock(hClass1, _T("Pt500"), BLOCK_SENSOR_TRD_3W_PT500);
			InsertBlock(hClass1, _T("Pt1000"), BLOCK_SENSOR_TRD_3W_PT1000);
			m_wndClassView.Expand(hClass1, TVE_EXPAND);
		hClass1 = m_wndClassView.InsertItem(_T("Термосопротивления 4-проводные"), hClass, 0);
			InsertBlock(hClass1, _T("М50"), BLOCK_SENSOR_TRD_4W_M50);
			InsertBlock(hClass1, _T("М100"), BLOCK_SENSOR_TRD_4W_M100);
			InsertBlock(hClass1, _T("P50"), BLOCK_SENSOR_TRD_4W_P50);
			InsertBlock(hClass1, _T("P100"), BLOCK_SENSOR_TRD_4W_P100);
			InsertBlock(hClass1, _T("Pt100"), BLOCK_SENSOR_TRD_4W_PT100);
			InsertBlock(hClass1, _T("Pt500"), BLOCK_SENSOR_TRD_4W_PT500);
			InsertBlock(hClass1, _T("Pt1000"), BLOCK_SENSOR_TRD_4W_PT1000);
			m_wndClassView.Expand(hClass1, TVE_EXPAND);
		hClass1 = m_wndClassView.InsertItem(_T("Прочие"), hRoot, 0);
			InsertBlock(hClass1, _T("Токовый 0-20мА, 4-20 мА"), BLOCK_TRANSFORM_CURRENT);
			InsertBlock(hClass1, _T("Линейное преобразование"), BLOCK_TRANSFORM_LINEAR);
			InsertBlock(hClass1, _T("Линейное преобразование с ограничением"), BLOCK_TRANSFORM_LINEAR_LIMITS);
			m_wndClassView.Expand(hClass1, TVE_EXPAND);
		m_wndClassView.Expand(hClass, TVE_EXPAND);
	m_wndClassView.Expand(hRoot, TVE_EXPAND);
	

	//HTREEITEM hRoot = m_wndClassView.InsertItem(_T("Классы FakeApp"), 0, 0);
	//m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	//HTREEITEM hClass = m_wndClassView.InsertItem(_T("CFakeAboutDlg"), 1, 1, hRoot);
	//m_wndClassView.InsertItem(_T("CFakeAboutDlg()"), 3, 3, hClass);

	//m_wndClassView.Expand(hRoot, TVE_EXPAND);

	//hClass = m_wndClassView.InsertItem(_T("CFakeApp"), 1, 1, hRoot);
	//m_wndClassView.InsertItem(_T("CFakeApp()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("InitInstance()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("OnAppAbout()"), 3, 3, hClass);

	//hClass = m_wndClassView.InsertItem(_T("CFakeAppDoc"), 1, 1, hRoot);
	//m_wndClassView.InsertItem(_T("CFakeAppDoc()"), 4, 4, hClass);
	//m_wndClassView.InsertItem(_T("~CFakeAppDoc()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("OnNewDocument()"), 3, 3, hClass);

	//hClass = m_wndClassView.InsertItem(_T("CFakeAppView"), 1, 1, hRoot);
	//m_wndClassView.InsertItem(_T("CFakeAppView()"), 4, 4, hClass);
	//m_wndClassView.InsertItem(_T("~CFakeAppView()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("GetDocument()"), 3, 3, hClass);
	//m_wndClassView.Expand(hClass, TVE_EXPAND);

	//hClass = m_wndClassView.InsertItem(_T("CFakeAppFrame"), 1, 1, hRoot);
	//m_wndClassView.InsertItem(_T("CFakeAppFrame()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("~CFakeAppFrame()"), 3, 3, hClass);
	//m_wndClassView.InsertItem(_T("m_wndMenuBar"), 6, 6, hClass);
	//m_wndClassView.InsertItem(_T("m_wndToolBar"), 6, 6, hClass);
	//m_wndClassView.InsertItem(_T("m_wndStatusBar"), 6, 6, hClass);

	//hClass = m_wndClassView.InsertItem(_T("Globals"), 2, 2, hRoot);
	//m_wndClassView.InsertItem(_T("theFakeApp"), 5, 5, hClass);
	//m_wndClassView.Expand(hClass, TVE_EXPAND);
}

void CClassView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Выберите нажатый элемент:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_CLASSMENU);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CClassView::AdjustLayout()
{
	TracePrint(TRACE_LEVEL_2,__FUNCTION__);
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndClassView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CClassView::PreTranslateMessage(MSG* pMsg)
{
	TracePrint(TRACE_LEVEL_2,__FUNCTION__);
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CClassView::OnSort(UINT id)
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate(1);
		m_wndToolBar.UpdateWindow();
	}
}

void CClassView::OnUpdateSort(CCmdUI* pCmdUI)
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CClassView::OnClassAddMemberFunction()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	AfxMessageBox(_T("Добавить функцию-член..."));
}

void CClassView::OnClassAddMemberVariable()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
}

void CClassView::OnClassDefinition()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
}

void CClassView::OnClassProperties()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
}

void CClassView::OnNewFolder()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	AfxMessageBox(_T("Создать папку..."));
}

void CClassView::OnPaint()
{
	TracePrint(TRACE_LEVEL_2,__FUNCTION__);
	CPaintDC dc(this); // контекст устройства для рисования

	CRect rectTree;
	m_wndClassView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CClassView::OnSetFocus(CWnd* pOldWnd)
{
	TracePrint(TRACE_LEVEL_2,__FUNCTION__);
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndClassView.SetFocus();
}

void CClassView::OnChangeVisualStyle()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	m_ClassViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TracePrint(TRACE_LEVEL_1,"Не удается загрузить точечный рисунок: %x\n", uiBmpId);
		
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ClassViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ClassViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndClassView.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* Заблокирован */);
}



HTREEITEM CClassView::GetCurSel(void)
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	return m_wndClassView.GetSelectedItem();
}


int CClassView::GetBlockID(HTREEITEM hItem)
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	return m_wndClassView.GetItemData(hItem);
}


void CClassView::OnClassviewmenuWebhelp()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	HTREEITEM hItem = GetCurSel();
	if (hItem){
		int id = GetBlockID(hItem);
		CString url = CFXObject::GetClassDescriptorByID(id);
		CString host = _T(WEBHELP_URL);
		host = host + "/doku.php?id=FXGraph:"+url;
		::ShellExecute(NULL,_T("open"),host,NULL,NULL,SW_SHOWNORMAL);
	}
}
