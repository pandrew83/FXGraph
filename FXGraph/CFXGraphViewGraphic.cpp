// CFXGraphViewGraphic.cpp: файл реализации
//

#include "stdafx.h"
#include "FXGraph.h"
#include "CFXGraphViewGraphic.h"
#include "FXGraphDoc.h"
#include "CFXGraphicVariable.h"
#include "CFXGraphic.h"

// CFXGraphViewGraphic

IMPLEMENT_DYNCREATE(CFXGraphViewGraphic, CView)
								
CFXGraphViewGraphic::CFXGraphViewGraphic()
{
	m_X = 0;
	m_Y = 0;
	m_StartX = 0;
	m_StartY = 0;
	m_Scale = 100;
}

CFXGraphViewGraphic::~CFXGraphViewGraphic()
{
}

BEGIN_MESSAGE_MAP(CFXGraphViewGraphic, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()


// Рисование CFXGraphViewGraphic

#define GRAPH_GRID_STEP 25
#define GRAPH_GRID_COLOR RGB(0,0,0)
//
//void CFXGraphViewGraphic::AddVariable(int id, CString name, CFXPinType type)
//{
//	POSITION pos = m_pGraphic->GetFirstVariable();
//	while (pos) {
//		CFXGraphicVariable* pVar = m_pGraphic->GetNextVariable(pos);
//		if (pVar->m_ID == id)
//			return;
//	}
//	CFXGraphicVariable* pVar = new CFXGraphicVariable();
//	pVar->m_ID = id;
//	pVar->m_Name = name;
//	pVar->m_Type = type;
//	pVar->m_Color = colors[rand() % NCOLORS];
//	m_pGraphic->AddVariable(pVar);
//}

void CFXGraphViewGraphic::OnDraw(CDC* pDC)
{
	TracePrint(TRACE_LEVEL_1, "CFXGraphViewGraphic::OnDraw");
	CFXGraphDoc* pDoc = (CFXGraphDoc*)GetDocument();
	CRect rect;
	GetClientRect(&rect); // Width & Height of Local
	CPoint p1 = Local2Logic(CPoint(0, 0));
	CPoint p2 = Local2Logic(CPoint(rect.Width() - 1, rect.Height() - 1));
	CPoint pg1 = p1, pg2 = p2;
	while (pg1.x % GRAPH_GRID_STEP) pg1.x++;
	while (pg1.y % GRAPH_GRID_STEP) pg1.y++;
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap tmpBitmap;
	tmpBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	dc.SelectObject(tmpBitmap);
	dc.FillSolidRect(&rect, RGB(255, 255, 255));
	m_MemDC1.DeleteDC();
	m_MemDC1.CreateCompatibleDC(pDC);
	m_MemDC1.SelectObject(&tmpBitmap);

	CPen pen;
	CBrush brush;
	// Рисуем оси
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPoint p = Logic2Local(CPoint(0, 0));
	dc.MoveTo(0, p.y);
	dc.LineTo(rect.Width(), p.y);
	// Рисуем риски осей
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 8 * m_Scale / 100;
	wcscpy(lf.lfFaceName, _T("Arial"));
	CFont font;
	font.CreateFontIndirect(&lf);
	dc.SelectObject(font);
	dc.SetBkColor(RGB(255, 255, 255));
	dc.SetTextAlign(TA_CENTER);
	int x = pg1.x;
	CString txt;
	while (x <= pg2.x) {
		p = Logic2Local(CPoint(x, 0));
		dc.MoveTo(p.x,p.y-5);
		dc.LineTo(p.x,p.y);
		txt.Format(_T("%d"), (x/GRAPH_GRID_STEP) * pDoc->m_CycleTicks);
		if (x!=0)
			dc.TextOut(p.x, p.y+1, txt);
		x += GRAPH_GRID_STEP;
	}
	int y = pg1.y;
	CSize sizeTxt = dc.GetTextExtent(txt);
	dc.SetTextAlign(TA_RIGHT);
	while (y <= pg2.y) {
		p = Logic2Local(CPoint(0, y));
		dc.MoveTo(p.x,p.y);
		dc.LineTo(p.x+5,p.y);
		txt.Format(_T("%d"), (-y / GRAPH_GRID_STEP) );
		if (y!=0)
			dc.TextOut(p.x-1,p.y-sizeTxt.cy/2,txt);
		y += GRAPH_GRID_STEP;
	}
	dc.MoveTo(p.x, 0);
	dc.LineTo(p.x, rect.Height());
	pen.DeleteObject();
	// Рисуем сетку
	p = pg1;
	while (p.y <= p2.y) {
		if (p.y == 0) {
			p.y += GRAPH_GRID_STEP;
			continue;
		}
		p.x = pg1.x;
		while (p.x <= p2.x) {
			if (p.x == 0) {
				p.x += GRAPH_GRID_STEP;
				continue;
			}
			dc.SetPixel(Logic2Local(p), GRAPH_GRID_COLOR);
			p.x += GRAPH_GRID_STEP;
		}
		p.y += GRAPH_GRID_STEP;
	}
	// TODO: Начало координат. Удалить после отладки
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	brush.CreateSolidBrush(RGB(0, 0, 255));
	p = Logic2Local(CPoint(0, 0));
	dc.Rectangle(&CRect(p.x-5,p.y-5,p.x+5,p.y+5));
	pen.DeleteObject();
	brush.DeleteObject();
	font.DeleteObject();
	// Рисуем графики
	POSITION pos = m_pGraphic->GetFirstVariable();
	while (pos) {
		CFXGraphicVariable* pVar = m_pGraphic->GetNextVariable(pos);
		pen.CreatePen(PS_SOLID, 1, pVar->m_Color);
		dc.SelectObject(pen);
		x = 1;
		int prev_y = 0;
		POSITION pos1 = pDoc->m_DataCollector.GetFirstDataRow(); 
		while (pos1) {
			CFXDataCollectorItem* pRow = pDoc->m_DataCollector.GetNextDataRow(pos1);
			variant_t value = pRow->m_Values[pVar->m_ID];
			int y = 0;
			switch (pVar->m_Type) {
			case Logical:
				y = value ? 1 : 0;
				break;
			case Float:
				y = (double)value;
				break;
			case Int:
				y = (int)value;
				break;
			}
			dc.MoveTo(Logic2Local(CPoint((x - 1) * GRAPH_GRID_STEP, -prev_y * GRAPH_GRID_STEP)));
			dc.LineTo(Logic2Local(CPoint(x * GRAPH_GRID_STEP, -prev_y * GRAPH_GRID_STEP)));
			if (prev_y != y) {
				dc.LineTo(Logic2Local(CPoint(x * GRAPH_GRID_STEP, -y * GRAPH_GRID_STEP)));
			}
			prev_y = y;
			x++;
		}
		pen.DeleteObject();
	}
	//
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);
	tmpBitmap.DeleteObject();
	dc.DeleteDC();

}

