
#pragma once
/////////////////////////////////////////////////////////////////////////////
// Окно CViewTree

class CViewTree : public CTreeCtrl
{
// Создание
public:
	CViewTree();
	CImageList* m_pDragDropImage;
	bool m_bDragging;
	HTREEITEM m_hItem;
// Переопределение
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Реализация
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnTvnItemChanged(NMHDR *pNMHDR, LRESULT *pResult);
	int m_bAllowDragDrop;
};
