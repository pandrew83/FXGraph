#include "StdAfx.h"
#include "FXLink.h"
#include "FXPin.h"
#include "FXGraphView.h"
#include "FXBlockFunctional.h"
IMPLEMENT_SERIAL(CFXLink,CFXObject,1)

CFXLink::CFXLink(void)
{
}

CFXLink::CFXLink(CFXBlock* pBlock,CFXPin* pPinOut, CFXPin* pPinIn):CFXObject(pBlock,_T("")){
	m_pOut = pPinOut;
	m_pIn = pPinIn;
	m_pIn->AddConnectedPin(pPinOut);
}

CFXLink::~CFXLink(void)
{
//	m_pPin2->RemoveConnectedPin(m_pPin1);
}

void CFXLink::Serialize(CArchive&ar){
	CFXObject::Serialize(ar);
	if (ar.IsStoring()){
		ar << m_pOut->m_ID;
		ar << m_pIn->m_ID;
	}
	else{
		CFXGraphDoc* pDoc = (CFXGraphDoc*)ar.m_pDocument;
		int id;
		ar >> id;
		m_pOut = (CFXPin*)id;
		ar >> id;
		m_pIn = (CFXPin*)id;

	}
}

void CFXLink::Invalidate(CFXGraphView* pView, int regions){
//	CDC* pDC = pView->GetDC();
	pView->InvalidateRect(&m_Rect1,false);
	pView->InvalidateRect(&m_Rect2,false);
	pView->InvalidateRect(&m_Rect3,false);
	m_pOut->Invalidate(pView,REGION_PIN|REGION_NAME|REGION_VALUE);
	m_pIn->Invalidate(pView,REGION_PIN|REGION_NAME|REGION_VALUE);

	CPoint p1 = pView->Logic2Local(m_pOut->GetXY());
	CPoint p2 = pView->Logic2Local(m_pIn->GetXY());
	CPoint pz = pView->Logic2Local(CPoint(m_X,m_Y));

	m_Rect1 = CRect(p1.x,p1.y,pz.x+1,p1.y+1);
	m_Rect2 = CRect(pz.x,p1.y,pz.x+1,p2.y+1);
	m_Rect3 = CRect(pz.x,p2.y,p2.x+1,p2.y+1);

	pView->InvalidateRect(&m_Rect1,false);
	pView->InvalidateRect(&m_Rect2,false);
	pView->InvalidateRect(&m_Rect3,false);
}

void CFXLink::Draw(CFXGraphView*pView){
	bool selected = pView->IsSelected(this);
	CPoint p1 = pView->Logic2Local(m_pOut->GetXY());
	CPoint p2 = pView->Logic2Local(m_pIn->GetXY());
	CPoint pz = pView->Logic2Local(CPoint(m_X,m_Y));

	m_Rect1 = CRect(p1.x,p1.y,pz.x+1,p1.y+1);
	m_Rect2 = CRect(pz.x,p1.y,pz.x+1,p2.y+1);
	m_Rect3 = CRect(pz.x,p2.y,p2.x+1,p2.y+1);
	CPen pen(PS_SOLID,1,selected?COLOR_SELECTED:LINK_COLOR);
	pView->m_pDC->SelectObject(pen);
	
	pView->m_pDC->MoveTo(p1);
	pView->m_pDC->LineTo(CPoint(pz.x,p1.y));
	pView->m_pDC->LineTo(CPoint(pz.x,p2.y));
	pView->m_pDC->LineTo(p2);
	pen.DeleteObject();

	pen.CreatePen(PS_SOLID,PEN_WIDTH,selected?m_ID|MASK1_SELECTED:m_ID);
	pView->m_Mem1.SelectObject(pen);
	pView->m_Mem1.MoveTo(p1);
	pView->m_Mem1.LineTo(CPoint(pz.x,p1.y));
	pView->m_Mem1.LineTo(CPoint(pz.x,p2.y));
	pView->m_Mem1.LineTo(p2);

	pen.DeleteObject();
}


void CFXLink::Remove(void)
{
	CFXBlockFunctional* pBlock = dynamic_cast<CFXBlockFunctional*>(m_pBlock);
	if (pBlock)
		pBlock->RemoveLink(this);
}


void CFXLink::AfterSerialize(){
	m_pOut = (CFXPin*)m_pBlock->GetByID((int)m_pOut);
	m_pIn = (CFXPin*)m_pBlock->GetByID((int)m_pIn);
	m_pIn->AddConnectedPin(m_pOut);
}
