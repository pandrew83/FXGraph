
// FXGraphView.cpp : ���������� ������ CFXGraphView
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "FXGraph.h"
#endif

#include "FXGraphDoc.h"
#include "FXGraphView.h"
#include "FXGraph.h"
#include "MainFrm.h"
#include <typeinfo>
#include "ChildFrm.h"
#include "FXBlockFunctional.h"
#include "FXBlockLogicalAnd.h"
#include "FXBlockLogicalNot.h"
#include "FXBlockLogicalOr.h"
#include "FXBlockLogicalXor.h"
#include "FXBlockControllerNiMod01.h"
#include "FXBlockMathIntAdd.h"
#include "FXBlockMathIntMul.h"
#include "FXBlockMathIntSub.h"
#include "FXBlockMathIntDiv.h"
#include "FXBlockMathFloatAdd.h"
#include "FXBlockMathFloatDiv.h"
#include "FXBlockMathFloatMul.h"
#include "FXBlockMathFloatSub.h"
#include "FXBlockMathFloatFloor.h"
#include "FXBlockMathCastFloatInt.h"
#include "FXBlockMathCastIntFloat.h"
#include "FXBlockComment.h"
#include "FXBlockMathBitwiseNot.h"
#include "FXBlockMathBitwiseOr.h"
#include "FXBlockBitwiseAnd.h"
#include "FXBlockMathBitwiseShiftLeft.h"
#include "FXBlockMathBitwiseShiftRight.h"
#include "FXBlockMathBitwiseXor.h"
#include "FXBlockMathBitwisePack.h"
#include "FXBlockMathBitwiseUnpack.h"
#include "FXBlockExtensionA01.h"
#include "FXBlockMathFloatGreat.h"
#include "FXBlockMathFloatGreatEqual.h"
#include "FXBlockMathFloatLess.h"
#include "FXBlockMathFloatLessEqual.h"
#include "FXBlockMathFloatNotEqual.h"
#include "FXBlockMathFloatEqual.h"
#include "FXBlockComparatorUp.h"
#include "FXBlockComparatorDown.h"
#include "FXBlockLogicalFallingEdge.h"
#include "FXBlockLogicalRisingEdge.h"
#include "FXBlockLogicalTriggerRS.h"
#include "FXBlockLogicalTriggerRSRisingEdge.h"
#include "FXBlockLogicalTriggerSR.h"
#include "FXBlockCounter.h"
#include "FXBlockMathIntMod.h"
#include "FXBlockMathFloatAbs.h"
#include "FXBlockMathIntAbs.h"
#include "FXBlockMathIntEqual.h"
#include "FXBlockMathIntGreat.h"
#include "FXBlockMathIntGreatEqual.h"
#include "FXBlockMathIntLess.h"
#include "FXBlockMathIntLessEqual.h"
#include "FXBlockMathIntNotEqual.h"
#include "FXBlockMathCos.h"
#include "FXBlockMathSin.h"
#include "FXBlockMathTan.h"
#include "FXBlockMathSqrt.h"
#include "FXBlockMathPow.h"
#include "FXBlockMathLog.h"
#include "FXBlockMathLog10.h"
#include "FXBlockMathExp.h"
#include "FXBlockMathAsin.h"
#include "FXBlockMathAcos.h"
#include "FXBlockMathAtan.h"
#include "FXBlockMathFloatRound.h"
#include "CFXBlockAntiBounce.h"
#include "CFXBlockDelayOn.h"
#include "CFXBlockDelayOff.h"
#include "CFXBlockSensorCurrent.h"
#include "CFXBlockSensorTRD2WM50.h"
#include "CFXBlockSensorTRD2WM100.h"
#include "CFXBlockSensorTRD2WPt100.h"
#include "CFXBlockSensorTRD2WPt500.h"
#include "CFXBlockSensorTRD2WPt1000.h"
#include "CFXBlockSensorTRD2WP50.h"
#include "CFXBlockSensorTRD2WP100.h"
#include "CFXBlockSensorTRD3WM50.h"
#include "CFXBlockSensorTRD3WM100.h"
#include "CFXBlockSensorTRD3WPt100.h"
#include "CFXBlockSensorTRD3WPt500.h"
#include "CFXBlockSensorTRD3WPt1000.h"
#include "CFXBlockSensorTRD3WP50.h"
#include "CFXBlockSensorTRD3WP100.h"
#include "CFXBlockSensorTRD4WM50.h"
#include "CFXBlockSensorTRD4WM100.h"
#include "CFXBlockSensorTRD4WPt100.h"
#include "CFXBlockSensorTRD4WPt500.h"
#include "CFXBlockSensorTRD4WPt1000.h"
#include "CFXBlockSensorTRD4WP50.h"
#include "CFXBlockSensorTRD4WP100.h"
#include "CommentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CFXGraphViewScenario
IMPLEMENT_DYNCREATE(CFXGraphViewScenario,CEditView)

CFXGraphViewScenario::CFXGraphViewScenario(){
}




// CFXGraphView

IMPLEMENT_DYNCREATE(CFXGraphView, CView)

BEGIN_MESSAGE_MAP(CFXGraphView, CView)
	// ����������� ������� ������
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFXGraphView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEHWHEEL()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ALIGN_BOTTOM, &CFXGraphView::OnAlignBottom)
	ON_COMMAND(ID_ALIGN_LEFT, &CFXGraphView::OnAlignLeft)
	ON_COMMAND(ID_ALIGN_RIGHT, &CFXGraphView::OnAlignRight)
	ON_COMMAND(ID_ALIGN_TOP, &CFXGraphView::OnAlignTop)
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_COMMAND(ID_BLOCK_INPUTPIN_ADD_LOGICAL, &CFXGraphView::OnBlockInputpinAddLogical)
	ON_COMMAND(ID_BLOCK_PIN_REMOVE, &CFXGraphView::OnBlockPinRemove)
	ON_COMMAND(ID_BLOCK_INPUTPIN_ADD_FLOAT, &CFXGraphView::OnBlockInputpinAddFloat)
	ON_COMMAND(ID_BLOCK_INPUTPIN_ADD_INT, &CFXGraphView::OnBlockInputpinAddInt)
	ON_COMMAND(ID_BLOCK_OUTPUTPIN_ADD_FLOAT, &CFXGraphView::OnBlockOutputpinAddFloat)
	ON_COMMAND(ID_BLOCK_OUTPUTPIN_ADD_INT, &CFXGraphView::OnBlockOutputpinAddInt)
	ON_COMMAND(ID_BLOCK_OUTPUTPIN_ADD_LOGICAL, &CFXGraphView::OnBlockOutputpinAddLogical)
//	ON_UPDATE_COMMAND_UI(ID_BLOCK_INPUTPIN_ADD_FLOAT, &CFXGraphView::OnUpdateBlockInputpinAddFloat)
	ON_COMMAND(ID_SHOW_LINKS, &CFXGraphView::OnShowLinks)
	ON_COMMAND(ID_LINK_REMOVE, &CFXGraphView::OnLinkRemove)
	ON_COMMAND(ID_BLOCK_REMOVE, &CFXGraphView::OnBlockRemove)
	ON_WM_LBUTTONDBLCLK()
//	ON_COMMAND(IDCLOSE, &CFXGraphView::OnIdclose)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNeedText)
	ON_COMMAND(ID_BLOCK_WEBHELP, &CFXGraphView::OnBlockWebhelp)
	ON_COMMAND(ID_BLOCK_BREAKPOINT, &CFXGraphView::OnBlockBreakpoint)
	ON_COMMAND(ID_BLOCK_PIN_REMOVE_LINKS, &CFXGraphView::OnBlockPinRemoveLinks)
END_MESSAGE_MAP()

// ��������/����������� CFXGraphView

CFXGraphView::CFXGraphView()
	: m_pDC(NULL)
	, m_ResizeObject(0)
	, m_MousePos(0)
	, m_bShowLinks(false)
	, m_pBlock(NULL)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::CFXGraphView");
	m_bButtonR = false;
	m_bButtonM = false;
	m_bButtonL = false;
	m_pCur = NULL;
	m_pObject = NULL;
	m_x = 0;
	m_y = 0;
}

