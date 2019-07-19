#include "StdAfx.h"
#include "FXBlockController.h"
#include "FXBlockFunctional.h"
#include "PropertiesWnd.h"

IMPLEMENT_SERIAL(CFXBlockController,CFXBlock,1)

CFXBlockController::CFXBlockController(void)
{
}

void CFXBlockController::Create(CFXObject* pBlock){
	CFXBlockFunctional::Create(pBlock);
	m_Ticks = 0;
}

bool CFXBlockController::SetProperty(int nProperty, variant_t& value, CFXGraphView* pView)
{
	if (CFXBlock::SetProperty(nProperty, value, pView))
		return true;
	return false;
}

CFXBlockController::~CFXBlockController(void)
{
}


void CFXBlockController::FillProperties(CPropertiesWnd* pWnd)
{
	CFXBlockFunctional::FillProperties(pWnd);
	CPropertyGridCtrl* pCtrl = &pWnd->m_wndPropList;
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty(_T("Сетевой номер"), (variant_t)m_NetworkID, _T("Идентификатор устройства в сети RS485"), PROP_NETWORK_ID);
	pCtrl->AddProperty(pProp);
}
