#pragma once


// Просмотр CFXGraphViewGraphic

class CFXGraphViewGraphic : public CView
{
	DECLARE_DYNCREATE(CFXGraphViewGraphic)

protected:
	CFXGraphViewGraphic();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CFXGraphViewGraphic();

public:
	virtual void OnDraw(CDC* pDC);      // для отрисовки этого представления
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


