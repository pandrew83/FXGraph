#include "StdAfx.h"
#include "FXBlock.h"
#include "FXPin.h"
#include "FXGraphView.h"
#include "PropertiesWnd.h"
#include "FXLink.h"
#include "FXGraphDoc.h"
#include "FXBlockFunctional.h"
#include "FXBlockFunctionalPin.h"

IMPLEMENT_SERIAL(CFXPin,CFXObject,1)

CString CFXPin::m_FormatFloats[2] ={_T("%.3f"),_T("%.1f")};
CString CFXPin::m_FormatInts[3]={_T("%d"),_T("%u"),_T("0x%x")};
int CFXPin::m_nFormatInts = 3;
int CFXPin::m_nFormatFloats = 2;

CArchive& operator<<(CArchive&ar, CFXPinType type){
	switch(type){
		case Float:
			ar << (char)1;
			break;
		case Int:
			ar << (char)2;
			break;
		case Logical:
			ar << (char)3;
			break;
	}
	return ar;
}

CArchive& operator>>(CArchive& ar, CFXPinType& type){
	char v;
	ar >> v;
	switch(v){
		case 1:
			type = Float;
			break;
		case 2:
			type = Int;
			break;
		case 3:
			type = Logical;
			break;
	}
	return ar;
}

CArchive& operator<<(CArchive&ar, CFXPinDir dir){
	if (dir == Input)
		ar << (char)1;
	else
		ar << (char)2;
	return ar;
}

CArchive& operator>>(CArchive&ar, CFXPinDir&dir){
	char v;
	ar >> v;
	if (v == 1)
		dir = Input;
	else
		dir = Output;
	return ar;
}

CFXPin::CFXPin(void)
	: m_FuncName(_T(""))
	, m_Format(_T(""))
{
	m_pParam = NULL;
}

CFXPin::~CFXPin(void)
{
}

void CFXPin::Draw(CFXGraphView*pView){
	// Возможно будет получен не тот документ!!!!!
	CFXGraphDoc* pDoc = m_pBlock->GetActiveDocument();
	bool isDebug = pDoc->m_bDebug;
	CString value;
	switch(m_Type){
		case Logical:
			value = m_Value?_T("True"):_T("False");
			break;
		case Int:
			value.Format(m_Format,(int)m_Value);
			break;
		case Float:
			value.Format(m_Format,(double)m_Value);
			break;
	}
	bool selected = pView->IsSelected(this);
	CPoint p = pView->Logic2Local(CPoint(m_X,m_Y));
	CPoint p1 = pView->Logic2Local(m_pBlock->GetXY());
	CFXBlock* pBlock = (CFXBlock*)m_pBlock;
	CPoint p2 = pView->Logic2Local(CPoint(pBlock->GetX()+pBlock->GetWidth(),pBlock->GetY()+pBlock->GetHeight()));
	COLORREF color = 0;
	switch(m_Type){
		case Float:
			color = PIN_COLOR_TYPE_FLOAT;
			break;
		case Int:
			color = PIN_COLOR_TYPE_INT;
			break;
		case Logical:
			color = PIN_COLOR_TYPE_LOGICAL;
			break;
	}
	if (selected)
		color = COLOR_SELECTED;
	CBrush brush(color);
	CPen pen(PS_SOLID,1,color);
	int pinSize = PIN_SIZE * pView->m_Scale / 100;
	m_RectPin = CRect(p.x-pinSize/2,p.y-pinSize/2,p.x+pinSize/2,p.y+pinSize/2);
	pView->m_pDC->SelectObject(brush);
	pView->m_pDC->SelectObject(pen);
	pView->m_pDC->Ellipse(&m_RectPin);
	brush.DeleteObject();
	pen.DeleteObject();

	brush.CreateSolidBrush(selected?m_ID|MASK1_SELECTED:m_ID);
	pen.CreatePen(PS_SOLID,1,selected?m_ID|MASK1_SELECTED:m_ID);
	pView->m_Mem1.SelectObject(brush);
	pView->m_Mem1.SelectObject(pen);
	pView->m_Mem1.Ellipse(&m_RectPin);
	brush.DeleteObject();
	pen.DeleteObject();
	CString name;
	if (m_pParam)
		name = m_pParam->m_Name;
	else
		name = m_Name;
	CSize sizeName = pView->m_pDC->GetTextExtent(name);
	CSize sizeFuncName = pView->m_pDC->GetTextExtent(m_FuncName);
	CSize sizeValue = pView->m_pDC->GetTextExtent(value);
	if (m_Dir == Input){
		m_RectName.left = p.x-pinSize-sizeName.cx;
		m_RectName.top = p.y-sizeName.cy/2;
		m_RectName.right = m_RectName.left + sizeName.cx;
		m_RectName.bottom = m_RectName.top + sizeName.cy;

		m_RectFuncName.left = p1.x+pinSize;
		m_RectFuncName.top = p.y-sizeFuncName.cy/2;
		m_RectFuncName.bottom = m_RectFuncName.top + sizeFuncName.cy;
		m_RectFuncName.right = m_RectFuncName.left + sizeFuncName.cx;

		m_RectValue.right = p.x+pinSize/2;
		m_RectValue.left = sizeValue.cx<pinSize? p.x-pinSize/2 :  p.x-sizeValue.cx+pinSize/2;
		m_RectValue.top = p.y-pinSize/2-sizeValue.cy;
		m_RectValue.bottom = p.y-pinSize/2;
	}
	else{
		m_RectName.left = p.x + pinSize;
		m_RectName.top = p.y-sizeName.cy/2;
		m_RectName.right = m_RectName.left + sizeName.cx;
		m_RectName.bottom = m_RectName.top + sizeName.cy;

		m_RectFuncName.left = p2.x - pinSize - sizeFuncName.cx;
		m_RectFuncName.right = m_RectFuncName.left + sizeFuncName.cx;
		m_RectFuncName.top = p.y-sizeFuncName.cy/2;
		m_RectFuncName.bottom = m_RectFuncName.top + sizeFuncName.cy;

		m_RectValue.left = p.x-pinSize/2;
		m_RectValue.right = sizeValue.cx<pinSize ? p.x+pinSize/2 : p.x-pinSize/2 + sizeValue.cx;
		m_RectValue.top = p.y-pinSize/2-sizeValue.cy;
		m_RectValue.bottom = p.y-pinSize/2;
	}
	pen.CreatePen(PS_SOLID,1,PIN_NAME_COLOR);
	CRect valueRect;
	if (isDebug || (m_pParam && m_Dir==Input)|| m_bConst)
		pView->m_pDC->DrawText(value,&m_RectValue,DT_NOPREFIX|DT_CENTER);
	pen.DeleteObject();
	if (!name.IsEmpty()){
		pen.CreatePen(PS_SOLID,1,PIN_NAME_COLOR);
		pView->m_pDC->DrawText(name,&m_RectName,DT_NOPREFIX);
		pen.DeleteObject();
	}
	if (!m_FuncName.IsEmpty()){
		pen.CreatePen(PS_SOLID,1,PIN_FUNC_NAME_COLOR);
		pView->m_pDC->DrawText(m_FuncName,&m_RectFuncName,DT_NOPREFIX);
		pen.DeleteObject();

	}
}

