
// FXGraphView.h : интерфейс класса CFXGraphView
//

#pragma once
#include "FXGraphDoc.h"
#include "atltypes.h"
#include "afxcmn.h"

class CFXObject;
class CFXBlock;
class CFXBlockFunctional;
class CFXGraphDoc;
class CFXGraphViewScenario : public CEditView{
protected:
	CFXGraphViewScenario();
	DECLARE_DYNCREATE(CFXGraphViewScenario)
public:
	~CFXGraphViewScenario(){
	}

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	CFXGraphDoc* GetDocument() const;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChange();
	afx_msg void OnEnUpdate();
};

class CFXGraphView : public CView
{
protected: // создать только из сериализации
	CFXGraphView();
	DECLARE_DYNCREATE(CFXGraphView)

// јтрибуты
public:
	CFXGraphDoc* GetDocument() const;
	CDC m_Mem1;
	CDC m_Mem2;
	COleDropTarget m_DropTarget;
	int m_Scale;
	double m_x;
	double m_y;
	double m_oldx;
	double m_oldy;
	bool m_bResize;
	bool m_bMoving;
	CPoint m_Point;
	CFXObject* m_pCur;
	CFXObject* m_pObject;
	CList<CFXObject*,CFXObject*> m_Selected;

// ќперации
public:

// ѕереопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено дл¤ отрисовки этого представлени¤
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// –еализаци¤
public:
	virtual ~CFXGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// —озданные функции схемы сообщений
protected:
	BOOL OnToolTipNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CPoint Logic2Local(CPoint point);
	CPoint Local2Logic(CPoint point);
	//double Logic2Local(int v);
	//double Local2Logic(int v);
	bool m_bButtonR;
	bool m_bButtonL;
	bool m_bButtonM;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	CDC* m_pDC;
	bool IsSelected(CFXObject* pObject);
	afx_msg void OnAlignBottom();
	afx_msg void OnAlignLeft();
	afx_msg void OnAlignRight();
	afx_msg void OnAlignTop();
	CPoint GetNearestPoint(CPoint point);
	int m_ResizeObject;
	void UpdatePropertiesWnd(void);
	CPoint m_MousePos;
	void UpdateProperty(int nProperty, int v);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBlockInputpinAddLogical();
	afx_msg void OnBlockPinRemove();
	afx_msg void OnBlockInputpinAddFloat();
	afx_msg void OnBlockInputpinAddInt();
	afx_msg void OnBlockOutputpinAddFloat();
	afx_msg void OnBlockOutputpinAddInt();
	afx_msg void OnBlockOutputpinAddLogical();
//	afx_msg void OnUpdateBlockInputpinAddFloat(CCmdUI *pCmdUI);
	afx_msg void OnShowLinks();
	bool m_bShowLinks;
	bool m_bLinking;
	afx_msg void OnLinkRemove();
	afx_msg void OnBlockRemove();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CFXBlockFunctional* m_pBlock;
	CFXBlock* AddBlock(DWORD ID, CPoint point);
	bool OnUpdateProperty(int nProperty, variant_t& value);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	CToolTipCtrl m_ToolTip;
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBlockWebhelp();
	afx_msg void OnBlockBreakpoint();
	afx_msg void OnBlockPinRemoveLinks();
	void UnselectAll(void);
	void SelectObject(CFXObject* pObject);
	void SetActiveObject(CFXObject* pObject);
	void SetViewAt(CFXObject* pObject);
	afx_msg void OnPinGraphNew();
	afx_msg void OnPinGraph(UINT nID);
//	afx_msg void OnPaint();
//	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // отладочна¤ верси¤ в FXGraphView.cpp
inline CFXGraphDoc* CFXGraphView::GetDocument() const
   { return reinterpret_cast<CFXGraphDoc*>(m_pDocument); }
inline CFXGraphDoc* CFXGraphViewScenario::GetDocument() const
{ return reinterpret_cast<CFXGraphDoc*>(m_pDocument);}
#endif

