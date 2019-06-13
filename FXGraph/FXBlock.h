#pragma once
#include "stdafx.h"

#include "FXObject.h"
#include "FXException.h"
#include "FXPin.h"

void box(CDC*pDC, int x, int y, int d, COLORREF color);
void box(CDC*pDC, CPoint p, int d, COLORREF color);

class CFXPin;

class CFXBlock : public CFXObject
{
protected:
	int m_Width;
	int m_Height;
//	int m_SysTicks;
	CFXBlock(void) : m_CalcOrder(0), m_bBreakPoint(0)
	{}
	DECLARE_SERIAL(CFXBlock)
	int GetClassID(){return 0;}
	CRect m_RectName;
	CRect m_RectBlock;
	CRect m_RectLeft;
	CRect m_RectRight;
public:
	void InvalidateName(CFXGraphView* pView);
	void InvalidateBlock(CFXGraphView* pView);
	void InvalidateLeft(CFXGraphView* pView);
	void InvalidateRight(CFXGraphView* pView);
	void InvalidateLinks(CFXGraphView* pView);
	CFXBlock(CFXBlock*pBlock);
	~CFXBlock(void);
	void Invalidate(CFXGraphView* pView, int regions);
	void GetPinLinks(CListLink& lst, CFXPin* pPin);
	bool m_bCalc;
	int m_PinInMinCount;
	int m_PinOutMinCount;
	int m_PinInMaxCount;
	int m_PinOutMaxCount;
	int m_MinWidth;
	int m_MinHeight;
	CList<CFXPinType,CFXPinType> m_InputPinTypes;
	CList<CFXPinType,CFXPinType> m_OutputPinTypes;
	CList<CFXPin*,CFXPin*> m_InputPins;
	CList<CFXPin*,CFXPin*> m_OutputPins;
	virtual CFXObject* GetByID(int id);
	virtual int GetNewID(){
		return m_pBlock->GetNewID();
	}
	virtual void SetX(int x){
		CFXObject::SetX(x);
		CalcPinCoords();
	}
	virtual void SetY(int y){
		CFXObject::SetY(y);
		CalcPinCoords();
	}
	virtual void SetXY(int x, int y){
		CFXObject::SetXY(x,y);
		CalcPinCoords();
	}
	virtual void SetXY(CPoint p){
		CFXObject::SetXY(p);
		CalcPinCoords();
	}
	virtual void SetWidth(int w){
		m_Width = w;
		CalcPinCoords();
	}
	virtual void SetHeight(int h){
		m_Height = h;
		CalcPinCoords();
	}
	virtual void SetDimensions(int w, int h){
		m_Width = w;
		m_Height = h;
		CalcPinCoords();
	}
	virtual int GetWidth() const{
		return m_Width;
	}
	virtual int GetHeight() const{
		return m_Height;
	}
	//void SetSysTicks(int SysTicks){
	//	m_SysTicks = SysTicks;
	//}
	int GetSysTicks();
	virtual CFXPin* AddInputPin(CFXPinType type, CString funcName, bool bAllowConst=true, bool bAllowParam=true, bool bConst=false, int nFormat=0, bool bLinkable=true);
	virtual CFXPin* AddOutputPin(CFXPinType type, CString funcName, bool bAllowConst=true, bool bAllowParam=true, bool bConst=false, int nFormat=0, bool bLinkable=true);
	void CalcPinCoords();
	//void RedefinePinIDs(){
	//	int id = 1;
	//	POSITION pos = m_InputPins.GetHeadPosition();
	//	while (pos){
	//		CFXPin* pPin = m_InputPins.GetNext(pos);
	//		pPin->m_ID = (m_ID&MASK1_ID) | (id << 12);
	//		id++;
	//	}
	//	pos = m_OutputPins.GetHeadPosition();
	//	while (pos){
	//		CFXPin* pPin = m_OutputPins.GetNext(pos);
	//		pPin->m_ID = (m_ID&MASK1_ID) | (id << 12);
	//		id++;
	//	}
	//}
	void Draw(CFXGraphView*pView);
	virtual void Move(int dx, int dy){
		CFXObject::Move(dx,dy);
		CalcPinCoords();
	}
	int GetPropertyList(void);
	virtual void FillProperties(CPropertiesWnd* pWnd);
//	CFXPin* GetPinByID(int pin_id);
	void RemovePin(CFXPin* pPin);
	virtual void Serialize(CArchive& ar);
	void RemoveBlock(void);
	virtual bool Check(void);
	virtual bool Calc();
	int m_CalcOrder;
	CFXBlock* m_pNextBlock;
	void UpdateConnectedPins(void);
	void RemovePinLinks(CFXPin* pPin);
	CFXLink* GetLink(CFXPin* pPin1, CFXPin* pPin2);
	bool m_bBreakPoint;
	virtual void Initialize(void);
	virtual bool IsRemovable();
};


