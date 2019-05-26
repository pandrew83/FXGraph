
#include "stdafx.h"
#include "ViewTree.h"
#include "FXGraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
	: m_bAllowDragDrop(0)
{
	m_pDragDropImage = NULL;
	m_bDragging = false;
	m_bAllowDragDrop = false;
	
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
//	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &CViewTree::OnTvnBegindrag)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &CViewTree::OnTvnBegindrag)
//	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONUP()
//	ON_NOTIFY_REFLECT(TVN_ITEMCHANGED, &CViewTree::OnTvnItemChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// обработчики сообщений CViewTree

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


//void CViewTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
//	// TODO: добавьте свой код обработчика уведомлений
//	*pResult = 0;
//}


void CViewTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!m_bAllowDragDrop)
		return;
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	CPoint pt(pNMTreeView->ptDrag.x,pNMTreeView->ptDrag.y);
	m_hItem = HitTest(pt);
	if (m_hItem == NULL)
		return;
	if (GetItemData(m_hItem) == 0)
		return;
	DWORD ID = GetItemData(m_hItem);

	ClientToScreen(&pt);


	COleDataSource src;
	int len = sizeof(DWORD);
	HGLOBAL hGlobal = ::GlobalAlloc(GMEM_FIXED,len);
	LPVOID lpBuf = ::GlobalLock(hGlobal);
	::CopyMemory(lpBuf,&ID,len);
	::GlobalUnlock(hGlobal);
	src.CacheGlobalData(CF_TEXT,hGlobal,NULL);
	src.DoDragDrop(DROPEFFECT_COPY,NULL,NULL);
//	ShowCursor(false);
//	SetCapture();
//	m_bDragging = 1;
	*pResult = 0;
}


//void CViewTree::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
//	if (m_bDragging){
//		TracePrint("CViewTree::OnMouseMove with dragging %d %d\n",point.x,point.y);
//		CPoint pt(point);
//		ClientToScreen(&pt);
//		m_pDragDropImage->DragMove(pt);
////		m_pDragDropImage->DragShowNolock(false);
//	}
//	CTreeCtrl::OnMouseMove(nFlags, point);
//}


//void CViewTree::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
//	if (m_bDragging){
//		m_bDragging = false;
//		ReleaseCapture();
//		m_pDragDropImage->DragLeave(NULL);
//		m_pDragDropImage->EndDrag();
//		delete m_pDragDropImage;
//		m_pDragDropImage = NULL;
//		CPoint pt(point);
//		ClientToScreen(&pt);
//		CWnd* pDropWnd = WindowFromPoint(pt);
//		if (pDropWnd->IsKindOf(RUNTIME_CLASS(CFXGraphView))){
//			DWORD id = GetItemData(m_hItem);
//			TracePrint("Dropped item data %d\n",id);
//		}
//	}
//	CTreeCtrl::OnLButtonUp(nFlags, point);
//}


//void CViewTree::OnTvnItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
//	// TODO: добавьте свой код обработчика уведомлений
////	TracePrint("CViewTree::OnTvnItemChanged Property value updated");
//	*pResult = 0;
//}
