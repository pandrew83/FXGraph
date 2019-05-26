
// mdi_templateView.h : ��������� ������ Cmdi_templateView
//

#pragma once


class Cmdi_templateView : public CView
{
protected: // ������� ������ �� ������������
	Cmdi_templateView();
	DECLARE_DYNCREATE(Cmdi_templateView)

// ��������
public:
	Cmdi_templateDoc* GetDocument() const;

// ��������
public:

// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ����������
public:
	virtual ~Cmdi_templateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ���������� ������ � mdi_templateView.cpp
inline Cmdi_templateDoc* Cmdi_templateView::GetDocument() const
   { return reinterpret_cast<Cmdi_templateDoc*>(m_pDocument); }
#endif