void CFXPin::Remove(void)
{
	((CFXBlock*)m_pBlock)->RemovePin(this);
}

void CFXPin::Serialize(CArchive& ar)
{
	TracePrint(TRACE_LEVEL_3,"CFXPin::Serialize");
	CFXObject::Serialize(ar);
	if (ar.IsStoring()){
		TracePrint(TRACE_LEVEL_3,"CFXPin::Serialize:Storing id=%d dir=%s",m_ID,m_Dir==Input?"Input":"Output");
		ar << m_Dir;
		ar << m_Type;
		ar << m_FuncName;
		ar << (m_pParam!=NULL?m_pParam->m_Name:_T(""));
		ar << m_bConst;
		ar << m_Format;
		switch(m_Type){
			case Logical:
				ar << (bool)m_Value;
				break;
			case Int:
				ar << (int)m_Value;
				break;
			case Float:
				ar << (double)m_Value;
				break;
		}
	}
	else{
		ar >> m_Dir;
		ar >> m_Type;
		ar >> m_FuncName;
		CString paramName;
		ar >> paramName;
		CFXGraphDoc* pDoc = (CFXGraphDoc*)ar.m_pDocument;
		if (m_Dir == Input){
			m_pParam = pDoc->GetInputParam(paramName);
		}
		else{
			m_pParam = pDoc->GetOutputParam(paramName);
		}
		ar >> m_bConst;
		ar >> m_Format;
		int valInt;
		bool valBool;
		double valDbl;
		switch(m_Type){
			case Logical:
				m_Value.vt = VT_BOOL;
				ar >> valBool;
				m_Value = valBool;
				break;
			case Int:
				m_Value.vt = VT_I4;
				ar >> valInt;
				m_Value = valInt;
				break;
			case Float:
				m_Value.vt = VT_R8;
				ar >> valDbl;
				m_Value = valDbl;
				break;
		}
	}
}

void CFXPin::GetPinLinks(CListLink& lst){
	((CFXBlock*)m_pBlock)->GetPinLinks(lst,this);
}

