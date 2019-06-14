
// ChildFrm.h : интерфейс класса CChildFrame
//

#pragma once
//class CFXBlockFunctional;

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// јтрибуты
public:

// ќперации
public:

// ѕереопределение
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// –еализаци¤
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// —озданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
//	CFXBlockFunctional* m_pBlock;
	afx_msg void OnClose();
//	afx_msg void OnIdclose();
};
