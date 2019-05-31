// CFXGraphViewGraphic.cpp: файл реализации
//

#include "stdafx.h"
#include "FXGraph.h"
#include "CFXGraphViewGraphic.h"


// CFXGraphViewGraphic

IMPLEMENT_DYNCREATE(CFXGraphViewGraphic, CView)

CFXGraphViewGraphic::CFXGraphViewGraphic()
{

}

CFXGraphViewGraphic::~CFXGraphViewGraphic()
{
}

BEGIN_MESSAGE_MAP(CFXGraphViewGraphic, CView)
END_MESSAGE_MAP()


// Рисование CFXGraphViewGraphic

void CFXGraphViewGraphic::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
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
