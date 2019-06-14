﻿#pragma once
#include "fxblock.h"

class CFXBlockComment :
	public CFXBlock
{
protected:
	CString m_Comment;
public:
	CFXBlockComment(void);
	CFXBlockComment(CFXBlock* pBlock):CFXBlock(pBlock){
		m_Comment = _T("");
		m_Name = "Комментарий";
		m_FontSize = 12;
		m_bCalc = false;
	}
	int GetPropList(){
		return PROPLIST_COMMENT;
	}
	DECLARE_SERIAL(CFXBlockComment);
	int GetClassID(){
		return BLOCK_COMMENT;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockComment");
	}
	CString GetComment(){
		return m_Comment;
	}
	void SetComment(CString comment){
		m_Comment = comment;
	}
	virtual void Serialize(CArchive& ar){
		CFXBlock::Serialize(ar);
		if (ar.IsStoring()){
			ar << m_Comment;
			ar << m_FontSize;
		}
		else{
			ar >> m_Comment;
			ar >> m_FontSize;
		}
	}
	~CFXBlockComment(void);
	void Draw(CFXGraphView* pView);
	virtual bool Check(){
		return true;
	}
	int m_FontSize;
	void SetFontSize(int fontSize);
	int GetFontSize(void);
};

