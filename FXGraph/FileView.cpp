
#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "FXGraph.h"
#include "ChildFrm.h"
#include "FXGraphDoc.h"
#include "ParamDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
	m_pCurDoc = NULL;
}

CFileView::~CFileView()
{
	TracePrint(TRACE_LEVEL_1,__FUNCTION__);
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_PARAM_OUTPUT_ADD, &CFileView::OnParamOutputAdd)
	ON_COMMAND(ID_PARAM_REMOVE, &CFileView::OnParamRemove)
	ON_COMMAND(ID_PARAM_INPUT_ADD, &CFileView::OnParamInputAdd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ����������� ��������� CWorkspaceBar

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnCreate");
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �������� �������������:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("�� ������� ������� ������������� ������\n");
		return -1;      // �� ������� �������
	}

	// ��������� ����������� �������������:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* ������������ */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// ��� ������� ����� �������������� ����� ���� ������� ����������, � �� ����� ������������ �����:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// ������� ��������� ������ ������������ ������������� � ���� ������ (������ ���, ������ �����)
	FillFileView();
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	TracePrint(TRACE_LEVEL_2,"CFileView::OnSize");
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::FillFileView()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::FillFileView");
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnContextMenu");
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// ������� ������� �������:
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
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	TracePrint(TRACE_LEVEL_2,"CFileView::AdjustLayout");
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnProperties");
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	if (!hItem)
		return;
	CFXParam* pParam = (CFXParam*)m_wndFileView.GetItemData(hItem);
	CParamDlg dlg;
	dlg.m_Name = pParam->m_Name;
	
	switch(pParam->m_Type){
		case Logical:
			dlg.m_Type = "Logical";
			dlg.m_valbool = (bool)pParam->m_Value;
			break;
		case Int:
			dlg.m_Type = "Int";
			dlg.m_valint = (int)pParam->m_Value;
			break;
		case Float:
			dlg.m_Type = "Float";
			dlg.m_valdbl = (double)pParam->m_Value;
			break;
	}
	if (dlg.DoModal() == IDOK){
		if (dlg.m_Type == "Logical"){
			pParam->m_Type = Logical;
			pParam->m_Value = dlg.m_valbool;
		}
		if (dlg.m_Type == "Int"){
			pParam->m_Type = Int;
			pParam->m_Value = dlg.m_valint;
		}
		if (dlg.m_Type == "Float"){
			pParam->m_Type = Float;
			pParam->m_Value = dlg.m_valdbl;
		}
		pParam->m_Name = dlg.m_Name;
		m_wndFileView.SetItemText(hItem,pParam->m_Name);
		// ���� ����� ��� ���� ������ ��������� � ���� ����������
		// 1. �������� ��� �������� ��������� �� ������������� ���� �������� ���� - �������� �������� ����
		// 2. ������ �������� �������� ����
		// ������� ������� ���������
		// ������� �������� � ��� ��� ����
		// ������� ������� ����
		// - ��� ����� ���� �������� �������� 
		if (m_pCurDoc){
			m_pCurDoc->OnParameterUpdated(pParam);
			m_pCurDoc->UpdateAllViews(NULL);
		}

	}

}

void CFileView::OnFileOpen()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnFileOpen");
	// TODO: �������� ���� ��� ����������� ������
}

void CFileView::OnFileOpenWith()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnFileOpenWith");
	// TODO: �������� ���� ��� ����������� ������
}

void CFileView::OnDummyCompile()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnDummyCompile");
	// TODO: �������� ���� ��� ����������� ������
}

void CFileView::OnEditCut()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnEditCut");
	// TODO: �������� ���� ��� ����������� ������
}

void CFileView::OnEditCopy()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnEditCopy");
	// TODO: �������� ���� ��� ����������� ������
}

void CFileView::OnEditClear()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnEditClear");
	// TODO: �������� ���� ��� ����������� ������
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // �������� ���������� ��� ���������

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnSetFocus");
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	TracePrint(TRACE_LEVEL_1,"OnChangeVisualStyle");
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ������������ */);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TracePrint(TRACE_LEVEL_1,"�� ������� ��������� �������� �������: %x\n", uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}




