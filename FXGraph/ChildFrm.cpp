
// ChildFrm.cpp : реализация класса CChildFrame
//

#include "stdafx.h"
#include "FXGraph.h"

#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
//	ON_COMMAND(IDCLOSE, &CChildFrame::OnIdclose)
END_MESSAGE_MAP()

// создание/уничтожение CChildFrame

CChildFrame::CChildFrame()
{
//	TracePrint("New CChildFrame");
}

CChildFrame::~CChildFrame()
{
	TracePrint(TRACE_LEVEL_1,"CChildFrame::~CChildFrame");
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// диагностика CChildFrame

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// обработчики сообщений CChildFrame


void CChildFrame::OnClose()
{
	TracePrint(TRACE_LEVEL_1,"CChildFrame::OnClose");
	CMDIChildWndEx::OnClose();
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMainFrame->m_wndProperties.UpdateProperties(NULL);
}

