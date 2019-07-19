#include "stdafx.h"
#include "CFXBlockVisualShowFloat.h"
#include "FXGraphView.h"
#include "PropertiesWnd.h"

IMPLEMENT_SERIAL(CFXBlockVisualShowFloat, CFXBlock, 1);
IMPLEMENT_SERIAL(CFXBlockVisualShowInt, CFXBlock, 1);
IMPLEMENT_SERIAL(CFXBlockVisualShowLogical, CFXBlock, 1);

CString CFXBlockVisualShowFloat::m_FormatFloats[2] = { _T("%.3f"),_T("%.1f") };
CString CFXBlockVisualShowFloat::m_FormatInts[3] = { _T("%d"),_T("%u"),_T("0x%x") };
int CFXBlockVisualShowFloat::m_nFormatInts = 3;
int CFXBlockVisualShowFloat::m_nFormatFloats = 2;

CFXBlockVisualShow::CFXBlockVisualShow()
{
}

CFXBlockVisualShow::~CFXBlockVisualShow()
{
}

void CFXBlockVisualShow::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Name = _T("Значение");
	m_MinHeight = 50;
	m_Height = 50;
}

bool CFXBlockVisualShow::Calc()
{
	if (!CFXBlock::Calc())
		return false;
	return true;
}

void CFXBlockVisualShow::Draw(CFXGraphView* pView)
{
	CFXBlock::Draw(pView);
	CString value;
	CFXPin* pPin = m_InputPins.GetHead();
	switch (pPin->m_Type) {
		case Float:
			value.Format(m_Format, (double)pPin->GetValue());
			break;
		case Logical:
			value = pPin->GetValue() ? _T("True") : _T("False");
			break;
		case Int:
			value.Format(m_Format, (int)pPin->GetValue());
			break;
	}
	CFXGraphDoc* pDoc = (CFXGraphDoc*)pView->GetDocument();

	CPoint p1 = pView->Logic2Local(CPoint(m_X, m_Y));
	CPoint p2 = pView->Logic2Local(CPoint(m_X + m_Width, m_Y));
	CPoint p3 = pView->Logic2Local(CPoint(m_X + m_Width, m_Y + m_Height));
	CPoint p4 = pView->Logic2Local(CPoint(m_X, m_Y + m_Height));
	//CPen dcPen(PS_SOLID, 1, RGB(0,0,255));
	//CBrush brush(RGB(255, 255, 255));

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 24 * pView->m_Scale / 100;
	wcscpy(lf.lfFaceName, _T("Arial"));
	CFont font;
	font.CreateFontIndirect(&lf);
	pView->m_pDC->SelectObject(font);
	//pView->m_pDC->SelectObject(dcPen);
	//pView->m_pDC->SelectObject(brush);
//	m_RectBlock = CRect(p1.x, p1.y, p3.x + 1, p3.y + 1);
//	pView->m_pDC->Rectangle(&m_RectBlock);
//	CSize sizeCaption = pView->m_pDC->GetTextExtent(m_Name);
	CSize sizeValue = pView->m_pDC->GetTextExtent(value);
	int y = p1.y + (m_Height*pView->m_Scale/100 - sizeValue.cy) / 2 + 1;
	m_RectValue = CRect(p1.x + 1, y, p3.x, y + sizeValue.cy);
	pView->m_pDC->SetTextColor(RGB(0, 0, 255));
	pView->m_pDC->DrawText(value, &m_RectValue, DT_CENTER | DT_NOPREFIX);
	//
	//dcPen.DeleteObject();
	//brush.DeleteObject();
	//font.DeleteObject();
}

void CFXBlockVisualShow::FillProperties(CPropertiesWnd* pWnd)
{
	CPropertyGridCtrl* pCtrl = &pWnd->m_wndPropList;
	CFXBlock::FillProperties(pWnd);
	CMFCPropertyGridProperty* pProp;
	CFXPin* pPin = m_InputPins.GetHead();
	pProp = new CProperty(_T("Формат"), (variant_t)m_Format, _T("Формат вывода значения"), PROP_FORMAT);
	if (pPin->m_Type == Float) {
		for (int i = 0; i < m_nFormatFloats; i++) {
			pProp->AddOption(m_FormatFloats[i]);
		}
	}
	if (pPin->m_Type == Int) {
		for (int i = 0; i < m_nFormatInts; i++) {
			pProp->AddOption(m_FormatInts[i]);
		}
	}
	pCtrl->AddProperty(pProp);
}

void CFXBlockVisualShow::SetFormat(CString format)
{
	m_Format = format;
}

bool CFXBlockVisualShow::SetProperty(int nProperty, variant_t& value, CFXGraphView* pView)
{
	if (CFXBlock::SetProperty(nProperty,value,pView))
		return true;
	if (nProperty == PROP_FORMAT) {
		if (value.vt != VT_BSTR)
			return false;
		m_Format = CString(value);
		Invalidate(pView, REGION_BLOCK);
	}
	return false;
}

CFXBlockVisualShowFloat::CFXBlockVisualShowFloat()
{
}

CFXBlockVisualShowFloat::~CFXBlockVisualShowFloat()
{
}

void CFXBlockVisualShowFloat::Create(CFXObject* pObject)
{
	CFXBlockVisualShow::Create(pObject);
	m_InputPinTypes.AddTail(Float);
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	AddInputPin(Float, _T(""));
	m_Format = m_FormatFloats[0];
}

CFXBlockVisualShowInt::CFXBlockVisualShowInt()
{
}

CFXBlockVisualShowInt::~CFXBlockVisualShowInt()
{
}

void CFXBlockVisualShowInt::Create(CFXObject* pObject)
{
	CFXBlockVisualShow::Create(pObject);
	m_InputPinTypes.AddTail(Int);
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	AddInputPin(Int, _T(""));
	m_Format = m_FormatInts[0];
}

CFXBlockVisualShowLogical::CFXBlockVisualShowLogical()
{
}

CFXBlockVisualShowLogical::~CFXBlockVisualShowLogical()
{
}

void CFXBlockVisualShowLogical::Create(CFXObject* pObject)
{
	CFXBlockVisualShow::Create(pObject);
	m_InputPinTypes.AddTail(Logical);
	m_PinInMinCount = 1;
	m_PinInMaxCount = 1;
	AddInputPin(Logical, _T(""));
//	m_Format = m_FormatFloats[0];
}
