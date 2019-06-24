#include "StdAfx.h"
#include "FXBlock.h"
#include "FXBlockFunctional.h"

#include "FXGraphView.h"
#include "PropertiesWnd.h"
#include <typeinfo>
IMPLEMENT_SERIAL(CFXBlock,CFXObject,1)

void box(CDC*pDC, int x, int y, int d,COLORREF color){
	TracePrint(TRACE_LEVEL_1,"box x=%d y=%d d=%d",x-d/2,y-d/2,d);
	COLORREF bg = pDC->GetBkColor();
	pDC->FillSolidRect(x-d/2,y-d/2,d,d,color);
	pDC->SetBkColor(bg);
}

void box(CDC*pDC, CPoint p, int d, COLORREF color){
	box(pDC,p.x,p.y,d,color);
}

void CFXBlock::Create(CFXObject*pObject) 
{
	CFXObject::Create(pObject);
	m_bCalc = true;
	m_bBreakPoint = false;
	m_PinInMinCount = 0;
	m_PinOutMinCount = 0;
	m_PinInMaxCount = 32;
	m_PinOutMaxCount = 32;
	m_MinHeight = 75;
	m_MinWidth = 100;
	m_Height = m_MinHeight;
	m_Width = m_MinWidth;
	m_CalcOrder = 0;
	m_pNextBlock = NULL;
}


CFXBlock::~CFXBlock(void)
{
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		delete m_InputPins.GetNext(pos);
	}
	m_InputPins.RemoveAll();
	pos = m_OutputPins.GetHeadPosition();
	while (pos){
		delete m_OutputPins.GetNext(pos);
	}
	m_OutputPins.RemoveAll();
}

int CFXBlock::GetSysTicks()
{
	return GetActiveDocument()->m_SysTick;
}

CFXPin* CFXBlock::AddInputPin(CFXPinType type, CString funcName, bool bAllowConst, bool bAllowParam, bool bConst, int nFormat, bool bLinkable){
	if (m_InputPins.GetCount()+1 > m_PinInMaxCount)
		return NULL;
	if (!m_InputPinTypes.Find(type))
		return NULL;
	CFXPin* pPin = new CFXPin(Input, type, funcName, this,bAllowConst,bAllowParam,bConst,nFormat,bLinkable);
	m_InputPins.AddTail(pPin);
	CalcPinCoords();
	return pPin;
}
void CFXBlock::GetPinLinks(CListLink& lst, CFXPin* pPin){
	((CFXBlockFunctional*)m_pBlock)->GetPinLinks(lst,pPin);
}

CFXPin* CFXBlock::AddOutputPin(CFXPinType type, CString funcName, bool bAllowConst, bool bAllowParam, bool bConst, int nFormat, bool bLinkable){
	if (m_OutputPins.GetCount()+1 > m_PinOutMaxCount)
		return NULL;
	if (!m_OutputPinTypes.Find(type))
		return NULL;
	CFXPin* pPin = new CFXPin(Output, type, funcName, this, bAllowConst, bAllowParam, bConst, nFormat,bLinkable);
//	pPin->m_ID = m_pBlock->GetNewID();
	CString name;
	name.Format(_T("pin.%d"),pPin->m_ID);
	pPin->SetName(name);
	m_OutputPins.AddTail(pPin);
	CalcPinCoords();
	return pPin;
}

CFXObject* CFXBlock::GetByID(int id){
	if (m_ID == id)
		return this;
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		if (pPin->m_ID == id)
			return pPin;
	}
	pos = m_OutputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_OutputPins.GetNext(pos);
		if (pPin->m_ID == id)
			return pPin;
		
	}
	return NULL;
}
bool CFXBlock::Calc(){
	// Обновление значения входных пинов
	POSITION pos = m_InputPins.GetHeadPosition();
	CFXGraphDoc* pDoc = m_pBlock->GetActiveDocument();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		if (!pPin->m_bConst && !pPin->m_pParam){
			ASSERT(pPin->GetConnectedPinsCount() == 1);

			POSITION pos = pPin->GetConnectedPins();
			CFXPin* pSrcPin = pPin->GetNextConnectedPin(pos);
			pPin->SetValue(pSrcPin->GetValue());
		}
		if (pPin->m_pParam){
			pPin->SetValue(pPin->m_pParam->m_Value);
		}
	}
	return true;
}

