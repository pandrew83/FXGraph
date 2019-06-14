// CGraphView.cpp: файл реализации
//


#include "stdafx.h"
#include "FXGraph.h"
#include "CGraphView.h"
#include "ViewTree.h"
#include "FXGraphDoc.h"
#include "CGraphicDlg.h"
#include "MainFrm.h"
#include "CFXGraphicVariable.h"
#include "CGraphPinDlg.h"
#include "CFXGraphViewGraphic.h"
// CGraphView

IMPLEMENT_DYNAMIC(CGraphView, CDockablePane)

CGraphView::CGraphView()
{

}

CGraphView::~CGraphView()
{
}

void CGraphView::UpdateView(CFXGraphDoc* pDoc)
{
	TracePrint(TRACE_LEVEL_2, "CGraphView::UpdateView");
	if (!pDoc) {
		TracePrint(TRACE_LEVEL_2, "CGraphView::UpdateView No document");
		m_wndGraphView.DeleteAllItems();
//		m_pCurDoc = NULL;
		return;
	}
//	m_pCurDoc = pDoc;
	m_wndGraphView.DeleteAllItems();
	HTREEITEM hRoot = m_wndGraphView.InsertItem(_T("Графики"), 0, 0);
	m_wndGraphView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	POSITION pos = pDoc->m_Graphs.GetHeadPosition();
	while (pos) {
		CFXGraphic* p = pDoc->m_Graphs.GetNext(pos);
		HTREEITEM hGraphic = m_wndGraphView.InsertItem(p->GetTitle(), hRoot);
		m_wndGraphView.SetItemData(hGraphic, (DWORD_PTR)p);
		POSITION pos1 = p->GetFirstVariable();
		while (pos1) {
			CFXGraphicVariable* pVar = p->GetNextVariable(pos1);
			HTREEITEM hVar = m_wndGraphView.InsertItem(pVar->m_Name,hGraphic);
			m_wndGraphView.SetItemData(hVar, (DWORD_PTR)pVar);
		}
		m_wndGraphView.Expand(hGraphic, TVE_EXPAND);
	}
	m_wndGraphView.Expand(hRoot, TVE_EXPAND);
	return;
}


void CGraphView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndGraphView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}


BEGIN_MESSAGE_MAP(CGraphView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_GRAPH_ADD, &CGraphView::OnGraphAdd)
	ON_COMMAND(ID_GRAPH_RENAME, &CGraphView::OnGraphRename)
	ON_COMMAND(ID_GRAPH_OPEN, &CGraphView::OnGraphOpen)
	ON_COMMAND(ID_GRAPH_REMOVE, &CGraphView::OnGraphRemove)
	ON_COMMAND(ID_GRAPH_PIN_PROPERTIES, &CGraphView::OnGraphPinProperties)
	ON_COMMAND(ID_GRAPH_PIN_REMOVE, &CGraphView::OnGraphPinRemove)
//	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// Обработчики сообщений CGraphView




int CGraphView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndGraphView.Create(dwViewStyle, rectDummy, this, 3))
	{
		TRACE0("Не удалось создать представление классов\n");
		return -1;      // не удалось создать
	}
	m_wndGraphView.m_bAllowDragDrop = false;

	// Загрузка изображений:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* Заблокирован */);
	return 0;
}