void CFXPin::FillProperties(CPropertiesWnd* pWnd)
{
	CPropertyGridCtrl* pCtrl = &pWnd->m_wndPropList;
	CMFCPropertyGridProperty* pProp;

	CFXGraphDoc* pDoc = GetActiveDocument();

	CList<CFXParam*,CFXParam*>* pList;
	if (m_Dir == Input)
		pList = &pDoc->m_InputParams;
	else
		pList = &pDoc->m_OutputParams;

	pWnd->m_wndPropList.RemoveAll();
	CFXObject::FillProperties(pWnd);
	pProp = new CMFCPropertyGridProperty(_T("Функция"),(variant_t)m_FuncName,_T("Функциональное имя"),PROP_FUNCNAME);
	pCtrl->AddProperty(pProp);
	if (m_Type == Float || m_Type == Int){
		pProp = new CProperty(_T("Формат"),(variant_t)m_Format,_T("Формат вывода значения пина"),PROP_FORMAT);
		if (m_Type == Float){
			for (int i=0; i<m_nFormatFloats; i++){
				pProp->AddOption(m_FormatFloats[i]);
			}
		}
		if (m_Type == Int){
			for (int i=0; i<m_nFormatInts; i++){
				pProp->AddOption(m_FormatInts[i]);
			}
		}
		pCtrl->AddProperty(pProp);
	}
	if (m_bAllowParam && !m_bConst){
		pProp = new CProperty(_T("Переменная"),(variant_t)(m_pParam?m_pParam->m_Name:_T("")),_T("Имя переменной"),PROP_PARAM);
		pProp->AllowEdit(false);
		pProp->AddOption(_T(""));
		POSITION pos = pList->GetHeadPosition();
		while (pos){
			CFXParam* pParam = pList->GetNext(pos);
			if (pParam->m_Type == m_Type){
				pProp->AddOption(pParam->m_Name);
			}
		}
		pCtrl->AddProperty(pProp);
	}
	if (m_bAllowConst){
		pProp = new CProperty(_T("Константа"),(variant_t)m_bConst,_T("Значение пина контанта"),PROP_CONST);
		pCtrl->AddProperty(pProp);
	}
	if (m_bConst || pDoc->m_bDebug){
		pProp = new CProperty(_T("Значение"),(variant_t)m_Value,_T("Значение пина"),PROP_VALUE);
		pCtrl->AddProperty(pProp);
	}

}


void CFXPin::SetParam(CFXParam* pParam)
{
	if (m_Dir == Output){
		if (pParam){
			if (pParam->m_pPin == NULL){
				pParam->m_pPin = this;
				m_pParam = pParam;
			}
			else{
				// pParam уже привязан к другому пину
			}
		}
		else{ // Сброс
			if (m_pParam)
				m_pParam->m_pPin = NULL;
			m_pParam = NULL;
		}
		
	}
	if (m_Dir == Input){
		m_pParam = pParam;
		if (m_pParam){
			m_Value = m_pParam->m_Value;
		}
	}

}

void CFXPin::SetValue(variant_t value){
	m_Value = value;
	if (m_Dir == Output && m_pParam)
		m_pParam->m_Value = value;
	CFXBlockFunctionalPin* pBlockFuncPin = dynamic_cast<CFXBlockFunctionalPin*>(m_pBlock);
	CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(m_pBlock);
	if (pBlockFuncPin){
		pBlockFuncPin->m_pLinkedPin->m_Value = value;
		CFXGraphView* pView = pBlockFuncPin->GetActiveDocument()->GetBlockView(dynamic_cast<CFXBlockFunctional*>(pBlockFuncPin->m_pBlock));
		if (pView){
			pBlockFuncPin->Invalidate(pView,REGION_VALUE);
		}
	}
	if (pBlockFunc){
		POSITION pos = pBlockFunc->m_Blocks.GetHeadPosition();
		while (pos){
			CFXBlockFunctionalPin* pBlockFuncPin = dynamic_cast<CFXBlockFunctionalPin*>(pBlockFunc->m_Blocks.GetNext(pos));
			if (pBlockFuncPin){
				if (pBlockFuncPin->m_pLinkedPin == this){
					if (pBlockFuncPin->m_pLinkedPin->m_Dir == Input){
						pBlockFuncPin->m_OutputPins.GetHead()->m_Value = value;
					}
					else{
						pBlockFuncPin->m_InputPins.GetHead()->m_Value = value;
					}
					CFXGraphView* pView = GetActiveDocument()->GetBlockView(pBlockFunc);
					if (pView)
						pBlockFuncPin->Invalidate(pView,REGION_LEFT|REGION_RIGHT);
				}
			}
		}
	}
}

variant_t CFXPin::GetValue(void)
{
	return m_Value;
}

CFXLink* CFXPin::GetLink(CFXPin* pPin)
{
	return ((CFXBlock*)m_pBlock)->GetLink(this,pPin);
}

void CFXPin::RemoveLinks(void)
{
	((CFXBlock*)m_pBlock)->RemovePinLinks(this);
}

