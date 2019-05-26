
// FXGraphDoc.h : интерфейс класса CFXGraphDoc
//

#pragma once
#include "FXParam.h"

class CFXBlock;
class CFXBlockFunctional;
class CFXLink;
class CFXParam;
class CFXPin;
//class CListParam;

class CFXGraphDoc : public CDocument
{
protected: // создать только из сериализации
	CFXGraphDoc();
	DECLARE_DYNCREATE(CFXGraphDoc)
	
// Атрибуты
public:
	CFXBlockFunctional* m_pBlock;
//	int m_LastID;
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CFXGraphDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	//CFXLink* AddLink(CFXPin* pPin1, CFXPin* pPin2);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
//	afx_msg void OnDebugRestart();
//	afx_msg void OnDebugStart();
//	afx_msg void OnDebugStop();
	CFXBlock* m_pDebugCur;
	void UpdateCalcOrder(void);
	CList<CFXParam*, CFXParam*> m_InputParams;
	CList<CFXParam*, CFXParam*> m_OutputParams;
	bool IsDebug(){
		return m_bDebug;
	}
protected:
public:
	bool m_bDebug;
	int m_SysTick;
	int m_CycleTicks;
	bool InitializeBlocks(void);
//	afx_msg void OnParams();
//	afx_msg void OnDebugStepInto();
//	afx_msg void OnDebugStepOver();
	CFXParam* GetInputParam(CString param);
	CFXParam* GetOutputParam(CString paramName);
	void OnParameterUpdated(CFXParam* pParam);
	bool CheckParamName(CString paramName);
	CFXGraphView* OpenBlock(CFXBlockFunctional* pBlockFunc);
	CFXGraphView* GetBlockView(CFXBlockFunctional* pBlockFunc);
	void OnRemoveBlock(CFXBlock* pBlock);
//	afx_msg void OnDebugStepTo();
	void OnDebugCycleEnd(void);
	afx_msg void OnProjectProperties();
	afx_msg void OnFindbyid();
	void DebugStart();
	void DebugRun(void);
	void CalcOrder(void);
	void DebugStop(void);
	void DebugStep(void);

	void UpdateBlock(CFXBlock* pBlock, bool activete=true);
	void DebugStepOver(void);
	void DebugPause(void);
	int m_DebugTimer;
	afx_msg void OnProjectScenario();
	CString m_DebugScenario;
	void InitializeScenario(void);
};
