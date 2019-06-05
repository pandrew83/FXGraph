#pragma once

#include "FXPin.h"

// Просмотр CFXGraphViewGraphic
class CFXGraphic;

class CFXGraphViewGraphic : public CView
{
	DECLARE_DYNCREATE(CFXGraphViewGraphic)

protected:
	CFXGraphViewGraphic();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CFXGraphViewGraphic();

public:
//	CList<CFXGraphicVariable*, CFXGraphicVariable*> m_Vars;
	CFXGraphic* m_pGraphic;
	CPoint Local2Logic(CPoint point);
	CPoint Logic2Local(CPoint point);
	int m_X;
	int m_Y;
	int m_StartX;
	int m_StartY;
	int m_Scale;
	CDC m_MemDC1;
	bool m_bButtonL;
	bool m_bButtonR;
	bool m_bButtonM;
	virtual void OnDraw(CDC* pDC);      // для отрисовки этого представления
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL OnToolTipNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CPoint m_Point;
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