int CFileView::UpdateFileView(CFXGraphDoc*pDoc)
{
	TracePrint(TRACE_LEVEL_2,"CFileView::UpdateFileView");
	TracePrint(TRACE_LEVEL_2,"CFileView::UpdateFileView Updating file view pCurDoc=%p pDoc=%p\n",m_pCurDoc,pDoc);
	if (!pDoc){
		TracePrint(TRACE_LEVEL_2,"CFileView::UpdateFileView No document");
		m_wndFileView.DeleteAllItems();
		m_pCurDoc = NULL;
		return 0;
	}
	if (m_pCurDoc == pDoc){
		TracePrint(TRACE_LEVEL_2,"CFileView::UpdateFileView No change document");
		return 0;
	}
	m_pCurDoc = pDoc;
	m_wndFileView.DeleteAllItems();
	HTREEITEM hRoot = m_wndFileView.InsertItem(_T("���������"), 0, 0);
	m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hInput = m_wndFileView.InsertItem(_T("�������"), 0, 0, hRoot);
	POSITION pos = pDoc->m_InputParams.GetHeadPosition();
	while (pos){
		CFXParam* p = pDoc->m_InputParams.GetNext(pos);
		HTREEITEM hItem = m_wndFileView.InsertItem(p->m_Name,hInput);
		m_wndFileView.SetItemData(hItem,(DWORD_PTR)p);
	}

	HTREEITEM hOutput = m_wndFileView.InsertItem(_T("��������"), 0, 0, hRoot);
	pos = pDoc->m_OutputParams.GetHeadPosition();
	while (pos){
		CFXParam* p = pDoc->m_OutputParams.GetNext(pos);
		HTREEITEM hItem = m_wndFileView.InsertItem(p->m_Name,hOutput);
		m_wndFileView.SetItemData(hItem,(DWORD_PTR)p);
	}

	//HTREEITEM hRes = m_wndFileView.InsertItem(_T("����� �������� FakeApp"), 0, 0, hRoot);

	//m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
	//m_wndFileView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
	//m_wndFileView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
	//m_wndFileView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);

	m_wndFileView.Expand(hRoot, TVE_EXPAND);
	m_wndFileView.Expand(hInput, TVE_EXPAND);
	m_wndFileView.Expand(hOutput, TVE_EXPAND);
	return 0;
}


void CFileView::OnParamOutputAdd()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnParamOutputAdd");
	if (!m_pCurDoc)
		return;
	CParamDlg dlg;
	CString name;
	int n=1;
	do{
		name.Format(_T("����� �������� �������� %d"),n);
		n++;
	} while (m_pCurDoc->CheckParamName(name));
	dlg.m_Name = name;
	dlg.m_Type = "Logical";
	dlg.m_valbool = false;
	variant_t value;
	if (dlg.DoModal() == IDOK){
		CFXPinType type;
		if (dlg.m_Type == "Logical"){
			type = Logical;
			value = dlg.m_valbool;
		}
		if (dlg.m_Type == "Int"){
			type = Int;
			value = dlg.m_valint;
		}
		if (dlg.m_Type == "Float"){
			type = Float;
			value = dlg.m_valdbl;
		}
		if (m_pCurDoc->CheckParamName(dlg.m_Name)){
			AfxMessageBox(_T("�������� � ����� ������ ��� ����������. �������� ������ ���"));
			return;
		}
		m_pCurDoc->m_OutputParams.AddTail(new CFXParam(dlg.m_Name,type,value));
		CFXGraphDoc* pDoc = m_pCurDoc;
		m_pCurDoc = NULL;
		UpdateFileView(pDoc);
		CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrame->UpdatePropertiesWindow();
	}
}


void CFileView::OnParamRemove()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnParamRemove");
	if (!m_pCurDoc)
		return;
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	if (!hItem)
		return;
	CFXParam* pParam = (CFXParam*)m_wndFileView.GetItemData(hItem);
	POSITION pos;
	pos = m_pCurDoc->m_InputParams.Find(pParam);
	if (pos){
		m_pCurDoc->m_InputParams.RemoveAt(pos);
		delete pParam;
		m_wndFileView.DeleteItem(hItem);
		return;
	}
	pos = m_pCurDoc->m_OutputParams.Find(pParam);
	if (pos){
		m_pCurDoc->m_OutputParams.RemoveAt(pos);
		delete pParam;
		m_wndFileView.DeleteItem(hItem);
		CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrame->UpdatePropertiesWindow();
		return;
	}
	// TODO: �������� ���� ��� ����������� ������
}


void CFileView::OnParamInputAdd()
{
	TracePrint(TRACE_LEVEL_1,"CFileView::OnParamInputAdd");
	if (!m_pCurDoc)
		return;
	CParamDlg dlg;
	int n = 1;
	CString name;
	do{
		name.Format(_T("����� ������� �������� %d"),n);
		n++;
	}
	while (m_pCurDoc->CheckParamName(name));
	dlg.m_Name = name;
	dlg.m_Type = "Logical";
	dlg.m_valbool = false;
	if (dlg.DoModal() == IDOK){
		CFXPinType type;
		variant_t value;
		if (dlg.m_Type == "Logical"){
			type = Logical;
			value = dlg.m_valbool;
		}
		if (dlg.m_Type == "Int"){
			type = Int;
			value = (int)dlg.m_valint;
		}
		if (dlg.m_Type == "Float"){
			type = Float;
			value = dlg.m_valdbl;
		}
		if (m_pCurDoc->CheckParamName(dlg.m_Name)){
			AfxMessageBox(_T("�������� � ����� ������ ��� ����������. �������� ������ ���"));
			return;
		}
		m_pCurDoc->m_InputParams.AddTail(new CFXParam(dlg.m_Name,type,value));
		CFXGraphDoc* pDoc = m_pCurDoc;
		m_pCurDoc = NULL;
		UpdateFileView(pDoc);
		CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrame->UpdatePropertiesWindow();
	}
}