CPoint CFXGraphViewGraphic::Logic2Local(CPoint point)
{
	TracePrint(TRACE_LEVEL_2, "CFXGraphViewGraphic::Logic2Local");
	CRect rect;
	GetClientRect(&rect);
	CPoint ret;
	ret.x = (LONG)((point.x - m_X) * m_Scale / 100 + rect.Width() / 2);
	ret.y = (LONG)((point.y - m_Y) * m_Scale / 100 + rect.Height() / 2);
	return ret;
}

CPoint CFXGraphViewGraphic::Local2Logic(CPoint point)
{
	TracePrint(TRACE_LEVEL_2, "CFXGraphViewGraphic::Local2Logic");
	CRect rect;
	GetClientRect(&rect);
	CPoint ret;
	ret.x = (LONG)((point.x - rect.Width() / 2) * 100 / m_Scale + m_X);
	ret.y = (LONG)((point.y - rect.Height() / 2) * 100 / m_Scale + m_Y);
	return ret;
}


// Диагностика CFXGraphViewGraphic

#ifdef _DEBUG
void CFXGraphViewGraphic::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CFXGraphViewGraphic::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CFXGraphViewGraphic


void CFXGraphViewGraphic::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CView::OnLButtonDown(nFlags, point);
}


void CFXGraphViewGraphic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CView::OnLButtonUp(nFlags, point);
}