void CFXBlock::CalcPinCoords(){
	POSITION pos;
	
	int k = 1;
	pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		pPin->SetXY(m_X-PIN_SIZE/2-PIN_DISTANCE, m_Y+k*m_Height/(m_InputPins.GetCount()+1));
		k++;
	}
	k = 1;
	pos = m_OutputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_OutputPins.GetNext(pos);
		pPin->SetXY(m_X+m_Width+PIN_SIZE/2+PIN_DISTANCE, m_Y+k*m_Height/(m_OutputPins.GetCount()+1));
		k++;
	}
	
}

void InvalidateBox(CFXGraphView* pView, CPoint p, int size){
	CRect rect;
	rect.left = p.x-size/2;
	rect.top = p.y-size/2;
	rect.right = p.x+size/2+1;
	rect.bottom = p.y+size/2+1;
	pView->InvalidateRect(&rect,false);
}

void CFXBlock::InvalidateBlock(CFXGraphView* pView){
	TracePrint(TRACE_LEVEL_2,"CFXBlock::InvalidateBlock Rect(%d,%d,%d,%d)",m_RectBlock.left,m_RectBlock.top,m_RectBlock.right,m_RectBlock.bottom);

	// Invalidate старый блок
	pView->InvalidateRect(m_RectBlock,false);
	// Invalidate старые маркеры
	InvalidateBox(pView,CPoint(m_RectBlock.left,m_RectBlock.top),CORNER_SIZE);
	InvalidateBox(pView,CPoint(m_RectBlock.left,m_RectBlock.bottom-1),CORNER_SIZE);
	InvalidateBox(pView,CPoint(m_RectBlock.right-1,m_RectBlock.top),CORNER_SIZE);
	InvalidateBox(pView,CPoint(m_RectBlock.right-1,m_RectBlock.bottom-1),CORNER_SIZE);
	// Invalidate новый блок

	CPoint p1 = pView->Logic2Local(CPoint(m_X,m_Y));
	CPoint p2 = pView->Logic2Local(CPoint(m_X+m_Width,m_Y));
	CPoint p3 = pView->Logic2Local(CPoint(m_X+m_Width,m_Y+m_Height));
	CPoint p4 = pView->Logic2Local(CPoint(m_X,m_Y+m_Height));
	m_RectBlock = CRect(p1.x,p1.y,p3.x+1,p3.y+1);
	pView->InvalidateRect(&m_RectBlock,false);
	InvalidateBox(pView,p1,CORNER_SIZE);
	InvalidateBox(pView,p2,CORNER_SIZE);
	InvalidateBox(pView,p3,CORNER_SIZE);
	InvalidateBox(pView,p4,CORNER_SIZE);
}

void CFXBlock::InvalidateName(CFXGraphView* pView){
	CDC* pDC = pView->GetDC();
	pView->InvalidateRect(m_RectName);
	CPoint p = pView->Logic2Local(CPoint(m_X,m_Y));

	LOGFONT lf;
	memset(&lf,0,sizeof(LOGFONT));
	lf.lfHeight = 14*pView->m_Scale/100;
	wcscpy(lf.lfFaceName,_T("Arial"));
	CFont font;
	CPen dcPen;
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(font);

	CSize sizeName = pDC->GetTextExtent(m_Name);
	m_RectName = CRect(p.x+1,p.y+1,p.x+m_RectBlock.Width()-2,p.y+1+sizeName.cy);

	pView->InvalidateRect(&m_RectName);

	font.DeleteObject();
	pView->ReleaseDC(pDC);
}

