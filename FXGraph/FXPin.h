#pragma once
#include "FXObject.h"
#include "FXLink.h"
#include "comutil.h"
#include "atltypes.h"
//#include "FXGraphView.h"


CArchive& operator<<(CArchive&ar, CFXPinType type);
CArchive& operator>>(CArchive& ar, CFXPinType& type);
CArchive& operator<<(CArchive&ar, CFXPinDir dir);
CArchive& operator>>(CArchive&ar, CFXPinDir&dir);

#define PIN_SIZE					10
#define PIN_COLOR_TYPE_LOGICAL		RGB(0,0,255)
#define PIN_COLOR_TYPE_INT			RGB(0,255,0)
#define PIN_COLOR_TYPE_FLOAT		RGB(0xcd,0,0xcd)
#define PIN_DISTANCE				4
#define PIN_FUNC_NAME_COLOR			RGB(0x80,0x80,0x80)
#define PIN_NAME_COLOR				RGB(0,0,0)

class CFXBlock;
class CFXLink;
class CFXObject;

class CFXPin : public CFXObject
{
	friend class CFXBlock;
public:
	enum{
		INT,
		UNSIGNED,
		HEX
	} Formats_Int;
	enum{
		FLOAT3,
		FLOAT1
	} Format_Floats;

protected:
	static int m_nFormatInts;
	static int m_nFormatFloats;
	static CString m_FormatFloats[2];
	static CString m_FormatInts[3];
	CString m_FuncName;
	virtual int GetNewID(){return 0;}
	CList<CFXPin*,CFXPin*> m_ConnectedPins;
//	CFXPin* m_pConnectedPin;
	variant_t m_Value;
public:
	void GetPinLinks(CListLink& lst);
	void CalcRects(CFXGraphView* pView);
	void AddConnectedPin(CFXPin* pPin){
		m_ConnectedPins.AddTail(pPin);
	}
	void RemoveConnectedPin(CFXPin* pPin){
		POSITION pos = m_ConnectedPins.Find(pPin);
		if (pos){
			m_ConnectedPins.RemoveAt(pos);
		}
	}
	bool IsConnectedPin(CFXPin* pPin){
		return m_ConnectedPins.Find(pPin) != NULL;
	}
	POSITION GetConnectedPins(){
		return m_ConnectedPins.GetHeadPosition();
	}
	CFXPin* GetNextConnectedPin(POSITION&pos){
		return m_ConnectedPins.GetNext(pos);
	}
	int GetConnectedPinsCount(){
		return m_ConnectedPins.GetCount();
	}
	bool m_bConst;
	bool m_bAllowParam;
	bool m_bAllowConst;
	bool m_bLinkable;
	CFXPinType m_Type;
	CFXPinDir m_Dir;
//	CList<CFXLink*,CFXLink*> m_Links;
	int GetClassID(){
		return FXPIN;
	}
	CString GetClassDescriptor() {
		return _T("CFXPin");
	}
	virtual void SetFuncName(CString funcName){
		m_FuncName = funcName;
	}
	CString GetFuncName(){
		return m_FuncName;
	}
	CFXPin(void);
	DECLARE_SERIAL(CFXPin)
	CFXPin(CFXPinDir dir, CFXPinType type, CString funcName, CFXBlock*pBlock, bool bAllowConst=true, bool bAllowParam=true, bool bConst=false,int nFormat=0, bool bLinkable=true):CFXObject(pBlock,_T("")){
		m_Type = type;
		m_Dir = dir;
		m_FuncName = funcName;
		m_bLinkable = bLinkable;
		m_bConst = bConst;
		m_pParam = NULL;
		m_bAllowConst = bAllowConst;
		m_bAllowParam = bAllowParam;
		switch(m_Type){
		case Logical:
			m_Value = false;
			m_Format = "";
			break;
		case Int:
			m_Value = (int)0;
			m_Format = CFXPin::m_FormatInts[nFormat];
			break;
		case Float:
			m_Value = (double)0;
			m_Format = CFXPin::m_FormatFloats[nFormat];
			break;
		}
	}
	~CFXPin(void);
	void Draw(CFXGraphView*pView);
	int GetPropertyList(){
		return PROPLIST_PIN;
	}
	CFXObject* GetByID(int id){
		return m_ID==id?this:NULL;
	}
	void Remove(void);
	virtual void Serialize(CArchive& ar);
	void FillProperties(CPropertiesWnd* pWnd);
	CFXParam* m_pParam;
	void SetParam(CFXParam* pParam);
	void SetValue(variant_t value);
	variant_t GetValue(void);
	CFXLink* GetLink(CFXPin* pPin);
	void RemoveLinks(void);
	CString m_Format;
	void Invalidate(CFXGraphView* pView,int regions);
protected:
	CRect m_RectValue;
	CRect m_RectName;
	CRect m_RectFuncName;
	CRect m_RectPin;
};

