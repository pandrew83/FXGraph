#pragma once
#include "fxobject.h"
class CFXPin;

#define LINK_COLOR		RGB(0x7f,0x7f,0x7f)
class CFXPin;

class CFXLink :
	public CFXObject
{
protected:
	//int m_Pin1ID;
	//int m_Pin2ID;
	int GetNewID(){return 0;}
	CRect m_Rect1;
	CRect m_Rect2;
	CRect m_Rect3;
public:
	void Invalidate(CFXGraphView* pView, int regions);
	CFXLink();
	DECLARE_SERIAL(CFXLink);
	virtual void AfterSerialize();
	CFXPin* m_pIn;
	CFXPin* m_pOut;
	~CFXLink(void);
	CFXLink(CFXBlock* pBlock,CFXPin* pPinOut, CFXPin* pPinIn);
	void Draw(CFXGraphView*pView);
	int GetPropertyList(){
		return PROPLIST_LINK;
	}
	CFXObject* GetByID(int id){
		if (m_ID == id)
			return this;
		return NULL;
	}
	void Remove(void);
	virtual void Serialize(CArchive&ar);
};

typedef CList<CFXLink*,CFXLink*> CListLink;