void CFXBlock::InvalidateLeft(CFXGraphView* pView){
	TracePrint(TRACE_LEVEL_2,"CFXBlock::InvalidateLeft Rect(%d,%d,%d,%d)",m_RectLeft.left,m_RectLeft.top,m_RectLeft.right,m_RectLeft.bottom);
	pView->InvalidateRect(&m_RectLeft,false);

	m_RectLeft.top = m_RectBlock.top;
	m_RectLeft.bottom = m_RectBlock.bottom;
	
	m_RectLeft.right = m_RectBlock.left-1;
	POSITION pos = m_InputPins.GetHeadPosition();

	int left = 1000000000;
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		pPin->Invalidate(pView,REGION_NAME|REGION_VALUE|REGION_PIN);
		if (pPin->m_RectName.left < left)
			left = pPin->m_RectName.left;
		if (pPin->m_RectValue.left < left)
			left = pPin->m_RectValue.left;
	}
	m_RectLeft.left = left;
}

void CFXBlock::InvalidateRight(CFXGraphView* pView){
	TracePrint(TRACE_LEVEL_2,"CFXBlock::InvalidateRight Rect(%d,%d,%d,%d)",m_RectRight.left,m_RectRight.top,m_RectRight.right,m_RectRight.bottom);
	pView->InvalidateRect(&m_RectRight,false);
	
	m_RectRight.top = m_RectBlock.top;
	m_RectRight.bottom = m_RectBlock.bottom;
	
	m_RectRight.left = m_RectBlock.right+1;
	POSITION pos = m_OutputPins.GetHeadPosition();
	int r = -1000000000;
	while (pos){
		CFXPin* pPin = m_OutputPins.GetNext(pos);
		pPin->Invalidate(pView,REGION_NAME|REGION_VALUE|REGION_PIN);
		if (pPin->m_RectName.right > r)
			r = pPin->m_RectName.right;
		if (pPin->m_RectValue.right > r)
			r = pPin->m_RectValue.right;
	}
	m_RectRight.right = r;
}

void CFXBlock::InvalidateLinks(CFXGraphView* pView){
	POSITION pos;
	pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		CListLink lst;
		pPin->GetPinLinks(lst);
		POSITION pos1 = lst.GetHeadPosition();
		while (pos1){
			CFXLink* pLink = lst.GetNext(pos1);
			pLink->Invalidate(pView,REGION_LINK);
		}
	}
	pos = m_OutputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_OutputPins.GetNext(pos);
		CListLink lst;
		pPin->GetPinLinks(lst);
		POSITION pos1 = lst.GetHeadPosition();
		while (pos1){
			CFXLink* pLink = lst.GetNext(pos1);
			pLink->Invalidate(pView,REGION_LINK);
		}
	}
}

void CFXBlock::Invalidate(CFXGraphView* pView, int regions){
	
	if (regions & REGION_NAME)
		InvalidateName(pView);
	if (regions & REGION_BLOCK || regions & REGION_COORD)
		InvalidateBlock(pView);
	if (regions & REGION_LEFT || regions & REGION_COORD)
		InvalidateLeft(pView);
	if (regions & REGION_RIGHT || regions & REGION_COORD)
		InvalidateRight(pView);
	if (regions & REGION_LINK || regions & REGION_COORD)
		InvalidateLinks(pView);
	if (regions & REGION_VALUE){
		POSITION pos;
		pos = m_InputPins.GetHeadPosition();
		while (pos){
			CFXPin* pPin = m_InputPins.GetNext(pos);
			pPin->Invalidate(pView,regions);
		}
		pos = m_OutputPins.GetHeadPosition();
		while (pos){
			CFXPin* pPin = m_OutputPins.GetNext(pos);
			pPin->Invalidate(pView,regions);
		}
	}
}

