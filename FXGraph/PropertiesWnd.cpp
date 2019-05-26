
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "FXGraph.h"
#include "FXGraphView.h"
#include "FXObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	//for(int i=0; i<100; i++)
	//	m_Properties[i] = NULL;
}

CPropertiesWnd::~CPropertiesWnd()
{
	TracePrint(TRACE_LEVEL_1,"CPropertiesWnd::~CPropertiesWnd");
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// обработчики сообщений CResourceViewBar

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	m_wndObjectCombo.GetWindowRect(&rectCombo);

	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Создать поле со списком:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Не удалось создать поле со списком \"Свойства\" \n");
		return -1;      // не удалось создать
	}

//	m_wndObjectCombo.AddString(_T("Приложение"));
	m_wndObjectCombo.AddString(_T("Окно \"Свойства\""));
	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Не удалось создать сетку свойств\n");
		return -1;      // не удалось создать
	}

//	InitPropList(0);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Заблокирован */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* Заблокирован */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// Все команды будут перенаправлены через этот элемент управления, а не через родительскую рамку:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	TracePrint(TRACE_LEVEL_1,"CPropertiesWnd::OnProperties1");
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CFXGraphView* pView = (CFXGraphView*)pFrame->GetActiveView();
	TracePrint(TRACE_LEVEL_1,"Selected items=%d",pView->m_Selected.GetSize());
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: добавьте сюда код обработчика команд
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: добавьте сюда код обработчика команд обновления интерфейса пользователя
}

CMFCPropertyGridProperty* tmp=NULL;

