// DragTreeView.cpp: файл реализации
//

#include "stdafx.h"
#include "FXGraph.h"
#include "DragTreeView.h"


// CDragTreeView

IMPLEMENT_DYNCREATE(CDragTreeView, CTreeView)

CDragTreeView::CDragTreeView()
{

	EnableAutomation();
}

CDragTreeView::~CDragTreeView()
{
}

void CDragTreeView::OnFinalRelease()
{
	// Когда будет освобождена последняя ссылка на объект автоматизации,
	// вызывается OnFinalRelease. Базовый класс автоматически
	// удалит объект. Перед вызовом базового класса добавьте
	// дополнительную очистку, необходимую вашему объекту.

	CTreeView::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CDragTreeView, CTreeView)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDragTreeView, CTreeView)
END_DISPATCH_MAP()

// Примечание: мы добавили поддержку для IID_IDragTreeView, чтобы обеспечить безопасную с точки зрения типов привязку
//  из VBA. Этот IID должен соответствовать GUID, связанному с 
//  disp-интерфейсом в файле .IDL.

// {65F1462F-F8E5-48CA-8BF0-0ADD6A6FDDF7}
static const IID IID_IDragTreeView =
{ 0x65F1462F, 0xF8E5, 0x48CA, { 0x8B, 0xF0, 0xA, 0xDD, 0x6A, 0x6F, 0xDD, 0xF7 } };

BEGIN_INTERFACE_MAP(CDragTreeView, CTreeView)
	INTERFACE_PART(CDragTreeView, IID_IDragTreeView, Dispatch)
END_INTERFACE_MAP()


// диагностика CDragTreeView

#ifdef _DEBUG
void CDragTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CDragTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// обработчики сообщений CDragTreeView
