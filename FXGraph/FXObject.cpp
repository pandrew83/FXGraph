#include "StdAfx.h"
#include "FXObject.h"
#include "PropertiesWnd.h"
#include "MainFrm.h"
#include "FXGraph.h"
#include "FXGraphDoc.h"
#include "FXBlockFunctional.h"

IMPLEMENT_SERIAL(CFXObject, CObject, 1)

void Log(CFXMsgType type,CString str){
	((CMainFrame*)(((CFXGraphApp*)AfxGetApp())->m_pMainWnd))->Log(type,str);
}

void WriteStr(CArchive& ar, LPCSTR fmt,...){
	va_list args;
	va_start(args,fmt);

	CStringA str;
	str.FormatV(fmt,args);
	va_end(args);
	ar.Write((LPCTSTR)str.GetBuffer(),str.GetLength());
}

CFXObject::CFXObject(void)
{
	m_ID = 0;
	m_Name = "";
	m_SaveX = 0;
	m_SaveY = 0;
	m_Style = 0;
	m_X = 0;
	m_Y = 0;
	m_pBlock = NULL;
}


CFXObject::~CFXObject(void)
{

}


void CFXObject::StartMoving(void)
{
	m_SaveX = m_X;
	m_SaveY = m_Y;
}


void CFXObject::Move(int dx, int dy)
{
	m_X = m_SaveX + dx;
	m_Y = m_SaveY + dy;
}

void CFXObject::Serialize(CArchive& ar){
	TracePrint(TRACE_LEVEL_3,"CFXObject::Serialize");
	CObject::Serialize(ar);
	if (ar.IsStoring()){
		TracePrint(TRACE_LEVEL_3,"CFXObject::Serialize:Storing id=%d name=%s",m_ID,m_Name);
		ar << m_ID;
		ar << m_Name;
		ar << m_X;
		ar << m_Y;
	}
	else{
		ar >> m_ID;
		ar >> m_Name;
		ar >> m_X;
		ar >> m_Y;
	}

}

void CFXObject::FillProperties(CPropertiesWnd* pWnd){
	CPropertyGridCtrl* pCtrl =  &pWnd->m_wndPropList;
	pCtrl->RemoveAll();
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty(_T("ID"),(variant_t)m_ID,_T("Идентификатор объекта"));
	pProp->AllowEdit(false);
	pCtrl->AddProperty(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Наименование"),m_Name,_T("Наименование блока"),PROP_NAME);
	pCtrl->AddProperty(pProp);

	pProp = new CMFCPropertyGridProperty( _T("X"), (_variant_t) m_X, _T("Указывает положение блока"),PROP_COORDX);
	pCtrl->AddProperty(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Y"), (_variant_t) m_Y, _T("Указывает положение блока"),PROP_COORDY);
	pCtrl->AddProperty(pProp);
//	pWnd->m_Properties[PROP_COORDX]->SetValue((_variant_t)m_X);
//	pWnd->m_Properties[PROP_COORDY]->SetValue((_variant_t)m_Y);
//	pWnd->m_Properties[PROP_NAME]->SetValue((_variant_t)m_Name);
}



CFXGraphDoc* CFXObject::GetActiveDocument(void)
{
	CMDIChildWnd * pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

      if ( !pChild )
          return NULL;

      CDocument * pDoc = pChild->GetActiveDocument();

      if ( !pDoc )
         return NULL;

      // Ошибка, если документ неправильного типа
      if ( ! pDoc->IsKindOf( RUNTIME_CLASS(CFXGraphDoc) ) )
         return NULL;

      return (CFXGraphDoc *) pDoc;
}


void CFXObject::Invalidate(CFXGraphView* pView, int regions)
{
}


CString CFXObject::GetClassDescriptorByID(int id)
{
	int cnt = CFXObject::m_ObjectDescriptors.GetCount();

	for (int i = 0; i < cnt; i++)
	{
		auto desc = &CFXObject::m_ObjectDescriptors.GetAt(i);
		if (desc->m_Id == id) {
			return desc->m_ClassName;
		}
	}
	throw new CFXException(_T("GetClassDescriptorByID: Unknown id"));
}

 CArray<CFXObjectDescriptor, CFXObjectDescriptor> CFXObject::m_ObjectDescriptors;