CFXGraphView::~CFXGraphView()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::~CFXGraphView");
}

BOOL CFXGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::PreCreateWindow");
	return CView::PreCreateWindow(cs);
}

BOOL CFXGraphView::OnToolTipNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnToolTipNeedText");
	BOOL bHandledNotify = FALSE;

    CPoint CursorPos;
    VERIFY(::GetCursorPos(&CursorPos));
    ScreenToClient(&CursorPos);

    CRect ClientRect;
    GetClientRect(ClientRect);

    // ��������������, ��� ������ �������� � ���������� ������� ����,
    // ������ ��� ���������� ���� ����� �������� ��� ��������� ���
    // ������ ��������� �� ������ ������������.
    if (ClientRect.PtInRect(CursorPos))
    {
        TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
		COLORREF color1 = m_Mem1.GetPixel(CursorPos);
		COLORREF color2 = m_Mem2.GetPixel(CursorPos);
		int id = color1 & MASK1_ID;
		if (id){
			CFXObject* pObject = m_pBlock->GetByID(id);
			if (pObject){
				CFXBlock* pBlock = dynamic_cast<CFXBlock*>(pObject);
				CFXPin* pPin = dynamic_cast<CFXPin*>(pObject);
				CFXLink* pLink = dynamic_cast<CFXLink*>(pObject);
				if (pBlock){
					wcscpy_s(pTTT->szText, pBlock->GetName());
				}
				if (pPin){
					wcscpy_s(pTTT->szText,pPin->GetName());
				}
				if (pLink){
					wcscpy_s(pTTT->szText,pLink->GetName());
				}
				bHandledNotify = TRUE;
			}
		}
	}
	return bHandledNotify;
}
// ��������� CFXGraphView

void CFXGraphView::OnDraw(CDC* pDC)
{
	TracePrint(TRACE_LEVEL_8,"CFXGraphView::OnDraw");
	CRect rect;
	GetClientRect(&rect); // Width & Height of Local

	CDC tmp;
	m_pDC = &tmp;
	tmp.CreateCompatibleDC(pDC);
	CBitmap tmpBitmap;
	tmpBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	tmp.SelectObject(tmpBitmap);
	tmp.FillSolidRect(rect,RGB(255,255,255));

	m_Mem1.DeleteDC();
	m_Mem2.DeleteDC();
	m_Mem1.CreateCompatibleDC(pDC);
	m_Mem2.CreateCompatibleDC(pDC);
	CBitmap bitmap1,bitmap2;
	bitmap1.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	bitmap2.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	m_Mem1.SelectObject(&bitmap1);
	m_Mem2.SelectObject(&bitmap2);
	



	CFXGraphApp* pApp = (CFXGraphApp*)AfxGetApp();
	if (pApp->m_GridState == 0){ // ����� ��������
		CPoint p1 = Local2Logic(CPoint(0,0));
		CPoint p2 = Local2Logic(CPoint(rect.Width()-1,rect.Height()-1));
		while (p1.x % pApp->m_GridStep) p1.x++;
		while (p1.y % pApp->m_GridStep) p1.y++;
		if (pApp->m_GridStyle){
			CPoint p = p1;
			CPen pen(PS_SOLID,1,pApp->m_GridColor);
			tmp.SelectObject(pen);
			while (p.y <= p2.y){
				CPoint t = Logic2Local(p);
				t.x = 0;
				tmp.MoveTo(t);
				t.x = rect.Width()-1;
				tmp.LineTo(t);
				p.y += pApp->m_GridStep;
			}
			p = p1;
			while (p.x <= p2.x){
				CPoint t = Logic2Local(p);
				t.y = 0;
				tmp.MoveTo(t);
				t.y = rect.Height()-1;
				tmp.LineTo(t);
				p.x += pApp->m_GridStep;
			}
			pen.DeleteObject();
		}
		else{
			CPoint p = p1;
			while (p.y <= p2.y){
				p.x = p1.x;
				while (p.x <= p2.x){
					tmp.SetPixel(Logic2Local(p),pApp->m_GridColor);
					p.x+=pApp->m_GridStep;
				}
				p.y += pApp->m_GridStep;
			}
		}
	}
	box(&tmp,Logic2Local(CPoint(0,0)),11,RGB(0,0,127));

	CFXGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_pBlock->Draw(this);

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&tmp,0,0,SRCCOPY);
	tmpBitmap.DeleteObject();
	tmp.DeleteDC();
}


// ������ CFXGraphView


void CFXGraphView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFXGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ���������� �� ���������
	return DoPreparePrinting(pInfo);
}

void CFXGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� �������������� ������������� ����� �������
}

void CFXGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� ������� ����� ������
}

void CFXGraphView::OnRButtonUp(UINT /* nFlags */, CPoint point){

	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnRButtonUp");
	m_bButtonR = false;
	m_bButtonL = false;
	OnContextMenu(this, point);
}

void CFXGraphView::OnRButtonDown(UINT nFlags, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnRButtonDown");
	CFXGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_oldx = m_x;
	m_oldy = m_y;
	m_Point = point;
	m_bButtonR = true;

	COLORREF ID = m_Mem1.GetPixel(point);
	COLORREF color2 = m_Mem2.GetPixel(point);
	if (ID){
		CFXObject* pObject = m_pBlock->GetByID(ID&MASK1_ID);
		if (pObject != m_pCur){
			m_pCur = pObject;
			m_Selected.RemoveAll();
			m_Selected.AddTail(m_pCur);
			Invalidate(0);
		}
	}
	else{
		m_pCur = NULL;
		m_Selected.RemoveAll();
		Invalidate(0);
	}
	CView::OnRButtonDown(nFlags, point);
}

void CFXGraphView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnContextMenu");
	COLORREF color1 = m_Mem1.GetPixel(point);
	COLORREF color2 = m_Mem2.GetPixel(point);
	int id = color1 & MASK1_ID;
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnContextMenu point=(%d,%d) %X %X\n",point.x,point.y,color1,id);

#ifndef SHARED_HANDLERS
	if (m_pCur){
		CFXBlock* pBlock = dynamic_cast<CFXBlock*>(m_pCur);
		CFXPin* pPin = dynamic_cast<CFXPin*>(m_pCur);
		CFXLink* pLink = dynamic_cast<CFXLink*>(m_pCur);
		if (pPin){
			TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnContextMenu pin #%X\n",pPin->m_ID);
			ClientToScreen(&point);
			theApp.GetContextMenuManager()->ShowPopupMenu(IDR_PIN,point.x,point.y,this,TRUE);
			return;
		}
		if (pLink){
			TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnContextMenu link=%X\n",pLink->m_ID);
			ClientToScreen(&point);
			theApp.GetContextMenuManager()->ShowPopupMenu(IDR_LINK,point.x,point.y,this,TRUE);
			return;
		}
		ClientToScreen(&point);
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_BLOCK,point.x,point.y,this,TRUE);
		return;
	}
	ClientToScreen(&point);
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// ����������� CFXGraphView

