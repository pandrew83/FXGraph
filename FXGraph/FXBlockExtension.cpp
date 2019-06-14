#include "StdAfx.h"
#include "FXBlockExtension.h"
#include "PropertiesWnd.h"

IMPLEMENT_SERIAL(CFXBlockExtension,CFXBlock,1);

CFXBlockExtension::CFXBlockExtension(void)
{
}


CFXBlockExtension::~CFXBlockExtension(void)
{
}


CFXPin* CFXBlockExtension::AddInputPin(CFXPinType type, CString funcName)
{
	return CFXBlock::AddInputPin(type,funcName,false,false,true);
}


CFXPin* CFXBlockExtension::AddOutputPin(CFXPinType type, CString funcName)
{
	return CFXBlock::AddOutputPin(type,funcName,false,false,true);
}


void CFXBlockExtension::FillProperties(CPropertiesWnd* pWnd)
{
	CFXBlock::FillProperties(pWnd);
	CPropertyGridCtrl* pCtrl = &pWnd->m_wndPropList;
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty(_T("Сетевой номер"), (variant_t)m_NetworkID, _T("Идентификатор устройства в сети RS485"),PROP_NETWORK_ID);
	pCtrl->AddProperty(pProp);
}


void CFXBlockExtension::Serialize(CArchive& ar)
{
	CFXBlock::Serialize(ar);
}