void CFXBlock::Draw(CFXGraphView*pView){
	CFXGraphDoc* pDoc = (CFXGraphDoc*)pView->GetDocument();
	bool isDebugBlock = pDoc->m_pDebugCur == this;
	bool isSelected = pView->IsSelected(this);
	CPoint p1 = pView->Logic2Local(CPoint(m_X,m_Y));
	CPoint p2 = pView->Logic2Local(CPoint(m_X+m_Width,m_Y));
	CPoint p3 = pView->Logic2Local(CPoint(m_X+m_Width,m_Y+m_Height));
	CPoint p4 = pView->Logic2Local(CPoint(m_X,m_Y+m_Height));
	TracePrint(TRACE_LEVEL_1,"Block (%d,%d)",p2.x,p2.y);
	COLORREF blockColor;
	if (isDebugBlock)
		blockColor = COLOR_DEBUG;
	else
		if (isSelected)
			blockColor = COLOR_SELECTED;
		else
			blockColor = COLOR_NORMAL;
	CBrush brush1;
//	CPoint p = pView->Logic2Local(CPoint(m_X,m_Y));
	CPen dcPen(PS_SOLID,1,blockColor);
	// На экран
	CBrush brush(RGB(255,255,255));

	LOGFONT lf;
	memset(&lf,0,sizeof(LOGFONT));
	lf.lfHeight = 14*pView->m_Scale/100;
	wcscpy(lf.lfFaceName,_T("Arial"));
	CFont font;
	font.CreateFontIndirect(&lf);
	pView->m_pDC->SelectObject(font);
	pView->m_pDC->SelectObject(dcPen);
	pView->m_pDC->SelectObject(brush);
	m_RectBlock = CRect(p1.x,p1.y,p3.x+1,p3.y+1);
	pView->m_pDC->Rectangle(&m_RectBlock);
	CSize sizeCaption = pView->m_pDC->GetTextExtent(m_Name);
	m_RectName = CRect(p1.x+1,p1.y+1,p3.x,p1.y+sizeCaption.cy);
	pView->m_pDC->DrawText(m_Name,&m_RectName,DT_CENTER|DT_NOPREFIX);
	// Drawing calc order
	if (pDoc->IsDebug()){
		CString str;
		str.Format(_T("%d"),m_CalcOrder);
		CSize size = pView->m_pDC->GetTextExtent(str);
		CRect rectOrder(p1.x+1,p3.y-size.cy,p3.x,p3.y);
		pView->m_pDC->DrawText(str,&rectOrder,DT_CENTER|DT_NOPREFIX);
	}
	// Breapoint drawing
	if (m_bBreakPoint){
		int breakpointSize = m_RectName.Height();
		CPoint pt1 = pView->Logic2Local(CPoint(m_X+5,m_Y+5));
		CPoint pt2 = pView->Logic2Local(CPoint(m_X+13,m_Y+13));
		CRect rectBreakpoint(pt1.x,pt1.y,pt2.x+1,pt2.y+1);
		CPen pen(PS_SOLID,1,RGB(0xdf,0x6a,0x62));
		CBrush brush(RGB(0xdf,0x6a,0x62));
		pView->m_pDC->SelectObject(brush);
		pView->m_pDC->SelectObject(pen);
		pView->m_pDC->Ellipse(&rectBreakpoint);
		brush.DeleteObject();
		pen.DeleteObject();

	}
	//
	dcPen.DeleteObject();
	brush.DeleteObject();
	font.DeleteObject();
		// На слое 1
		pView->m_Mem1.FillSolidRect(&m_RectBlock,m_ID|(isSelected?MASK1_SELECTED:0));
		
		if (isSelected){
			// Рисуем маркеры
			box(pView->m_pDC,p1,CORNER_SIZE,COLOR_SELECTED);
			box(pView->m_pDC,p2,CORNER_SIZE,COLOR_SELECTED);
			box(pView->m_pDC,p3,CORNER_SIZE,COLOR_SELECTED);
			box(pView->m_pDC,p4,CORNER_SIZE,COLOR_SELECTED);

			CPen memPen1(PS_SOLID,PEN_WIDTH,m_ID|(isSelected?MASK1_SELECTED:0));
			CPen memPen2(PS_SOLID,PEN_WIDTH,MASK2_BORDER_TOP);
			pView->m_Mem1.SelectObject(memPen1);
			pView->m_Mem2.SelectObject(memPen2);
			
			// Рисует верхнюю линию блока в памяти
			pView->m_Mem1.MoveTo(p1);
			pView->m_Mem1.LineTo(p2);
			pView->m_Mem2.MoveTo(p1);
			pView->m_Mem2.LineTo(p2);
			memPen2.DeleteObject();

			memPen2.CreatePen(PS_SOLID,PEN_WIDTH,MASK2_BORDER_RIGHT);
			pView->m_Mem2.SelectObject(memPen2);
			pView->m_Mem1.MoveTo(p2);
			pView->m_Mem1.LineTo(p3);
			pView->m_Mem2.MoveTo(p2);
			pView->m_Mem2.LineTo(p3);
			memPen2.DeleteObject();
		
			memPen2.CreatePen(PS_SOLID,PEN_WIDTH,MASK2_BORDER_BOTTOM);
			pView->m_Mem2.SelectObject(memPen2);
			pView->m_Mem1.MoveTo(p4);
			pView->m_Mem1.LineTo(p3);
			pView->m_Mem2.MoveTo(p4);
			pView->m_Mem2.LineTo(p3);
			memPen2.DeleteObject();

			memPen2.CreatePen(PS_SOLID,PEN_WIDTH,MASK2_BORDER_LEFT);
			pView->m_Mem2.SelectObject(memPen2);
			pView->m_Mem1.MoveTo(p1);
			pView->m_Mem1.LineTo(p4);
			pView->m_Mem2.MoveTo(p1);
			pView->m_Mem2.LineTo(p4);
			memPen1.DeleteObject();
			memPen2.DeleteObject();

			box(&pView->m_Mem1,p1,CORNER_SIZE,m_ID|(isSelected?MASK1_SELECTED:0));
			box(&pView->m_Mem2,p1,CORNER_SIZE,MASK2_CORNER_TL);

			box(&pView->m_Mem1,p2,CORNER_SIZE,m_ID|(isSelected?MASK1_SELECTED:0));
			box(&pView->m_Mem2,p2,CORNER_SIZE,MASK2_CORNER_TR);

			box(&pView->m_Mem1,p3,CORNER_SIZE,m_ID|(isSelected?MASK1_SELECTED:0));
			box(&pView->m_Mem2,p3,CORNER_SIZE,MASK2_CORNER_BR);

			box(&pView->m_Mem1,p4,CORNER_SIZE,m_ID|(isSelected?MASK1_SELECTED:0));
			box(&pView->m_Mem2,p4,CORNER_SIZE,MASK2_CORNER_BL);
		}

		pView->m_pDC->SetPixel(p1,RGB(0,255,0));
		pView->m_pDC->SetPixel(p2,RGB(0,255,0));
		pView->m_pDC->SetPixel(p3,RGB(0,255,0));
		pView->m_pDC->SetPixel(p4,RGB(0,255,0));

		// Draw pinouts
		m_RectLeft.top = m_RectRight.top = m_RectBlock.top;
		m_RectLeft.bottom = m_RectRight.bottom = m_RectBlock.bottom;
	
		m_RectLeft.right = m_RectBlock.left-1;
		m_RectLeft.left = 1000000000;
		POSITION pos = m_InputPins.GetHeadPosition();
		while (pos){
			CFXPin* pPin = m_InputPins.GetNext(pos);
			pPin->Draw(pView);
			if (pPin->m_RectName.left < m_RectLeft.left)
				m_RectLeft.left = pPin->m_RectName.left;
			if (pPin->m_RectValue.left < m_RectLeft.left)
				m_RectLeft.left = pPin->m_RectValue.left;
		}
		m_RectRight.left = m_RectBlock.right+1;
		m_RectRight.right = -1000000000;
		pos = m_OutputPins.GetHeadPosition();
		while (pos){
			CFXPin* pPin = m_OutputPins.GetNext(pos);
			pPin->Draw(pView);
			if (pPin->m_RectName.right > m_RectRight.right)
				m_RectRight.right = pPin->m_RectName.right;
			if (pPin->m_RectValue.right > m_RectRight.right)
				m_RectRight.right = pPin->m_RectValue.right;
		}
	}