#ifdef _DEBUG
void CFXGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CFXGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFXGraphDoc* CFXGraphView::GetDocument() const // �������� ������������ ������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFXGraphDoc)));
	return (CFXGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// ����������� ��������� CFXGraphView


void CFXGraphView::OnLButtonDown(UINT nFlags, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLButtonDown");
	CFXGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_bButtonL = true;
	m_Point = point;
	COLORREF color1 = m_Mem1.GetPixel(point);
	COLORREF color2 = m_Mem2.GetPixel(point);
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLButtonDown point=(%d,%d) %X %X\n",point.x,point.y,color1,color2);
	m_pCur = m_pBlock->GetByID(color1&MASK1_ID);
	if (m_pCur){
		if (color2 & (MASK2_BORDERS|MASK2_CORNERS) && !pDoc->m_bDebug){ // ������ �� ������� �����
			// ����� ��������� �������
			m_bResize = true;
			m_ResizeObject = color2;
			return;
		}
		if (nFlags & MK_CONTROL){ // ������ � CTRL
			if (color1&MASK1_SELECTED){
				// ��� ����������. ������� ���������
				m_Selected.RemoveAt(m_Selected.Find(m_pCur));
				m_pCur->Invalidate(this,REGION_BLOCK|REGION_LEFT|REGION_RIGHT|REGION_PIN);
			}
			else{
				// �� ����������. ��������
				m_Selected.AddTail(m_pCur);
				m_pCur->Invalidate(this,REGION_BLOCK|REGION_LEFT|REGION_RIGHT|REGION_PIN);
			}
		}
		else{
			if (color2 & (MASK2_BORDERS|MASK2_CORNERS) && !pDoc->m_bDebug){
				m_Selected.RemoveAll();
				m_Selected.AddTail(m_pCur);
				m_bResize = true;
			}
			else{
				if (color1 & MASK1_SELECTED){
					return;
					// ����������
					// ��������:
					// 1. ���� ������ ����������, �� �����������
					// 2. ���������, �� ������ �� ������
				}
				else{
					// �� ����������. �������� ������ ���
					if (m_Selected.GetSize() == 1 && !pDoc->m_bDebug){
						CFXPin* pPin1 = dynamic_cast<CFXPin*>(m_Selected.GetHead());
						CFXPin* pPin2 = dynamic_cast<CFXPin*>(m_pCur);
						CFXPin* pPinIn = NULL;
						CFXPin* pPinOut = NULL;

						// ������ �������� ���������� �����
						// 1. input - Output
						// 1.1. ��� ���� �� ����� ������ - ���������
						// 1.2. ���� ��� ����� ����� - 
						// 1.3. ��� ���� ����� �����
						// 1.3.1. ��� ���� ������� ����� ������ - �����
						// 1.3.2. ��� ���� ����� ������ �����
						
						// 3. input - input
						// 3.1. ��� ���� �� ����� ������ - �����
						// 3.2. ���� ��� ����� ����� - �������� Output � ��������� 
						// 3.3. ��� ���� ����� �����
						// 3.3.1 ��� ���� ��������� ����� ������ - �����
						// 3.3.2 ��� ���� ����� ������ �����
						// 4. output - output - �����
						// ����������� ����������
						// ���� ���� ������ ����� - �����
						// 

						if (!pPin1 || !pPin2 || (pPin1->m_Dir == Output && pPin2->m_Dir == Output)){
							// ���� �� �������� �� ���. ��������� ����� �������
							while (!m_Selected.IsEmpty()){
								CFXObject* pObj = m_Selected.RemoveHead();
								pObj->Invalidate(this,REGION_BLOCK|REGION_LEFT|REGION_RIGHT|REGION_PIN);
							}
							m_Selected.AddTail(m_pCur);
							TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLButtonDown: Calling UpdatePropertiesWnd at point #6");
							UpdatePropertiesWnd();
							m_pCur->Invalidate(this,REGION_BLOCK|REGION_LEFT|REGION_RIGHT|REGION_PIN);
							return;
						}
						if (pPin1->m_Dir == Input && pPin2->m_Dir == Input){ 
							CListLink lst1,lst2;
							pPin1->GetPinLinks(lst1);
							pPin2->GetPinLinks(lst2);
							if (lst1.GetCount() == 0 && lst2.GetCount() == 0){
								m_Selected.RemoveAll();
								m_Selected.AddTail(m_pCur);
								TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLButtonDown: Calling UpdatePropertiesWnd at point #5");
								UpdatePropertiesWnd();
								Invalidate(0);
								return;
							}
							if (lst1.GetCount() == 0 && lst2.GetCount() != 0){
								pPinIn = pPin1;
								CFXLink* pLink = lst2.GetHead();
								pPinOut = pLink->m_pOut;
							}
							if (lst1.GetCount() != 0 && lst2.GetCount() == 0){
								pPinIn = pPin2;
								CFXLink* pLink = lst1.GetHead();
								pPinOut = pLink->m_pOut;
							}
							if (lst1.GetCount() != 0 && lst2.GetCount() != 0){
								CFXLink* pLink1 = lst1.GetHead();
								CFXLink* pLink2 = lst2.GetHead();
								if (pLink1->m_pOut == pLink2->m_pOut){
									m_Selected.RemoveAll();
									m_Selected.AddTail(m_pCur);
									TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLButtonDown: Calling UpdatePropertiesWnd at point #4");
									UpdatePropertiesWnd();
									Invalidate(0);
									return;
								}
								pPin1->RemoveLinks();
								m_pBlock->AddLink(pLink2->m_pOut,pPin1);
								m_bLinking = true;
								m_Selected.RemoveAll();
								TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLButtonDown: Calling UpdatePropertiesWnd at point #3");
								UpdatePropertiesWnd();
								Invalidate(0);
								m_pCur = NULL;
								return;
							}
						}
						if (!pPinOut && !pPinIn){
							if (pPin1->m_Dir == Input && pPin2->m_Dir == Output){
								pPinIn = pPin1;
								pPinOut = pPin2;
							}
							else{
								pPinIn = pPin2;
								pPinOut = pPin1;
							}

						}
						if (pPinOut->GetLink(pPinIn)){
							// ��� ���� ����� ����� ����� ������
							return;
						}
						CListLink lst1,lst2;
						pPinIn->GetPinLinks(lst1);
						pPinOut->GetPinLinks(lst2);
						if (lst1.GetCount() > 0){
							// ��� �� ������
							if (AfxMessageBox(_T("��� ��� ����� ����� � ������ �����. �������� �����?"),MB_YESNO) == IDNO){
								return;
							}
							pPinIn->RemoveLinks();
						}
						CFXLink* pLink = m_pBlock->AddLink(pPinOut,pPinIn);
						pLink->Invalidate(this,REGION_LINK);
						m_bLinking = true;
						while (!m_Selected.IsEmpty()){
							m_Selected.RemoveHead()->Invalidate(this,REGION_BLOCK|REGION_LEFT|REGION_RIGHT|REGION_PIN|REGION_LINK);
						}
						TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLButtonDown: Calling UpdatePropertiesWnd at point #2");
						UpdatePropertiesWnd();
						m_pBlock->Invalidate(this,REGION_LINK);
						return;

					}
					else{
						while (!m_Selected.IsEmpty()){
							m_Selected.RemoveHead()->Invalidate(this,REGION_BLOCK|REGION_LEFT|REGION_RIGHT|REGION_PIN|REGION_LINK);
						}
						m_Selected.AddTail(m_pCur);
						m_pCur->Invalidate(this,REGION_BLOCK|REGION_LEFT|REGION_RIGHT|REGION_PIN);
					}
				}
			}
		}
	}
	else{
		POSITION pos = m_Selected.GetHeadPosition();
		while (pos){
			CFXObject* pObj = m_Selected.GetNext(pos);
			pObj->Invalidate(this,REGION_BLOCK|REGION_LEFT|REGION_RIGHT|REGION_PIN);
		}
		m_Selected.RemoveAll();
	}
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLButtonDown: Calling UpdatePropertiesWnd at point #1");
	UpdatePropertiesWnd();
//	Invalidate(0);
}


void CFXGraphView::OnLButtonUp(UINT nFlags, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLButtonUp");
	m_bButtonL = false;
	if (m_bResize){
		m_bResize = false;
		UpdatePropertiesWnd();
		return;
	}
	if (m_bMoving){
		m_bMoving = false;
		UpdatePropertiesWnd();
		return;
	}
	if (m_bLinking){
		m_bLinking = false;
		return;
	}
	// ����� ���������
	CFXGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	COLORREF color1 = m_Mem1.GetPixel(point);
	COLORREF color2 = m_Mem2.GetPixel(point);
	CFXObject* pObject = m_pBlock->GetByID(color1);
	if (pObject){ // ��������� ��� ��������
		if (nFlags & MK_CONTROL){ // � CTRL
			if (color1 & MASK1_SELECTED){ // ����������
				//m_Selected.RemoveAll();
				//m_Selected.AddTail(pObject);
			}
			else{
			}
		}
		else{
	/*		m_Selected.RemoveAll();
			m_Selected.AddTail(pObject);
			TracePrint("CFXGraphView::OnLButtonUp: Calling UpdatePropertiesWnd");
			UpdatePropertiesWnd();*/
		}
	}
//	Invalidate(0);
}

void CFXGraphView::OnMouseMove(UINT nFlags, CPoint point)
{
	TracePrint(TRACE_LEVEL_2,"CFXGraphView::OnMouseMove");
	CFXGraphDoc* pDoc = GetDocument();
	CFXGraphApp* pApp = (CFXGraphApp*)AfxGetApp();
	CMainFrame* pMainFrame = (CMainFrame*)pApp->m_pMainWnd;
	if (m_MousePos == point )
		return;
	m_MousePos = point;
	CPoint logic = Local2Logic(point);
	CString strStatus;

    strStatus.Format(ID_INDICATOR_COORD, logic.x,logic.y);

    pMainFrame->m_wndStatusBar.SetPaneText(pMainFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOR_COORD),strStatus );
	//	TracePrint("%d OnMouseMove (%d,%d)\n",(rand()%100)+100,point.x,point.y);
	COLORREF color1 = m_Mem1.GetPixel(point);
	COLORREF color2 = m_Mem2.GetPixel(point);
//	TracePrint("%X %X\n",color1,color2);
	int ID = color1 & MASK1_ID;
	if (m_bButtonL && !m_bMoving && !m_bResize && color1 & MASK1_SELECTED && !pDoc->m_bDebug){
		// ����� ������, �� ����� ����������� � ����������� ������ �� ���������� ��������
		// m_Point - ����� ������ �����������
		m_bMoving = true;
		m_pCur = m_pBlock->GetByID(ID);
		POSITION pos = m_Selected.GetHeadPosition();
		while (pos){
			CFXObject* pObject = m_Selected.GetNext(pos);
			pObject->StartMoving();
		}
	}
	if (m_bResize){
		CFXBlock* pBlock = (CFXBlock*)m_pCur;
		if (m_ResizeObject & MASK2_BORDER_TOP){
			int newY;
			if (pApp->m_GridBind)
				newY = GetNearestPoint(CPoint(0,Local2Logic(point).y)).y;
			else
				newY = logic.y;
			int y = pBlock->GetY();
			if (y+pBlock->GetHeight()-newY < pBlock->m_MinHeight){
				return;
			}
			pBlock->SetY(newY);
			pBlock->SetHeight(y+pBlock->GetHeight()-newY);
		}
		if (m_ResizeObject & MASK2_BORDER_BOTTOM){
			int newH; 
			if (pApp->m_GridBind)
				newH = GetNearestPoint(CPoint(0,Local2Logic(point).y - pBlock->GetY())).y;
			else
				newH = Local2Logic(point).y - pBlock->GetY();
			if (newH < pBlock->m_MinHeight){
				return;
			}
			pBlock->SetHeight(newH);
		}
		if (m_ResizeObject & MASK2_BORDER_LEFT){
			int newX;
			if (pApp->m_GridBind)
				newX = GetNearestPoint(CPoint(0,Local2Logic(point).x)).y;
			else
				newX = Local2Logic(point).x;
			int x = pBlock->GetX();
			if (x+pBlock->GetWidth()-newX < pBlock->m_MinWidth){
				return;
			}
			else{
				pBlock->SetX(newX);
				pBlock->SetWidth(x+pBlock->GetWidth()-newX);
			}
		}
		if (m_ResizeObject & MASK2_BORDER_RIGHT){
			int newW;
			if (pApp->m_GridBind)
				newW = GetNearestPoint(CPoint(Local2Logic(point).x - pBlock->GetX(),0)).x;
			else
				newW = Local2Logic(point).x - pBlock->GetX();
			if (newW < pBlock->m_MinWidth){
				return;
			}
			pBlock->SetWidth(newW);
		}
		if (m_ResizeObject & MASK2_CORNER_TL){
			CPoint p;
			int newW,newH;
			if (pApp->m_GridBind)
				p = GetNearestPoint(Local2Logic(point));
			else
				p = Local2Logic(point);
			newH = pBlock->GetY()+pBlock->GetHeight()-p.y;
			newW = pBlock->GetX()+pBlock->GetWidth()-p.x;
			if (newH < pBlock->m_MinHeight && newW < pBlock->m_MinWidth)
				return;
			if (newH >= pBlock->m_MinHeight){
				pBlock->SetY(p.y);
				pBlock->SetHeight(newH);
			}
			if (newW >= pBlock->m_MinWidth){
				pBlock->SetX(p.x);
				pBlock->SetWidth(newW);
			}
		}
		if (m_ResizeObject & MASK2_CORNER_TR){
			CPoint p;
			int newW,newH;
			if (pApp->m_GridBind)
				p = GetNearestPoint(Local2Logic(point));
			else
				p = Local2Logic(point);
			newH = pBlock->GetY()+pBlock->GetHeight()-p.y;
			newW = p.x-pBlock->GetX();
			if (newH < pBlock->m_MinHeight && newW < pBlock->m_MinWidth)
				return;
			if (newH >= pBlock->m_MinHeight){
				pBlock->SetY(p.y);
				pBlock->SetHeight(newH);
			}
			if (newW >= pBlock->m_MinWidth)
				pBlock->SetWidth(newW);
		}
		if (m_ResizeObject & MASK2_CORNER_BL){
			CPoint p;
			int newW,newH;
			if (pApp->m_GridBind)
				p = GetNearestPoint(Local2Logic(point));
			else
				p = Local2Logic(point);
			newH = p.y - pBlock->GetY();
			newW = pBlock->GetX()+pBlock->GetWidth()-p.x;
			if (newH< pBlock->m_MinHeight && newW < pBlock->m_MinWidth)
				return;
			if (newH >= pBlock->m_MinHeight)
				pBlock->SetHeight(newH);
			if (newW >= pBlock->m_MinWidth){
				pBlock->SetX(p.x);
				pBlock->SetWidth(newW);
			}
		}
		if (m_ResizeObject & MASK2_CORNER_BR){
			CPoint p;
			int newW,newH;
			if (pApp->m_GridBind)
				p = GetNearestPoint(Local2Logic(point));
			else
				p = Local2Logic(point);
			newH = p.y-pBlock->GetY();
			newW = p.x-pBlock->GetX();
			if (newH< pBlock->m_MinHeight && newW < pBlock->m_MinWidth)
				return;
			if (newH >= pBlock->m_MinHeight)
				pBlock->SetHeight(newH);
			if (newW >= pBlock->m_MinWidth)
				pBlock->SetWidth(newW);
		}
		UpdateProperty(PROP_WIDTH,pBlock->GetWidth());
		UpdateProperty(PROP_HEIGHT,pBlock->GetHeight());
		UpdateProperty(PROP_COORDX,pBlock->GetX());
		UpdateProperty(PROP_COORDY,pBlock->GetY());
		pBlock->Invalidate(this,REGION_COORD);
//		Invalidate(0);
		return;
	}
	if (m_bMoving){
		// �������� � ���������� �������� �� �������� ����� � ������� �����
		CPoint p1 = Local2Logic(point);
		CPoint p11 = Local2Logic(m_Point);
		int dx = p1.x-p11.x;
		int dy = p1.y-p11.y;
		// ����� ���������� �������� ����� � ���������� ��������
		CPoint p2 = CPoint(m_pCur->m_SaveX+dx,m_pCur->m_SaveY+dy);
		CPoint p3;
		CPoint p4;
		if (pApp->m_GridBind){ // �������� �������� � �����
			p3 = GetNearestPoint(p2);
		}
		else{ // ������������ ����������� ��� ��������
			p3 = p2;
		}
//		TracePrint("m_Point=(%d,%d) point=(%d,%d) p1=(%d,%d) p2=(%d,%d) p3=(%d,%d) p4=(%d,%d)\n",m_Point.x,m_Point.y,point.x,point.y,p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y);
		// �������� �� �������� ����� ����� �� ������� �����
		p4 = CPoint(p3.x-m_pCur->m_SaveX,p3.y-m_pCur->m_SaveY);
		if (p4.x || p4.y){
			TracePrint(TRACE_LEVEL_1,"OffSet=(%d,%d)",p4.x,p4.y);
			POSITION pos = m_Selected.GetHeadPosition();
			while (pos){
				CFXObject* pObject = m_Selected.GetNext(pos);
				CFXPin* pPin = dynamic_cast<CFXPin*>(pObject);
				if (!pPin){
					pObject->Move(p4.x,p4.y);
					pObject->Invalidate(this,REGION_COORD);
				}
			}
			UpdateProperty(PROP_COORDX,m_pCur->GetX());
			UpdateProperty(PROP_COORDY,m_pCur->GetY());
//			m_pCur->Invalidate(this,REGION_COORD);
//			Invalidate(0);
		}
		return;
	}
	if (!m_bButtonL && !m_bButtonR && !m_bButtonM && ID){
		CFXObject* pObject = m_pBlock->GetByID(ID & MASK1_ID);
		if (pObject){
			m_ToolTip.Activate(true);
		}
		else
			m_ToolTip.Activate(false);
	}
	else
		m_ToolTip.Activate(false);
	// ���������� �������� ����
	if (!pDoc->m_bDebug && !m_bButtonL && !m_bButtonR && (color2 & (MASK2_BORDERS|MASK2_CORNERS))){
		if (color2 & MASK2_BORDER_TOP || color2 & MASK2_BORDER_BOTTOM)
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
		if (color2 & MASK2_BORDER_LEFT || color2 & MASK2_BORDER_RIGHT)
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		if (color2 & MASK2_CORNER_TL || color2 & MASK2_CORNER_BR)
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
		if (color2 & MASK2_CORNER_TR || color2 & MASK2_CORNER_BL)
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
	}
	else
		if (m_bResize){
		}
		else{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		}

	// ����������� ����
	if (m_bButtonM && nFlags & MK_MBUTTON){
		CPoint p1 = Local2Logic(m_Point);
		CPoint p2 = Local2Logic(point);
		int dx = p2.x-p1.x;
		int dy = p2.y-p1.y;
		m_x = m_oldx - dx;
		m_y = m_oldy - dy;
		Invalidate(0);
	}
	
}