void CGraphView::OnSize(UINT nType, int cx, int cy)
{
	TracePrint(TRACE_LEVEL_2, __FUNCTION__);
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CGraphView::OnChangeVisualStyle()
{
	TracePrint(TRACE_LEVEL_1, __FUNCTION__);
	m_GraphViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TracePrint(TRACE_LEVEL_1, "Не удается загрузить точечный рисунок: %x\n", uiBmpId);

		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_GraphViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_GraphViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndGraphView.SetImageList(&m_GraphViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* Заблокирован */);
}


void CGraphView::OnPaint()
{
	TracePrint(TRACE_LEVEL_2, __FUNCTION__);
	CPaintDC dc(this); // контекст устройства для рисования

	CRect rectTree;
	m_wndGraphView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}


void CGraphView::OnSetFocus(CWnd* pOldWnd)
{
	TracePrint(TRACE_LEVEL_2, __FUNCTION__);
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndGraphView.SetFocus();
}

void CGraphView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	TracePrint(TRACE_LEVEL_1, __FUNCTION__);
	CTreeCtrl* pWndTree = (CTreeCtrl*)& m_wndGraphView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}
	HTREEITEM hTreeItem;
	if (point != CPoint(-1, -1))
	{
		// Выберите нажатый элемент:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}
	else
		return;

	pWndTree->SetFocus();
	CMenu menu;
	int level = m_wndGraphView.GetItemLevel(hTreeItem);
	if (level == 3)
		menu.LoadMenu(IDR_GRAPHPINMENU);
	else
		menu.LoadMenu(IDR_GRAPHMENU);

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


void CGraphView::OnGraphAdd()
{
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CFXGraphDoc* pDoc = pMainFrame->GetCurDoc();
	if (pDoc) {
		CGraphicDlg dlg;
		if (dlg.DoModal() == IDOK) {
			pDoc->AddGraphic(dlg.m_Title);
			UpdateView(pDoc);
		}
	}
}


void CGraphView::OnGraphRename()
{
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CFXGraphDoc* pDoc = pMainFrame->GetCurDoc();
	if (pDoc) {
		HTREEITEM hItem = m_wndGraphView.GetSelectedItem();
		CFXGraphic* pGraphic = (CFXGraphic*)m_wndGraphView.GetItemData(hItem);
		CGraphicDlg dlg;
		dlg.m_Title = pGraphic->GetTitle();
		if (dlg.DoModal() == IDOK) {
			pGraphic->SetTitle(dlg.m_Title);
			UpdateView(pDoc);
		}
	}
}


void CGraphView::OnGraphOpen()
{ 
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CFXGraphDoc* pDoc = pMainFrame->GetCurDoc();
	if (pDoc) {
		HTREEITEM hItem = m_wndGraphView.GetSelectedItem();
		int level = m_wndGraphView.GetItemLevel(hItem);
		if (level == 2) {
			// Graphic
			CFXGraphic* pGraphic =( CFXGraphic*)m_wndGraphView.GetItemData(hItem);
			pDoc->OpenGraphic(pGraphic);
		}
		if (level == 3) {
			// Variable
			CFXGraphicVariable* pVar = (CFXGraphicVariable*)m_wndGraphView.GetItemData(hItem);
			HTREEITEM hItemGraph = m_wndGraphView.GetParentItem(hItem);
			CFXGraphic* pGraphic = (CFXGraphic*)m_wndGraphView.GetItemData(hItemGraph);
			pDoc->OpenGraphic(pGraphic);
		}
	}
}


void CGraphView::OnGraphRemove()
{
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CFXGraphDoc* pDoc = pMainFrame->GetCurDoc();
	if (pDoc) {
		HTREEITEM hItem = m_wndGraphView.GetSelectedItem();
		CFXGraphic* pGraphic = (CFXGraphic*)m_wndGraphView.GetItemData(hItem);
		m_wndGraphView.DeleteItem(hItem);
		pDoc->RemoveGraphic(pGraphic);
		UpdateView(pDoc);
	}
}


void CGraphView::OnGraphPinProperties()
{
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CFXGraphDoc* pDoc = pMainFrame->GetCurDoc();
	if (!pDoc)
		return;
	HTREEITEM hItemVar = m_wndGraphView.GetSelectedItem();
	if (!hItemVar)
		return;
	CFXGraphicVariable* pVar = (CFXGraphicVariable*)m_wndGraphView.GetItemData(hItemVar);
	HTREEITEM hItemGraph = m_wndGraphView.GetParentItem(hItemVar);
	CFXGraphic* pGraphic = (CFXGraphic*)m_wndGraphView.GetItemData(hItemGraph);
	CGraphPinDlg dlg;
	dlg.m_ColorBtn.SetColor(pVar->m_Color);
	if (dlg.DoModal() == IDOK) {
		pVar->m_Color = dlg.m_ColorBtn.GetColor();
		UpdateView(pDoc);
		CFXGraphViewGraphic* pView = pDoc->GetGraphicView(pGraphic);
		if (pView)
			pView->Invalidate(0);
	}
}


void CGraphView::OnGraphPinRemove()
{
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CFXGraphDoc* pDoc = pMainFrame->GetCurDoc();
	if (!pDoc)
		return;
	HTREEITEM hItemVar = m_wndGraphView.GetSelectedItem();
	if (!hItemVar)
		return;
	CFXGraphicVariable* pVar = (CFXGraphicVariable*)m_wndGraphView.GetItemData(hItemVar);
	HTREEITEM hItemGraph = m_wndGraphView.GetParentItem(hItemVar);
	CFXGraphic* pGraphic = (CFXGraphic*)m_wndGraphView.GetItemData(hItemGraph);
	pGraphic->RemoveVariable(pVar);
	UpdateView(pDoc);
	CFXGraphViewGraphic* pView = pDoc->GetGraphicView(pGraphic);
	if (pView)
		pView->Invalidate(0);

}

