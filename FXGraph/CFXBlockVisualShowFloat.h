#pragma once
#include "FXBlock.h"

class CFXBlockVisualShow :
	public CFXBlock
{
public:
//	DECLARE_SERIAL(CFXBlockVisualShowFloat);
	CFXBlockVisualShow();
	~CFXBlockVisualShow();
	void Create(CFXObject* pObject);
	bool Calc();
	void Draw(CFXGraphView* pView);
	virtual void FillProperties(CPropertiesWnd* pWnd);
	void SetFormat(CString format);
	virtual bool SetProperty(int nProperty, variant_t& value, CFXGraphView* pView);
protected:
	CRect m_RectValue;
	CString m_Format;
	static int m_nFormatInts;
	static int m_nFormatFloats;
	static CString m_FormatFloats[2];
	static CString m_FormatInts[3];
};

class CFXBlockVisualShowFloat : public CFXBlockVisualShow {
public:
	DECLARE_SERIAL(CFXBlockVisualShowFloat);
	CFXBlockVisualShowFloat();
	~CFXBlockVisualShowFloat();
	void Create(CFXObject* pObject);
//	bool Calc();
};

class CFXBlockVisualShowInt : public CFXBlockVisualShow {
public:
	DECLARE_SERIAL(CFXBlockVisualShowInt);
	CFXBlockVisualShowInt();
	~CFXBlockVisualShowInt();
	void Create(CFXObject* pObject);
};

class CFXBlockVisualShowLogical : public CFXBlockVisualShow {
public:
	DECLARE_SERIAL(CFXBlockVisualShowLogical);
	CFXBlockVisualShowLogical();
	~CFXBlockVisualShowLogical();
	void Create(CFXObject* pObject);
};