int CFXBlock::GetPropertyList(void)
{
	return PROPLIST_BLOCK;
}

void CFXBlock::FillProperties(CPropertiesWnd* pWnd){
	CPropertyGridCtrl* pCtrl = &pWnd->m_wndPropList;
	pCtrl->RemoveAll();
	CFXObject::FillProperties(pWnd);

	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty(_T("Ширина"),(variant_t)m_Width,_T("Ширина блока"),PROP_WIDTH);
	pCtrl->AddProperty(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Высота"),(variant_t)m_Height,_T("Высота блока"),PROP_HEIGHT);
	pCtrl->AddProperty(pProp);
}

void CFXBlock::RemovePin(CFXPin* pPin)
{
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* p = m_InputPins.GetAt(pos);
		if (p == pPin){
			if (m_InputPins.GetCount()-1 < m_PinInMinCount)
				return;
			m_InputPins.RemoveAt(pos);
			delete pPin;
			// TODO: Удалить все линки связанные с этим пином
			CalcPinCoords();
			return;
		}
		m_InputPins.GetNext(pos);
	}
	pos = m_OutputPins.GetHeadPosition();
	while (pos){
		CFXPin* p = m_OutputPins.GetAt(pos);
		if (p == pPin){
			if (m_OutputPins.GetCount()-1 < m_PinOutMinCount)
				return;
			m_OutputPins.RemoveAt(pos);
			delete pPin;
			CalcPinCoords();
			// TODO: Удалить все линки связанные с этим пином
			return;
		}
		m_OutputPins.GetNext(pos);
	}
}


