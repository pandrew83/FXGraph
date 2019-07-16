#pragma once
#include "FXBlock.h"
#include "FXLink.h"

class CFXPin;
class CFXLink;

class CFXBlockFunctional : public CFXBlock
{
public:
	DECLARE_SERIAL(CFXBlockFunctional)
	CFXBlockFunctional(void);
	void Create(CFXObject* pObject);
	CList<CFXBlock*,CFXBlock*> m_Blocks;
	CList<CFXLink*,CFXLink*> m_Links;
	CFXBlock* m_pDebugFirst;
	~CFXBlockFunctional(void);
	void Draw(CFXGraphView*pView);
	void AddBlock(CFXBlock* pBlock);

	CFXObject* GetByID(int ID);
	int GetNewID(){
		if (m_pBlock)
			return m_pBlock->GetNewID();
		else
			return m_LastID++;
	}
	void Serialize(CArchive& ar);
	CFXLink* AddLink(CFXPin* pPin1, CFXPin* pPin2);
//	virtual CFXPin* AddInputPin(CFXPinType type, CString funcName, bool bAllowConst = true, bool bAllowParam = true, bool bConst = false, int nFormat = 0, bool bLinkable = true);
	virtual CFXPin* AddInputPin(CFXPinType type, CString funcName, bool bAllowConst = true, bool bAllowParam = true, bool bConst = false, int nFormat = 0,bool bLinkable=true);
	virtual CFXPin* AddOutputPin(CFXPinType type, CString funcName, bool bAllowConst=true, bool bAllowParam=true, bool bConst=false, int nFormat = 0, bool bLinkable=true);
	virtual void RemovePin(CFXPin* pPin);
protected:
	int m_LastID;
public:
	void RemoveLink(CFXLink* pLink);
	CFXLink* GetLink(CFXPin* pPin1, CFXPin* pPin2);
	void RemoveBlock(CFXBlock* pBlock);
	void GetPinLinks(CListLink& lst, CFXPin* pPin);
	virtual bool Check();
	void CalcOrder(void);
	bool Calc(void);
	bool IsRootBlock(){
		return m_pBlock == NULL;
	}
	void RemovePinLinks(CFXPin* pPin);
	void Initialize(void);
	void UpdateView();
};

