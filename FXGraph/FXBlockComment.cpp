#include "StdAfx.h"
#include "FXBlockComment.h"
#include "FXGraphView.h"

IMPLEMENT_SERIAL(CFXBlockComment,CFXBlock,1);

CFXBlockComment::CFXBlockComment(void)
	: m_FontSize(0)
{
	m_Comment = _T("");
}

void CFXBlockComment::Create(CFXObject* pObject)
{
	CFXBlock::Create(pObject);
	m_Comment = _T("");
	m_Name = "Комментарий";
	m_FontSize = 12;
	m_bCalc = false;
}

CFXBlockComment::~CFXBlockComment(void)
{
}


void CFXBlockComment::Draw(CFXGraphView* pView)
{
	CFXBlock::Draw(pView);
	CPen pen;
	CBrush brush;

	LOGFONT lf;
	memset(&lf,0,sizeof(LOGFONT));
	lf.lfHeight = m_FontSize*pView->m_Scale/100;
	wcscpy(lf.lfFaceName,_T("Arial"));
	CFont font;
	font.CreateFontIndirect(&lf);
	pView->m_pDC->SelectObject(font);
	CRect rectText(pView->Logic2Local(CPoint(m_X+5,m_Y+25)),pView->Logic2Local(CPoint(m_X+m_Width-6,m_Y+m_Height-2)));
	pView->m_pDC->DrawText(m_Comment,&rectText,DT_LEFT|DT_NOPREFIX|DT_WORDBREAK);

}


void CFXBlockComment::SetFontSize(int fontSize)
{
	m_FontSize = fontSize;
}


int CFXBlockComment::GetFontSize(void)
{
	return m_FontSize;
}
