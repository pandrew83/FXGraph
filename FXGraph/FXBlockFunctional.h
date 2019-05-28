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
	CFXBlockFunctional(CFXBlock* pBlock):CFXBlock(pBlock){
		m_bCalc = true;
		m_pDebugFirst = NULL;
		m_LastID = m_ID+1;
		m_Width = 100;
		m_Height = 100;
		m_Name = "Functional";
		m_InputPinTypes.AddTail(Float);
		m_InputPinTypes.AddTail(Int);
		m_InputPinTypes.AddTail(Logical);
		m_OutputPinTypes.AddTail(Float);
		m_OutputPinTypes.AddTail(Int);
		m_OutputPinTypes.AddTail(Logical);
	}
	int GetClassID(){
		return BLOCK_FUNCTIONAL;
	}
//	CList<CFXObject*,CFXObject*> m_Objects;
	CList<CFXBlock*,CFXBlock*> m_Blocks;
	CList<CFXLink*,CFXLink*> m_Links;
//	CArray<CFXBlock*,CFXBlock*> m_Blocks;
//	int m_DebugIndex;
//	CFXBlock* m_pDebugCur;
	CFXBlock* m_pDebugFirst;
//	CList<CFXLink*,CFXLink*> m_Links;
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
	virtual CFXPin* AddInputPin(CFXPinType type, CString funcName, bool bAllowConst=true, bool bAllowParam=true, bool bConst=false, bool bLinkable=true);
	virtual CFXPin* AddOutputPin(CFXPinType type, CString funcName, bool bAllowConst=true, bool bAllowParam=true, bool bConst=false, bool bLinkable=true);
protected:
	int m_LastID;
public:
	void RemoveLink(CFXLink* pLink);
	CFXLink* GetLink(CFXPin* pPin1, CFXPin* pPin2);
	void RemoveBlock(CFXBlock* pBlock);
	void GetPinLinks(CListLink& lst, CFXPin* pPin);
	virtual bool Check(){
		bool result = CFXBlock::Check();
		if (!result)
			return false;
		POSITION pos = m_Blocks.GetHeadPosition();
		while (pos){
			CFXBlock* pBlock = m_Blocks.GetNext(pos);
			if (!pBlock->Check())
				return false;
		}
		return true;
	}
	void CalcOrder(void);
	bool Calc(void);
	bool IsRootBlock(){
		return m_pBlock == NULL;
	}
	void RemovePinLinks(CFXPin* pPin);
	void Initialize(void);
	void UpdateView();
};