void CFXGraphView::OnMButtonUp(UINT nFlags, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnMButtonUp");
	m_bButtonM = false;
	CView::OnMButtonUp(nFlags, point);
}


void CFXGraphView::OnMButtonDown(UINT nFlags, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnMButtonDown");
	m_oldx = m_x;
	m_oldy = m_y;
	m_Point = point;
	m_bButtonM = true;

	CView::OnMButtonDown(nFlags, point);
}

BOOL CFXGraphView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnMouseWheel");
	CFXGraphDoc* pDoc = GetDocument();
	if (zDelta > 0){
		m_Scale += 10;
	}
	else{
		m_Scale -= 10;
	}
	pDoc->UpdateAllViews(NULL);
	return 0;
}


void CFXGraphView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnMouseHWheel");
	CView::OnMouseHWheel(nFlags, zDelta, pt);
}


BOOL CFXGraphView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnDrop");
	CFXGraphApp* pApp = (CFXGraphApp*)AfxGetApp();
	CFXGraphDoc* pDoc = GetDocument();
	HGLOBAL hGlobal = pDataObject->GetGlobalData(CF_TEXT,NULL);
	if (hGlobal){
		DWORD* pID = (DWORD*)::GlobalLock(hGlobal);
		CPoint logic = Local2Logic(point);
		if (pApp->m_GridBind)
			logic = GetNearestPoint(logic);
		AddBlock(*pID,logic);
		pDoc->UpdateAllViews(NULL);
		::GlobalUnlock(hGlobal);
		::GlobalFree(hGlobal);
	}
	return CView::OnDrop(pDataObject, dropEffect, point);
}


