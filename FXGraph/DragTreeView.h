#pragma once


// представление CDragTreeView

class CDragTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CDragTreeView)

protected:
	CDragTreeView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CDragTreeView();

public:
	virtual void OnFinalRelease();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