void CFXGraphViewGraphic::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	m_Point = point;
	m_StartX = m_X;
	m_StartY = m_Y;
	CView::OnMButtonDown(nFlags, point);
}


void CFXGraphViewGraphic::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CView::OnMButtonUp(nFlags, point);
}


void CFXGraphViewGraphic::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CView::OnRButtonDown(nFlags, point);
}


void CFXGraphViewGraphic::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CView::OnRButtonUp(nFlags, point);
}


//void CFXGraphViewGraphic::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	TracePrint(TRACE_LEVEL_1, "CFXGraphView::OnMouseWheel");
//	CFXGraphDoc* pDoc = (CFXGraphDoc*)GetDocument();
//	if (zDelta > 0) {
//		m_Scale += 10;
//	}
//	else {
//		m_Scale -= 10;
//		if (m_Scale <= 0)
//			m_Scale = 10;
//	}
//	Invalidate(0);
//}


void CFXGraphViewGraphic::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_MBUTTON ) {
		CPoint d = Local2Logic(point) - Local2Logic(m_Point);
		m_X = m_StartX-d.x;
		m_Y = m_StartY-d.y;
		Invalidate(0);
		return;
	}
	CView::OnMouseMove(nFlags, point);
}


BOOL CFXGraphViewGraphic::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	TracePrint(TRACE_LEVEL_1, "CFXGraphViewGraphic::OnMouseWheel");
	CFXGraphDoc* pDoc = (CFXGraphDoc*)GetDocument();
	if (zDelta > 0) {
		m_Scale += 10;
	}
	else {
		m_Scale -= 10;
		if (m_Scale <= 0)
			m_Scale = 10;
	}
	Invalidate(0);
	return true;
}

BOOL CFXGraphViewGraphic::OnToolTipNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
	TracePrint(TRACE_LEVEL_1, "CFXGraphViewGraphic::OnToolTipNeedText");
	BOOL bHandledNotify = FALSE;

	CPoint CursorPos;
	VERIFY(::GetCursorPos(&CursorPos));
	ScreenToClient(&CursorPos);

	CRect ClientRect;
	GetClientRect(ClientRect);

	// Удостовериться, что курсор попадает в клиентскую область окна,
	// потому что библиотека тоже хочет получать эти сообщения для
	// показа подсказок на панели инструментов.
	if (ClientRect.PtInRect(CursorPos))
	{
		TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
		CPoint p = Local2Logic(CursorPos);
		
		//COLORREF color1 = m_Mem1.GetPixel(CursorPos);
		//COLORREF color2 = m_Mem2.GetPixel(CursorPos);
		//int id = color1 & MASK1_ID;
		//if (id) {
		//	CFXObject* pObject = m_pBlock->GetByID(id);
		//	if (pObject) {
		//		CFXBlock* pBlock = dynamic_cast<CFXBlock*>(pObject);
		//		CFXPin* pPin = dynamic_cast<CFXPin*>(pObject);
		//		CFXLink* pLink = dynamic_cast<CFXLink*>(pObject);
		//		if (pBlock) {
		//			wcscpy_s(pTTT->szText, pBlock->GetName());
		//		}
		//		if (pPin) {
		//			wcscpy_s(pTTT->szText, pPin->GetName());
		//		}
		//		if (pLink) {
		//			wcscpy_s(pTTT->szText, pLink->GetName());
		//		}
		//		bHandledNotify = TRUE;
		//	}
		//}
	}
	return bHandledNotify;
}