DROPEFFECT CFXGraphView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnDragOver");
	return DROPEFFECT_COPY;//CView::OnDragOver(pDataObject, dwKeyState, point);
}


void CFXGraphView::OnDragLeave()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnDragLeave");
	CView::OnDragLeave();
}


DROPEFFECT CFXGraphView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnDragEnter");
	return CView::OnDragEnter(pDataObject, dwKeyState, point);
}


int CFXGraphView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnCreate");
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_DropTarget.Register(this);
	m_x = 0;
	m_y = 0;
	m_Scale = 100;
	m_bResize = 0;
	m_bMoving = 0;
	m_bButtonL = false;
	m_bButtonR = false;
	m_bShowLinks = true;
	CPaintDC dc(this);
	m_Mem1.CreateCompatibleDC(&dc);
	m_Mem2.CreateCompatibleDC(&dc);
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnCreate: New view %p\n",this);
	return 0;
}

CPoint CFXGraphView::Logic2Local(CPoint point)
{
	TracePrint(TRACE_LEVEL_2,"CFXGraphView::Logic2Local");
	CRect rect;
	GetClientRect(&rect);
	CPoint ret;
	ret.x = (LONG)((point.x-m_x)*m_Scale/100+rect.Width()/2);
	ret.y = (LONG)((point.y-m_y)*m_Scale/100+rect.Height()/2);
	return ret;
}

CPoint CFXGraphView::Local2Logic(CPoint point)
{
	TracePrint(TRACE_LEVEL_2,"CFXGraphView::Local2Logic");
	CRect rect;
	GetClientRect(&rect);
	CPoint ret;
	ret.x = (LONG)((point.x-rect.Width()/2)*100/m_Scale+m_x);
	ret.y = (LONG)((point.y-rect.Height()/2)*100/m_Scale+m_y);
	return ret;
}

bool CFXGraphView::IsSelected(CFXObject* pObject)
{
	TracePrint(TRACE_LEVEL_2,"CFXGraphView::IsSelected");
	POSITION pos = m_Selected.GetHeadPosition();
	while (pos){
		CFXObject* pObj = m_Selected.GetNext(pos);
		if (pObject == pObj)
			return true;
	}
	return false;
}


void CFXGraphView::OnAlignBottom()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnAlignBottom");
	if (!m_Selected.IsEmpty()){
		int y = m_Selected.GetHead()->GetY();
		POSITION pos = m_Selected.GetHeadPosition();
		while(pos){
			CFXObject* pObject = m_Selected.GetNext(pos);
			if (y < pObject->GetY())
				y = pObject->GetY();
		}
		pos = m_Selected.GetHeadPosition();
		while (pos){
			CFXObject* pObject = m_Selected.GetNext(pos);
			pObject->SetY(y);
			pObject->Invalidate(this,REGION_COORD);
		}
}
}


void CFXGraphView::OnAlignLeft()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnAlignLeft");
	if (!m_Selected.IsEmpty()){
		int x = m_Selected.GetHead()->GetX();
		POSITION pos = m_Selected.GetHeadPosition();
		while(pos){
			CFXObject* pObject = m_Selected.GetNext(pos);
			if (x > pObject->GetX())
				x = pObject->GetX();
		}
		pos = m_Selected.GetHeadPosition();
		while (pos){
			CFXObject* pObject = m_Selected.GetNext(pos);
			pObject->SetX(x);
			pObject->Invalidate(this,REGION_COORD);
		}
//		Invalidate(0);
	}
}


void CFXGraphView::OnAlignRight()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnAlignRight");
	if (!m_Selected.IsEmpty()){
		int x = m_Selected.GetHead()->GetX();
		POSITION pos = m_Selected.GetHeadPosition();
		while(pos){
			CFXObject* pObject = m_Selected.GetNext(pos);
			if (x < pObject->GetX())
				x = pObject->GetX();
		}
		pos = m_Selected.GetHeadPosition();
		while (pos){
			CFXBlock* pBlock = (CFXBlock*)m_Selected.GetNext(pos);
			pBlock->SetX(x);
			pBlock->CalcPinCoords();
			pBlock->Invalidate(this,REGION_COORD);
		}
//		Invalidate(0);
	}
}


void CFXGraphView::OnAlignTop()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnAlignTop");
	if (!m_Selected.IsEmpty()){
		int y = m_Selected.GetHead()->GetY();
		POSITION pos = m_Selected.GetHeadPosition();
		while(pos){
			CFXObject* pObject = m_Selected.GetNext(pos);
			if (y > pObject->GetY())
				y = pObject->GetY();
		}
		pos = m_Selected.GetHeadPosition();
		while (pos){
			CFXObject* pObject = m_Selected.GetNext(pos);
			pObject->SetY(y);
			pObject->Invalidate(this,REGION_COORD);
		}
//		Invalidate(0);
	}
}