void CFXBlock::Serialize(CArchive& ar)
{
	TracePrint(TRACE_LEVEL_3,"CFXBlock::Serialize");
	CFXObject::Serialize(ar);
	if (ar.IsStoring()){
		TracePrint(TRACE_LEVEL_3,"CFXBlock::Serialize:Storing id=%d name=%s",m_ID,m_Name);
		POSITION pos;
		ar << m_bBreakPoint;
		ar << m_bCalc;
		ar << m_CalcOrder;
		ar << m_Height;
		ar << m_Width;
		ar << m_MinHeight;
		ar << m_MinWidth;
		ar << m_PinInMaxCount;
		ar << m_PinInMinCount;
		ar << m_PinOutMaxCount;
		ar << m_PinOutMinCount;
		ar.WriteCount(m_InputPinTypes.GetCount());
		pos = m_InputPinTypes.GetHeadPosition();
		while (pos){
			ar << m_InputPinTypes.GetNext(pos);
		}
		ar.WriteCount(m_OutputPinTypes.GetCount());
		pos = m_OutputPinTypes.GetHeadPosition();
		while (pos){
			ar << m_OutputPinTypes.GetNext(pos);
		}


		ar.WriteCount(m_InputPins.GetCount());
		pos = m_InputPins.GetHeadPosition();
		while (pos){
			ar << m_InputPins.GetNext(pos);
		}

		ar.WriteCount(m_OutputPins.GetCount());
		pos = m_OutputPins.GetHeadPosition();
		while (pos){
			ar << m_OutputPins.GetNext(pos);
		}
	}
	else{
		ar >> m_bBreakPoint;
		ar >> m_bCalc;
		ar >> m_CalcOrder;
		ar >> m_Height;
		ar >> m_Width;
		ar >> m_MinHeight;
		ar >> m_MinWidth;
		ar >> m_PinInMaxCount;
		ar >> m_PinInMinCount;
		ar >> m_PinOutMaxCount;
		ar >> m_PinOutMinCount;
		int c = 0;
		c = ar.ReadCount();
		for (int i=0; i<c; i++){
			CFXPinType type;
			ar >> type;
			m_InputPinTypes.AddTail(type);
		}
		c = ar.ReadCount();
		for (int i=0; i<c; i++){
			CFXPinType type;
			ar >> type;
			m_OutputPinTypes.AddTail(type);
		}
		c = ar.ReadCount();
		for (int i=0; i<c; i++){
			CFXPin* pPin;
			ar >> pPin;
			pPin->m_pBlock = this;
			m_InputPins.AddTail(pPin);
		}
		c = ar.ReadCount();
		for (int i=0; i<c; i++){
			CFXPin* pPin;
			ar >> pPin;
			pPin->m_pBlock = this;
			
			m_OutputPins.AddTail(pPin);
		}
	}
}


