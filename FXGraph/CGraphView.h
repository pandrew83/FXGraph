#pragma once

#include "ViewTree.h"

// CGraphView
class CGraphToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFXGraphDoc;
class CFXGraphic;

class CGraphView : public CDockablePane
{
	DECLARE_DYNAMIC(CGraphView)

public:
	CGraphView();
	virtual ~CGraphView();
	void UpdateView(CFXGraphDoc* pDoc);
protected:
	DECLARE_MESSAGE_MAP()
	void AdjustLayout();
	void OnChangeVisualStyle();
	CImageList m_GraphViewImages;
	CGraphToolBar m_wndToolBar;
	CColorTree m_wndGraphView;
//	CFXGraphDoc* m_pCurDoc;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnGraphAdd();
	afx_msg void OnGraphRename();
	afx_msg void OnGraphOpen();
	afx_msg void OnGraphRemove();
	afx_msg void OnGraphPinProperties();
	afx_msg void OnGraphPinRemove();
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


