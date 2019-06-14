// PropertyGridCtrl.cpp: файл реализации
//

#include "stdafx.h"
#include "FXGraph.h"
#include "PropertyGridCtrl.h"
#include "MainFrm.h"

// CPropertyGridCtrl

IMPLEMENT_DYNAMIC(CPropertyGridCtrl, CMFCPropertyGridCtrl)

CPropertyGridCtrl::CPropertyGridCtrl()
{

}

CPropertyGridCtrl::~CPropertyGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CPropertyGridCtrl, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()



// обработчики сообщений CPropertyGridCtrl




void CPropertyGridCtrl::OnPropertyChanged(CMFCPropertyGridProperty* pProp) const
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	_variant_t v = pProp->GetValue();
	if (!pMainFrame->ValidateProperty(pProp->GetData(),v)){
		pProp->SetValue(pProp->GetOriginalValue());
	}
	return; 	
}



BOOL CPropertyGridCtrl::ValidateItemData(CMFCPropertyGridProperty* pProp)
{
	// TODO: добавьте специализированный код или вызов базового класса
	TracePrint(TRACE_LEVEL_1,"CPropertyGridCtrl::ValidateItemData");
	return CMFCPropertyGridCtrl::ValidateItemData(pProp);
}
