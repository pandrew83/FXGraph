
// mdi_templateView.cpp : реализаци€ класса Cmdi_templateView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позвол€ет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "mdi_template.h"
#endif

#include "mdi_templateDoc.h"
#include "mdi_templateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmdi_templateView

IMPLEMENT_DYNCREATE(Cmdi_templateView, CView)

BEGIN_MESSAGE_MAP(Cmdi_templateView, CView)
	// —тандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cmdi_templateView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// создание/уничтожение Cmdi_templateView

Cmdi_templateView::Cmdi_templateView()
{
	// TODO: добавьте код создани€

}

Cmdi_templateView::~Cmdi_templateView()
{
}

BOOL Cmdi_templateView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменени€
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// рисование Cmdi_templateView

void Cmdi_templateView::OnDraw(CDC* /*pDC*/)
{
	Cmdi_templateDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки дл€ собственных данных
}


// печать Cmdi_templateView


void Cmdi_templateView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cmdi_templateView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void Cmdi_templateView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void Cmdi_templateView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void Cmdi_templateView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cmdi_templateView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// диагностика Cmdi_templateView

#ifdef _DEBUG
void Cmdi_templateView::AssertValid() const
{
	CView::AssertValid();
}

void Cmdi_templateView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmdi_templateDoc* Cmdi_templateView::GetDocument() const // встроена неотлаженна€ верси€
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmdi_templateDoc)));
	return (Cmdi_templateDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений Cmdi_templateView
