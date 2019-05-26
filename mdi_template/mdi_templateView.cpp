
// mdi_templateView.cpp : ���������� ������ Cmdi_templateView
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
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
	// ����������� ������� ������
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cmdi_templateView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// ��������/����������� Cmdi_templateView

Cmdi_templateView::Cmdi_templateView()
{
	// TODO: �������� ��� ��������

}

Cmdi_templateView::~Cmdi_templateView()
{
}

BOOL Cmdi_templateView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �������� ����� Window ��� ����� ����������� ���������
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// ��������� Cmdi_templateView

void Cmdi_templateView::OnDraw(CDC* /*pDC*/)
{
	Cmdi_templateDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �������� ����� ��� ��������� ��� ����������� ������
}


// ������ Cmdi_templateView


void Cmdi_templateView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cmdi_templateView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ���������� �� ���������
	return DoPreparePrinting(pInfo);
}

void Cmdi_templateView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� �������������� ������������� ����� �������
}

void Cmdi_templateView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� ������� ����� ������
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


// ����������� Cmdi_templateView

#ifdef _DEBUG
void Cmdi_templateView::AssertValid() const
{
	CView::AssertValid();
}

void Cmdi_templateView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmdi_templateDoc* Cmdi_templateView::GetDocument() const // �������� ������������ ������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmdi_templateDoc)));
	return (Cmdi_templateDoc*)m_pDocument;
}
#endif //_DEBUG


// ����������� ��������� Cmdi_templateView
