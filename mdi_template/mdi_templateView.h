
// mdi_templateView.h : интерфейс класса Cmdi_templateView
//

#pragma once


class Cmdi_templateView : public CView
{
protected: // создать только из сериализации
	Cmdi_templateView();
	DECLARE_DYNCREATE(Cmdi_templateView)

// Атрибуты
public:
	Cmdi_templateDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~Cmdi_templateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // отладочная версия в mdi_templateView.cpp
inline Cmdi_templateDoc* Cmdi_templateView::GetDocument() const
   { return reinterpret_cast<Cmdi_templateDoc*>(m_pDocument); }
#endif