void CFXPin::Invalidate(CFXGraphView* pView,int regions)
{
	CDC* pDC = pView->GetDC();
	CPoint p = pView->Logic2Local(CPoint(m_X,m_Y));
	int pinSize = PIN_SIZE * pView->m_Scale / 100;
	LOGFONT lf;
	memset(&lf,0,sizeof(LOGFONT));
	lf.lfHeight = 14*pView->m_Scale/100;
	wcscpy(lf.lfFaceName,_T("Arial"));
	CFont font;
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(font);
	CSize sizeValue;
	CSize sizeName;
	CSize sizeFuncName;
	CPoint p1 = pView->Logic2Local(m_pBlock->GetXY());
	CFXBlock* pBlock = (CFXBlock*)m_pBlock;
	CPoint p2 = pView->Logic2Local(CPoint(pBlock->GetX()+pBlock->GetWidth(),pBlock->GetY()+pBlock->GetHeight()));
	
	if (regions & REGION_VALUE){
		pView->InvalidateRect(&m_RectValue,false);
		CString value;
		switch(m_Type){
			case Logical:
				value = m_Value?_T("True"):_T("False");
				break;
			case Int:
				value.Format(m_Format,(int)m_Value);
				break;
			case Float:
				value.Format(m_Format,(double)m_Value);
				break;
		}
		sizeValue = pDC->GetTextExtent(value);
	}
	if (regions & REGION_NAME){
		CString name;
		if (m_pParam)
			name = m_pParam->m_Name;
		else
			name = m_Name;
		pView->InvalidateRect(m_RectName,false);
		sizeName = pDC->GetTextExtent(name);
	}
	if (regions & REGION_FUNCNAME){
		pView->InvalidateRect(m_RectFuncName,false);
		sizeFuncName = pDC->GetTextExtent(m_FuncName);
	}
	if (regions & REGION_PIN){
		pView->InvalidateRect(m_RectPin,false);
	}

	if (m_Dir == Input){
		if (regions & REGION_NAME){
			m_RectName.left = p.x-pinSize-sizeName.cx;
			m_RectName.top = p.y-sizeName.cy/2;
			m_RectName.right = m_RectName.left + sizeName.cx;
			m_RectName.bottom = m_RectName.top + sizeName.cy;
		}
		if (regions & REGION_FUNCNAME){
			m_RectFuncName.left = p1.x+pinSize;
			m_RectFuncName.top = p.y-sizeFuncName.cy/2;
			m_RectFuncName.bottom = m_RectFuncName.top + sizeFuncName.cy;
			m_RectFuncName.right = m_RectFuncName.left + sizeFuncName.cx;
		}
		if (regions & REGION_VALUE){
			m_RectValue.right = p.x+pinSize/2;
			m_RectValue.left = sizeValue.cx<pinSize? p.x-pinSize/2 :  p.x-sizeValue.cx+pinSize/2;
			m_RectValue.top = p.y-pinSize/2-sizeValue.cy;
			m_RectValue.bottom = p.y-pinSize/2;
		}
	}
	else{
		if (regions & REGION_NAME){
			m_RectName.left = p.x + pinSize;
			m_RectName.top = p.y-sizeName.cy/2;
			m_RectName.right = m_RectName.left + sizeName.cx;
			m_RectName.bottom = m_RectName.top + sizeName.cy;
		}
		if (regions & REGION_FUNCNAME){
			m_RectFuncName.left = p2.x - pinSize - sizeFuncName.cx;
			m_RectFuncName.right = m_RectFuncName.left + sizeFuncName.cx;
			m_RectFuncName.top = p.y-sizeFuncName.cy/2;
			m_RectFuncName.bottom = m_RectFuncName.top + sizeFuncName.cy;
		}
		if (regions & REGION_VALUE){
			m_RectValue.left = p.x-pinSize/2;
			m_RectValue.right = sizeValue.cx<pinSize ? p.x+pinSize/2 : p.x-pinSize/2 + sizeValue.cx;
			m_RectValue.top = p.y-pinSize/2-sizeValue.cy;
			m_RectValue.bottom = p.y-pinSize/2;
		}
	}
	if (regions & REGION_VALUE){
		pView->InvalidateRect(&m_RectValue,false);
	}
	if (regions & REGION_NAME){
		pView->InvalidateRect(&m_RectName,false);
	}
	if (regions & REGION_FUNCNAME){
		pView->InvalidateRect(&m_RectFuncName,false);
	}
	if (regions & REGION_PIN){
		int pinSize = PIN_SIZE * pView->m_Scale / 100;
		m_RectPin = CRect(p.x-pinSize/2,p.y-pinSize/2,p.x+pinSize/2,p.y+pinSize/2);
		pView->InvalidateRect(&m_RectPin,false);
	}
	font.DeleteObject();
	pView->ReleaseDC(pDC);
}