void CFXBlock::RemoveBlock(void)
{
	CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(m_pBlock);
	ASSERT(pBlockFunc);
	pBlockFunc->RemoveBlock(this);
}



bool CFXBlock::Check(void)
{
	bool result = true;
	POSITION pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		if (!pPin->m_bConst && !pPin->m_pParam){
			CListLink lst;
			pPin->GetPinLinks(lst);
			if (lst.GetCount() == 0){
				CString msg;
				msg.Format(_T("Блок #%d (%s) пин %d (%s) имеет неопределенное значение"),m_ID,m_Name,pPin->m_ID,pPin->GetName());
				Log(Debug,msg);
				result = false;
			}
		}
	}
	return result;
}


void CFXBlock::UpdateConnectedPins(void)
{
	CFXGraphDoc* pDoc = GetActiveDocument();
	POSITION pos = m_OutputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_OutputPins.GetNext(pos);
		if (pPin->m_pParam){
			pPin->m_pParam->m_Value = pPin->GetValue();
		}
		CListLink lst;
		pPin->GetPinLinks(lst);
		POSITION pos1 = lst.GetHeadPosition();
		while (pos1){
			CFXPin* pPinIn = lst.GetNext(pos1)->m_pIn;
			pPinIn->SetValue( pPin->GetValue() );
		}
	}
}


void CFXBlock::RemovePinLinks(CFXPin* pPin)
{
	CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(m_pBlock);
	if (pBlockFunc){
		pBlockFunc->RemovePinLinks(pPin);
	}
}


CFXLink* CFXBlock::GetLink(CFXPin* pPin1, CFXPin* pPin2)
{
	return ((CFXBlockFunctional*)m_pBlock)->GetLink(pPin1,pPin2);
}


void CFXBlock::Initialize(void)
{
	POSITION pos;
	pos = m_InputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_InputPins.GetNext(pos);
		if (pPin->m_pParam){
			pPin->SetValue(pPin->m_pParam->m_Value);
		}
	}
	pos = m_OutputPins.GetHeadPosition();
	while (pos){
		CFXPin* pPin = m_OutputPins.GetNext(pos);
		switch(pPin->m_Type){
			case Logical:
				pPin->SetValue(false);
				break;
			case Float:
				pPin->SetValue((double)0);
				break;
			case Int:
				pPin->SetValue(0);
				break;
		}
		if (pPin->m_pParam)
			pPin->m_pParam->m_Value = pPin->GetValue();
	}
}


bool CFXBlock::IsRemovable()
{
	return true;
}