//void CPropertiesWnd::InitPropList(int propList)
//{
//	SetPropListFont();
//
//	m_wndPropList.EnableHeaderCtrl(FALSE);
//	m_wndPropList.EnableDescriptionArea();
//	m_wndPropList.SetVSDotNetLook();
//	m_wndPropList.MarkModifiedProperties();
//	if (m_CurPropList != propList){
//		m_wndPropList.RemoveAll();
//		m_CurPropList = propList;
//
//		CMFCPropertyGridProperty* pGroupMain;
//		CMFCPropertyGridProperty* pGroupView;
//		CMFCPropertyGridProperty* pProp;
//		CMFCPropertyGridProperty* pPosition;
//		CMFCPropertyGridProperty* pSize;
//		CMFCPropertyGridProperty* pGroupPins;
//		switch(propList){
//			case 0:
//				for(int i=0;i<100;i++)
//					m_Properties[i] = NULL;
//				m_wndPropList.RedrawWindow();
//				break;
//			case PROPLIST_BLOCK:
//				// Список свойств блока
//
//				pGroupMain = new CMFCPropertyGridProperty(_T("Основные"));
//				pProp = new CMFCPropertyGridProperty(_T("Наименование"),_T(""),_T("Наименование блока"),PROP_NAME);
//				m_Properties[PROP_NAME] = pProp;
//				pGroupMain->AddSubItem(pProp);
//				m_wndPropList.AddProperty(pGroupMain);
//
//				pGroupView = new CMFCPropertyGridProperty(_T("Вид"));
//				pPosition = new CMFCPropertyGridProperty(_T("Положение блока"), 0, TRUE);
//				pProp = new CMFCPropertyGridProperty( _T("X"), (_variant_t) 0, _T("Указывает положение блока"),PROP_COORDX);
//				m_Properties[PROP_COORDX] = pProp;
//				pPosition->AddSubItem(pProp);
//
//				pProp = new CMFCPropertyGridProperty( _T("Y"), (_variant_t) 0, _T("Указывает положение блока"),PROP_COORDY);
//				m_Properties[PROP_COORDY] = pProp;
//				pPosition->AddSubItem(pProp);
//				pGroupView->AddSubItem(pPosition);
//
//				pSize = new CMFCPropertyGridProperty(_T("Размер блока"), 0, TRUE);
//
//				pProp = new CMFCPropertyGridProperty(_T("Высота"), (_variant_t)0, _T("Указывает высоту блока"),PROP_HEIGHT);
//				m_Properties[PROP_HEIGHT] = pProp;
//				pSize->AddSubItem(pProp);
//
//				pProp = new CMFCPropertyGridProperty( _T("Ширина"), (_variant_t) 0, _T("Указывает ширину блока"),PROP_WIDTH);
//				m_Properties[PROP_WIDTH] = pProp;
//				pSize->AddSubItem(pProp);
//
//				pGroupView->AddSubItem(pSize);
//				m_wndPropList.AddProperty(pGroupView);
//
//				break;
//			case PROPLIST_PIN:
//				pGroupMain = new CMFCPropertyGridProperty(_T("Основные"));
//				pProp = new CMFCPropertyGridProperty(_T("Наименование"),_T(""),_T("Наименование блока"),PROP_NAME);
//				m_Properties[PROP_NAME] = pProp;
//				pGroupMain->AddSubItem(pProp);
//
//				pProp = new CMFCPropertyGridProperty(_T("Функция"),_T(""),_T("Наименование функции блока"),PROP_FUNCNAME);
//				m_Properties[PROP_FUNCNAME] = pProp;
//				pGroupMain->AddSubItem(pProp);
//
//				pProp = new CMFCPropertyGridProperty(_T("Переменная"),_T(""),_T("Переменная связанная с данным пином"),PROP_PARAM);
//				pProp->AllowEdit(false);
//				m_Properties[PROP_PARAM] = pProp;
//				pGroupMain->AddSubItem(pProp);
//
//				pProp = new CMFCPropertyGridProperty(_T("Константа"),_T(""),_T("Значение пина контанта"),PROP_CONST);
//				pProp->AllowEdit(false);
//				pProp->AddOption(_T("Да"));
//				pProp->AddOption(_T("Нет"));
//				m_Properties[PROP_CONST] = pProp;
//				pGroupMain->AddSubItem(pProp);
//
//				pProp = new CMFCPropertyGridProperty(_T("Значение"),_T(""),_T("Значение пина"),PROP_VALUE);
//				m_Properties[PROP_VALUE] = pProp;
//				pGroupMain->AddSubItem(pProp);
//
//				m_wndPropList.AddProperty(pGroupMain);
//
//				pGroupView = new CMFCPropertyGridProperty(_T("Вид"));
//				pPosition = new CMFCPropertyGridProperty(_T("Положение блока"), 0, TRUE);
//				pProp = new CMFCPropertyGridProperty( _T("X"), (_variant_t) 0, _T("Указывает положение блока"),PROP_COORDX);
//				pProp->AllowEdit(0);
//				m_Properties[PROP_COORDX] = pProp;
//				pPosition->AddSubItem(pProp);
//
//				pProp = new CMFCPropertyGridProperty( _T("Y"), (_variant_t) 0, _T("Указывает положение блока"),PROP_COORDY);
//				pProp->AllowEdit(0);
//				m_Properties[PROP_COORDY] = pProp;
//				pPosition->AddSubItem(pProp);
//				pGroupView->AddSubItem(pPosition);
//				m_wndPropList.AddProperty(pGroupView);
//
//				break;
//			case PROPLIST_LINK:
//				pGroupMain = new CMFCPropertyGridProperty(_T("Основные"));
//				pProp = new CMFCPropertyGridProperty(_T("Наименование"),_T(""),_T("Наименование блока"),PROP_NAME);
//				m_Properties[PROP_NAME] = pProp;
//				pGroupMain->AddSubItem(pProp);
//				m_wndPropList.AddProperty(pGroupMain);
//
//				pGroupView = new CMFCPropertyGridProperty(_T("Вид"));
//				pPosition = new CMFCPropertyGridProperty(_T("Положение блока"), 0, TRUE);
//				pProp = new CMFCPropertyGridProperty( _T("X"), (_variant_t) 0, _T("Указывает положение блока"),PROP_COORDX);
//				m_Properties[PROP_COORDX] = pProp;
//				pPosition->AddSubItem(pProp);
//
//				pProp = new CMFCPropertyGridProperty( _T("Y"), (_variant_t) 0, _T("Указывает положение блока"),PROP_COORDY);
//				m_Properties[PROP_COORDY] = pProp;
//				pPosition->AddSubItem(pProp);
//				pGroupView->AddSubItem(pPosition);
//				m_wndPropList.AddProperty(pGroupView);
//				break;
//			case PROPLIST_COMMENT:
//				pGroupMain = new CMFCPropertyGridProperty(_T("Основные"));
//				pProp = new CMFCPropertyGridProperty(_T("Наименование"),_T(""),_T("Наименование блока"),PROP_NAME);
//				m_Properties[PROP_NAME] = pProp;
//				pGroupMain->AddSubItem(pProp);
//				m_wndPropList.AddProperty(pGroupMain);
//
//				pGroupView = new CMFCPropertyGridProperty(_T("Вид"));
//				pPosition = new CMFCPropertyGridProperty(_T("Положение блока"), 0, TRUE);
//				pProp = new CMFCPropertyGridProperty( _T("X"), (_variant_t) 0, _T("Указывает положение блока"),PROP_COORDX);
//				m_Properties[PROP_COORDX] = pProp;
//				pPosition->AddSubItem(pProp);
//
//				pProp = new CMFCPropertyGridProperty( _T("Y"), (_variant_t) 0, _T("Указывает положение блока"),PROP_COORDY);
//				m_Properties[PROP_COORDY] = pProp;
//				pPosition->AddSubItem(pProp);
//				pGroupView->AddSubItem(pPosition);
//				m_wndPropList.AddProperty(pGroupView);
//				break;
//
//		}
//	}
//	//CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Вид"));
//
//	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Трехмерный вид"), (_variant_t) false, _T("В окне используется обычный (не жирный) шрифт, а у элементов управления есть визуально трехмерная граница.")));
//
//	//CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("Граница"), _T("Диалоговое окно"), _T("Одно из значений: \"Нет\", \"Тонкая\", \"Изменяемая\" или \"Диалоговое окно\""));
//	//pProp->AddOption(_T("Нет"));
//	//pProp->AddOption(_T("Тонкая"));
//	//pProp->AddOption(_T("Изменяемая"));
//	//pProp->AddOption(_T("Диалоговое окно"));
//	//pProp->AllowEdit(FALSE);
//
//	//pGroup1->AddSubItem(pProp);
//	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Заголовок"), (_variant_t) _T("О программе"), _T("Указывает текст, который будет отображаться в строке заголовка окна")));
//
//	//m_wndPropList.AddProperty(pGroup1);
//
//	//CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("Размер окна"), 0, TRUE);
//
//	//pProp = new CMFCPropertyGridProperty(_T("Высота"), (_variant_t) 250l, _T("Указывает высоту окна"));
//	//pProp->EnableSpinControl(TRUE, 50, 300);
//	//pSize->AddSubItem(pProp);
//
//	//pProp = new CMFCPropertyGridProperty( _T("Ширина"), (_variant_t) 150l, _T("Указывает ширину окна"));
//	//pProp->EnableSpinControl(TRUE, 50, 200);
//	//pSize->AddSubItem(pProp);
//
//	//m_wndPropList.AddProperty(pSize);
//
//	//CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Шрифт"));
//
//	//LOGFONT lf;
//	//CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
//	//font->GetLogFont(&lf);
//
//	//lstrcpy(lf.lfFaceName, _T("Arial"));
//
//	//pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("Шрифт"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("Указывает шрифт окна по умолчанию")));
//	//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Использование системного шрифта"), (_variant_t) true, _T("Указывает, что в окне используется шрифт MS Shell Dlg")));
//
//	//m_wndPropList.AddProperty(pGroup2);
//
//	//CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("Разное"));
//	//pProp = new CMFCPropertyGridProperty(_T("(Имя)"), _T("Приложение"));
//	//pProp->Enable(FALSE);
//	//pGroup3->AddSubItem(pProp);
//
//	//CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("Цвет окна"), RGB(210, 192, 254), NULL, _T("Указывает цвет окна по умолчанию"));
//	//pColorProp->EnableOtherButton(_T("Другое..."));
//	//pColorProp->EnableAutomaticButton(_T("По умолчанию"), ::GetSysColor(COLOR_3DFACE));
//	//pGroup3->AddSubItem(pColorProp);
//
//	//static const TCHAR szFilter[] = _T("Файлы значков(*.ico)|*.ico|Все файлы(*.*)|*.*||");
//	//pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Значок"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Указывает значок окна")));
//
//	//pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Папка"), _T("c:\\")));
//
//	//m_wndPropList.AddProperty(pGroup3);
//
//	//CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("Иерархия"));
//
//	//CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("Первый подуровень"));
//	//pGroup4->AddSubItem(pGroup41);
//
//	//CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("Второй подуровень"));
//	//pGroup41->AddSubItem(pGroup411);
//
//	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Элемент 1"), (_variant_t) _T("Значение 1"), _T("Это описание")));
//	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Элемент 2"), (_variant_t) _T("Значение 2"), _T("Это описание")));
//	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Элемент 3"), (_variant_t) _T("Значение 3"), _T("Это описание")));
//
//	//pGroup4->Expand(FALSE);
////	m_wndPropList.AddProperty(pGroup4);
//}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}


void CPropertiesWnd::UpdateProperties(CFXObject* pObject)
{
	if (pObject == NULL){
		m_wndPropList.RemoveAll();
		TracePrint(TRACE_LEVEL_1,"CPropertiesWnd::UpdateProperties: Reset properties window");
		m_wndPropList.AdjustLayout();
		return;
	}
	
//	int propList = pObject->GetPropertyList();

//	InitPropList(propList);
	TracePrint(TRACE_LEVEL_1,"CPropertiesWnd::UpdateProperties: pObject fill properties");
	pObject->FillProperties(this);
}


void CPropertiesWnd::UpdateProperty(int nProperty, int v)
{
	TracePrint(TRACE_LEVEL_2,"CPropertiesWnd::UpdateProperty:");
	CMFCPropertyGridProperty* pProp = m_wndPropList.FindItemByData(nProperty);
	if (pProp){
		pProp->SetValue((variant_t)v);
	}
}