CPoint CFXGraphView::GetNearestPoint(CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::GetNearestPoint");
	CFXGraphApp* pApp = (CFXGraphApp*)AfxGetApp();
	int xk = point.x / pApp->m_GridStep;
	int yk = point.y / pApp->m_GridStep;
	if (abs(point.x - xk*pApp->m_GridStep) >= pApp->m_GridStep/2)
		point.x = (xk+(point.x>0?1:-1))*pApp->m_GridStep;
	else
		point.x = xk*pApp->m_GridStep;
	if (abs(point.y - yk*pApp->m_GridStep) >= pApp->m_GridStep/2)
		point.y = (yk+(point.y>0?1:-1))*pApp->m_GridStep;
	else
		point.y = yk*pApp->m_GridStep;
	return point;
}


void CFXGraphView::UpdatePropertiesWnd(void)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::UpdatePropertiesWnd");
	CFXGraphDoc* pDoc = GetDocument();
	CMainFrame* frame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (m_Selected.GetSize() == 1){
		TracePrint(TRACE_LEVEL_1,"CFXGraphView::UpdatePropertiesWnd: Single selected");
		frame->m_wndProperties.UpdateProperties(m_Selected.GetHead());
	}
	else{
		TracePrint(TRACE_LEVEL_1,"CFXGraphView::UpdatePropertiesWnd: No selected");
		
		frame->m_wndProperties.UpdateProperties(NULL);
	}
}


void CFXGraphView::UpdateProperty(int nProperty, int v)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::UpdateProperty");
	CMainFrame* frame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	frame->m_wndProperties.UpdateProperty(nProperty,v);
}




void CFXGraphView::OnBlockInputpinAddLogical()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnBlockInputpinAddLogical");
	if (m_pCur){
		CFXBlock* pBlock = (CFXBlock*)m_pCur;
		pBlock->AddInputPin(Logical,_T(""));
		pBlock->Invalidate(this,REGION_LEFT);
//		Invalidate(0);
	}
}


void CFXGraphView::OnBlockPinRemove()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnBlockPinRemove");
	CFXGraphDoc* pDoc = (CFXGraphDoc*)GetDocument();
	if (pDoc->m_bDebug){
		AfxMessageBox(_T("������ ������� ��� �� ����� ������� �������"));
		return;
	}
	if (m_pCur){
		CFXPin* pPin = dynamic_cast<CFXPin*>(m_pCur);
		if (pPin){
			if (pPin->m_pParam && pPin->m_pParam->m_pPin){
				pPin->m_pParam->m_pPin = NULL;
			}
			pPin->Remove();
			pPin->m_pBlock->Invalidate(this,REGION_LEFT|REGION_RIGHT);
//			Invalidate(0);
			m_pCur = NULL;
		}
	}
}


void CFXGraphView::OnBlockInputpinAddFloat()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnBlockInputpinAddFloat");
	if (m_pCur){
		CFXBlock* pBlock = (CFXBlock*)m_pCur;
		pBlock->AddInputPin(Float,_T(""));
		pBlock->Invalidate(this,REGION_LEFT);
//		Invalidate(0);
	}
}


void CFXGraphView::OnBlockInputpinAddInt()
{
	TracePrint(TRACE_LEVEL_1,"OnBlockInputpinAddInt");
	if (m_pCur){
		CFXBlock* pBlock = (CFXBlock*)m_pCur;
		pBlock->AddInputPin(Int,_T(""));
		pBlock->Invalidate(this,REGION_LEFT);
//		Invalidate(0);
	}
}


void CFXGraphView::OnBlockOutputpinAddFloat()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnBlockOutputpinAddFloat");
	if (m_pCur){
		CFXBlock* pBlock = (CFXBlock*)m_pCur;
		pBlock->AddOutputPin(Float,_T(""));
//		Invalidate(0);
	}
}


void CFXGraphView::OnBlockOutputpinAddInt()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnBlockOutputpinAddInt");
	if (m_pCur){
		CFXBlock* pBlock = (CFXBlock*)m_pCur;
		pBlock->AddOutputPin(Int,_T(""));
		pBlock->Invalidate(this,REGION_RIGHT);
//		Invalidate(0);
	}
}


void CFXGraphView::OnBlockOutputpinAddLogical()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnBlockOutputpinAddLogical");
	if (m_pCur){
		CFXBlock* pBlock = (CFXBlock*)m_pCur;
		pBlock->AddOutputPin(Logical,_T(""));
		pBlock->Invalidate(this,REGION_RIGHT);
//		Invalidate(0);
	}
}

void CFXGraphView::OnShowLinks()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnShowLinks");
	m_bShowLinks = !m_bShowLinks;	
	Invalidate(0);
}


void CFXGraphView::OnLinkRemove()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLinkRemove");
	CFXLink* pLink = dynamic_cast<CFXLink*>(m_pCur);
	if (pLink){
		m_Selected.RemoveAll();
		pLink->Remove();
		m_pCur = NULL;
		Invalidate(0);
	}
}


void CFXGraphView::OnBlockRemove()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnBlockRemove");
	CFXGraphDoc* pDoc = (CFXGraphDoc*)GetDocument();
	if (pDoc->m_bDebug){
		AfxMessageBox(_T("������ ������� ���� �� ����� ������� �������"));
		return;
	}
	CFXBlock* pBlock = dynamic_cast<CFXBlock*>(m_pCur);
	if (pBlock){
		pDoc->OnRemoveBlock(pBlock);
		pBlock->RemoveBlock();
		m_Selected.RemoveAll();
		m_pCur = NULL;
		Invalidate(0);
	}
}




void CFXGraphView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnLButtonDblClk");
	CFXGraphDoc* pDoc = GetDocument();
	int color1 = m_Mem1.GetPixel(point);
	int id = color1 & MASK1_ID;
	if (id){
		CFXBlockFunctional* pFunc = dynamic_cast<CFXBlockFunctional*>(m_pBlock->GetByID(id));
		if (pFunc){
			pDoc->OpenBlock(pFunc);
			return;
		}
		CFXBlockComment* pComment = dynamic_cast<CFXBlockComment*>(m_pBlock->GetByID(id));
		if (pComment){
			CCommentDlg dlg;
			dlg.m_Comment = pComment->GetComment();
			if (dlg.DoModal() == IDOK){
				pComment->SetComment(dlg.m_Comment);
				Invalidate(0);
			}
		}
	}
	
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������

	CView::OnLButtonDblClk(nFlags, point);
}


CFXBlock* CFXGraphView::AddBlock(DWORD ID, CPoint point)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::AddBlock");
	CFXBlock* pBlock;
	switch(ID){
		case BLOCK_FUNCTIONAL:
			pBlock = new CFXBlockFunctional(m_pBlock);
			break;
		case BLOCK_LOGICAL_AND:
			pBlock = new CFXBlockLogicalAnd(m_pBlock);
			break;
		case BLOCK_LOGICAL_OR:
			pBlock = new CFXBlockLogicalOr(m_pBlock);
			break;
		case BLOCK_LOGICAL_NOT:
			pBlock = new CFXBlockLogicalNot(m_pBlock);
			break;
		case BLOCK_LOGICAL_XOR:
			pBlock = new CFXBlockLogicalXor(m_pBlock);
			break;
		case BLOCK_CONTROLLER_NIMOD01:
			pBlock = new CFXBlockControllerNiMod01(m_pBlock);
			break;
		case BLOCK_MATH_INT_ADD:
			pBlock = new CFXBlockMathIntAdd(m_pBlock);
			break;
		case BLOCK_MATH_INT_SUB:
			pBlock = new CFXBlockMathIntSub(m_pBlock);
			break;
		case BLOCK_MATH_INT_MUL:
			pBlock = new CFXBlockMathIntMul(m_pBlock);
			break;
		case BLOCK_MATH_INT_DIV:
			pBlock = new CFXBlockMathIntDiv(m_pBlock);
			break;
		case BLOCK_MATH_INT_MOD:
			pBlock = new CFXBlockMathIntMod(m_pBlock);
			break;
		case BLOCK_MATH_INT_ABS:
			pBlock = new CFXBlockMathIntAbs(m_pBlock);
			break;
		case BLOCK_MATH_INT_EQUAL:
			pBlock = new CFXBlockMathIntEqual(m_pBlock);
			break;
		case BLOCK_MATH_INT_GREAT:
			pBlock = new CFXBlockMathIntGreat(m_pBlock);
			break;
		case BLOCK_MATH_INT_GREATEQUAL:
			pBlock = new CFXBlockMathIntGreatEqual(m_pBlock);
			break;
		case BLOCK_MATH_INT_LESS:
			pBlock = new CFXBlockMathIntLess(m_pBlock);
			break;
		case BLOCK_MATH_INT_LESSEQUAL:
			pBlock = new CFXBlockMathIntLessEqual(m_pBlock);
			break;
		case BLOCK_MATH_INT_NOTEQUAL:
			pBlock = new CFXBlockMathIntNotEqual(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_ADD:
			pBlock = new CFXBlockMathFloatAdd(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_SUB:
			pBlock = new CFXBlockMathFloatSub(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_MUL:
			pBlock = new CFXBlockMathFloatMul(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_DIV:
			pBlock = new CFXBlockMathFloatDiv(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_FLOOR:
			pBlock = new CFXBlockMathFloatFloor(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_ROUND:
			pBlock = new CFXBlockMathFloatRound(m_pBlock);
			break;
		case BLOCK_MATH_COS:
			pBlock = new CFXBlockMathCos(m_pBlock);
			break;
		case BLOCK_MATH_SIN:
			pBlock = new CFXBlockMathSin(m_pBlock);
			break;
		case BLOCK_MATH_TAN:
			pBlock = new CFXBlockMathTan(m_pBlock);
			break;
		case BLOCK_MATH_SQRT:
			pBlock = new CFXBlockMathSqrt(m_pBlock);
			break;
		case BLOCK_MATH_POW:
			pBlock = new CFXBlockMathPow(m_pBlock);
			break;
		case BLOCK_MATH_LOG:
			pBlock = new CFXBlockMathLog(m_pBlock);
			break;
		case BLOCK_MATH_LOG10:
			pBlock = new CFXBlockMathLog10(m_pBlock);
			break;
		case BLOCK_MATH_ACOS:
			pBlock = new CFXBlockMathAcos(m_pBlock);
			break;
		case BLOCK_MATH_ASIN:
			pBlock = new CFXBlockMathAsin(m_pBlock);
			break;
		case BLOCK_MATH_ATAN:
			pBlock = new CFXBlockMathAtan(m_pBlock);
			break;
		case BLOCK_MATH_EXP:
			pBlock = new CFXBlockMathExp(m_pBlock);
			break;

		case BLOCK_MATH_CAST_FLOAT_INT:
			pBlock = new CFXBlockMathCastFloatInt(m_pBlock);
			break;
		case BLOCK_MATH_CAST_INT_FLOAT:
			pBlock = new CFXBlockMathCastIntFloat(m_pBlock);
			break;
		case BLOCK_COMMENT:
			pBlock = new CFXBlockComment(m_pBlock);
			break;
		case BLOCK_MATH_BITWISE_AND:
			pBlock = new CFXBlockMathBitwiseAnd(m_pBlock);
			break;
		case BLOCK_MATH_BITWISE_OR:
			pBlock = new CFXBlockMathBitwiseOr(m_pBlock);
			break;
		case BLOCK_MATH_BITWISE_XOR:
			pBlock = new CFXBlockMathBitwiseXor(m_pBlock);
			break;
		case BLOCK_MATH_BITWISE_NOT:
			pBlock = new CFXBlockMathBitwiseNot(m_pBlock);
			break;
		case BLOCK_MATH_BITWISE_SHIFT_LEFT:
			pBlock = new CFXBlockMathBitwiseShiftLeft(m_pBlock);
			break;
		case BLOCK_MATH_BITWISE_SHIFT_RIGHT:
			pBlock = new CFXBlockMathBitwiseShiftRight(m_pBlock);
			break;
		case BLOCK_MATH_BITWISE_PACK:
			pBlock = new CFXBlockMathBitwisePack(m_pBlock);
			break;
		case BLOCK_MATH_BITWISE_UNPACK:
			pBlock = new CFXBlockMathBitwiseUnpack(m_pBlock);
			break;
		case BLOCK_EXTENSION_NIMODA01:
			pBlock = new CFXBlockExtensionA01(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_GREAT:
			pBlock = new CFXBlockMathFloatGreat(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_GREATEQUAL:
			pBlock = new CFXBlockMathFloatGreatEqual(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_LESS:
			pBlock = new CFXBlockMathFloatLess(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_LESSEQUAL:
			pBlock = new CFXBlockMathFloatLessEqual(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_EQUAL:
			pBlock = new CFXBlockMathFloatEqual(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_NOTEQUAL:
			pBlock = new CFXBlockMathFloatNotEqual(m_pBlock);
			break;
		case BLOCK_MATH_FLOAT_ABS:
			pBlock = new CFXBlockMathFloatAbs(m_pBlock);
			break;
		case BLOCK_COMPARATOR_UP:
			pBlock = new CFXBlockComparatorUp(m_pBlock);
			break;
		case BLOCK_COMPARATOR_DOWN:
			pBlock = new CFXBlockComparatorDown(m_pBlock);
			break;
		case BLOCK_LOGICAL_RISING_EDGE:
			pBlock = new CFXBlockLogicalRisingEdge(m_pBlock);
			break;
		case BLOCK_LOGICAL_FALLING_EDGE:
			pBlock = new CFXBlockLogicalFallingEdge(m_pBlock);
			break;
		case BLOCK_LOGICAL_TRIGGER_RS:
			pBlock = new CFXBlockLogicalTriggerRS(m_pBlock);
			break;
		case BLOCK_LOGICAL_TRIGGER_SR:
			pBlock = new CFXBlockLogicalTriggerSR(m_pBlock);
			break;
		case BLOCK_LOGICAL_TRIGGER_RS_RE:
			pBlock = new CFXBlockLogicalTriggerRSRisingEdge(m_pBlock);
			break;
		case BLOCK_COUNTER:
			pBlock = new CFXBlockCounter(m_pBlock);
			break;
		case BLOCK_ANTIBOUNCE:
			pBlock = new CFXBlockAntiBounce(m_pBlock);
			break;
		case BLOCK_DELAY_ON:
			pBlock = new CFXBlockDelayOn(m_pBlock);
			break;
		case BLOCK_DELAY_OFF:
			pBlock = new CFXBlockDelayOff(m_pBlock);
			break;
		case BLOCK_SENSOR_CURRENT:
			pBlock = new CFXBlockSensorCurrent(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_2W_M50:
			pBlock = new CFXBlockSensorTRD2WM50(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_2W_M100:
			pBlock = new CFXBlockSensorTRD2WM100(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_2W_P50:
			pBlock = new CFXBlockSensorTRD2WP50(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_2W_P100:
			pBlock = new CFXBlockSensorTRD2WP100(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_2W_PT100:
			pBlock = new CFXBlockSensorTRD2WPt100(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_2W_PT500:
			pBlock = new CFXBlockSensorTRD2WPt500(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_2W_PT1000:
			pBlock = new CFXBlockSensorTRD2WPt1000(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_3W_M50:
			pBlock = new CFXBlockSensorTRD3WM50(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_3W_M100:
			pBlock = new CFXBlockSensorTRD3WM100(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_3W_P50:
			pBlock = new CFXBlockSensorTRD3WP50(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_3W_P100:
			pBlock = new CFXBlockSensorTRD3WP100(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_3W_PT100:
			pBlock = new CFXBlockSensorTRD3WPt100(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_3W_PT500:
			pBlock = new CFXBlockSensorTRD3WPt500(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_3W_PT1000:
			pBlock = new CFXBlockSensorTRD3WPt1000(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_4W_M50:
			pBlock = new CFXBlockSensorTRD4WM50(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_4W_M100:
			pBlock = new CFXBlockSensorTRD4WM100(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_4W_P50:
			pBlock = new CFXBlockSensorTRD4WP50(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_4W_P100:
			pBlock = new CFXBlockSensorTRD4WP100(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_4W_PT100:
			pBlock = new CFXBlockSensorTRD4WPt100(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_4W_PT500:
			pBlock = new CFXBlockSensorTRD4WPt500(m_pBlock);
			break;
		case BLOCK_SENSOR_TRD_4W_PT1000:
			pBlock = new CFXBlockSensorTRD4WPt1000(m_pBlock);
			break;
		default:
			return NULL;
	}
	pBlock->SetXY(point);

	m_pBlock->AddBlock(pBlock);
	return pBlock;
}


bool CFXGraphView::OnUpdateProperty(int nProperty, variant_t& value)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnUpdateProperty");
	if (!m_pCur)
		return false;
	CFXGraphDoc* pDoc = (CFXGraphDoc*)GetDocument();
	CFXPin* pPin;
	switch(nProperty){
		case PROP_COORDX:	
			if (value.vt != VT_I4)
				return false;
			m_pCur->SetX((int)value);
			m_pCur->Invalidate(this,REGION_COORD);
			return true;
		case PROP_COORDY:
			if (value.vt != VT_I4)
				return false;
			m_pCur->SetY((int)value);
			m_pCur->Invalidate(this,REGION_COORD);
			return true;
		case PROP_NAME:
			if (value.vt != VT_BSTR)
				return false;
			m_pCur->SetName(CString(value));
			pPin = dynamic_cast<CFXPin*>(m_pCur);
			m_pCur->Invalidate(this,REGION_NAME);
			return true;
		case PROP_FUNCNAME:
			if (value.vt != VT_BSTR)
				return false;
			pPin = dynamic_cast<CFXPin*>(m_pCur);
			if (pPin){
				pPin->SetFuncName(CString(value));
				pPin->Invalidate(this,REGION_FUNCNAME);
				return true;
			}
			return false;
		case PROP_PARAM:
			if (value.vt != VT_BSTR)
				return false;
			pPin = dynamic_cast<CFXPin*>(m_pCur);
			if (pPin){
				CFXParam* pParam = NULL;
				if (pPin->m_Dir == Input)
					pParam = pDoc->GetInputParam(CString(value));
				else
					pParam = pDoc->GetOutputParam(CString(value));
				pPin->m_bConst = false;
				pPin->SetParam(pParam);
				pPin->Invalidate(this,REGION_VALUE);
				return true;
			}
			return false;
		case PROP_CONST:
			pPin = dynamic_cast<CFXPin*>(m_pCur);
			pPin->m_bConst = (bool)value;
			if (value){
				pPin->SetParam(NULL);
			}
			pPin->Invalidate(this,REGION_VALUE);
			return TRUE;
		case PROP_VALUE:
			pPin = dynamic_cast<CFXPin*>(m_pCur);
			pPin->SetValue(value);
			pPin->Invalidate(this,REGION_VALUE);
			return true;
		case PROP_FORMAT:
			pPin = dynamic_cast<CFXPin*>(m_pCur);
			pPin->m_Format = value;
			pPin->Invalidate(this,REGION_VALUE);
			return true;
	}
	return FALSE;
}


//void CFXGraphView::OnIdclose()
//{
//	TracePrint("View is closed");
//}



void CFXGraphView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	TracePrint(TRACE_LEVEL_2,"CFXGraphView::OnActivateView bActivate=%d pActivateView=%p pDeactiveView=%p\n",bActivate,pActivateView,pDeactiveView);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->MDIGetActive();
	if (pChildFrame){
		CFXGraphDoc* pDoc = (CFXGraphDoc*)pChildFrame->GetActiveDocument();
		if (pDoc){
			pMainFrame->m_wndFileView.UpdateFileView(pDoc);
//			UpdatePropertiesWnd();
		}
		else{
			pMainFrame->m_wndFileView.UpdateFileView(NULL);
//			UpdatePropertiesWnd();
		}
	}
	else
		pMainFrame->m_wndFileView.UpdateFileView(NULL);
	//if (bActivate)
	//	pMainFrame->m_wndFileView.UpdateFileView((CFXGraphDoc*)pActivateView->GetDocument());
	//else
	//	if (!pActivateView)
	//		pMainFrame->m_wndFileView.UpdateFileView(NULL);
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CFXGraphView::OnInitialUpdate()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnInitialUpdate");
	CView::OnInitialUpdate();
	if (!m_ToolTip.Create(this,TTS_ALWAYSTIP)){
		TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnInitialUpdate: Failed to create tooltip");
		return;
	}
	if (!m_ToolTip.AddTool(this)){
		TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnInitialUpdate: Failed to AddTool");
		return;
	}
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
}


BOOL CFXGraphView::PreTranslateMessage(MSG* pMsg)
{
	TracePrint(TRACE_LEVEL_2,"CFXGraphView::PreTranslateMessage");
    if (::IsWindow(m_ToolTip.m_hWnd) && pMsg->hwnd == m_hWnd)
    {
        switch(pMsg->message)
        {
        case WM_LBUTTONDOWN:    
        case WM_MOUSEMOVE:
        case WM_LBUTTONUP:    
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:    
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            m_ToolTip.RelayEvent(pMsg);
            break;
        }
    }
    return CView::PreTranslateMessage(pMsg);
}



void CFXGraphView::OnBlockWebhelp()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnBlockWebhelp");
	ASSERT(m_pCur);
	if (m_pCur){
		int id = m_pCur->GetClassID();
		CString url = CFXObject::GetClassDescriptor(id);
		CString host = _T(WEBHELP_URL);
		host = host + "/doku.php?id=FXGraph:"+url;
		::ShellExecute(NULL,_T("open"),host,NULL,NULL,SW_SHOWNORMAL);

	}
}


void CFXGraphView::OnBlockBreakpoint()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnBlockBreakpoint");
	if (m_pCur){
		CFXBlock* pBlock = dynamic_cast<CFXBlock*>(m_pCur);
		if (pBlock){
			pBlock->m_bBreakPoint = !pBlock->m_bBreakPoint;
			Invalidate(0);
		}
	}
}


void CFXGraphView::OnBlockPinRemoveLinks()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphView::OnBlockPinRemoveLinks");
	if (m_pCur){
		CFXPin* pPin = dynamic_cast<CFXPin*>(m_pCur);
		if (pPin){ 
			pPin->RemoveLinks();
			Invalidate(0);
		}
	}
}



void CFXGraphView::UnselectAll(void)
{
	while (!m_Selected.IsEmpty()){
		CFXObject* pObj = m_Selected.RemoveTail();

		pObj->Invalidate(this,REGION_BLOCK);
	}
}


void CFXGraphView::SelectObject(CFXObject* pObject)
{
	if (!IsSelected(pObject)){
		m_Selected.AddTail(pObject);
		pObject->Invalidate(this,REGION_BLOCK);
	}
}


void CFXGraphView::SetActiveObject(CFXObject* pObject)
{
	m_pCur = pObject;
	SelectObject(pObject);
	SetViewAt(pObject);
	UpdatePropertiesWnd();
}


void CFXGraphView::SetViewAt(CFXObject* pObject)
{
	CFXBlock* pBlock = dynamic_cast<CFXBlock*>(pObject);
	if (pBlock){
		this->m_x = pBlock->GetX()+pBlock->GetWidth()/2;
		this->m_y = pBlock->GetY()+pBlock->GetHeight()/2;
	}
	else{
		this->m_x = pObject->GetX();
		this->m_y = pObject->GetY();
	}
	this->Invalidate(0);
}


//void CFXGraphViewScenario::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
//{
//	// TODO: �������� ������������������ ��� ��� ����� �������� ������
//}


void CFXGraphViewScenario::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphViewScenario::OnUpdate");
}
BEGIN_MESSAGE_MAP(CFXGraphViewScenario, CEditView)
	ON_CONTROL_REFLECT(EN_CHANGE, &CFXGraphViewScenario::OnEnChange)
	ON_CONTROL_REFLECT(EN_UPDATE, &CFXGraphViewScenario::OnEnUpdate)
END_MESSAGE_MAP()


void CFXGraphViewScenario::OnEnChange()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphViewScenario::OnEnChange");
	CFXGraphDoc* pDoc = (CFXGraphDoc*)GetDocument();
	GetEditCtrl().GetWindowTextW(pDoc->m_DebugScenario);
}


void CFXGraphViewScenario::OnEnUpdate()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphViewScenario::OnEnUpdate");
}