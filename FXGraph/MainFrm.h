
// MainFrm.h : интерфейс класса CMainFrame
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "CFXDataCollector.h"

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
	CFXDataCollector m_DataCollector;
// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// Реализация
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // встроенные члены панели элементов управления
	bool m_bDebugRunning;
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCToolBar		  m_wndToolBarGrid;
	CMFCToolBar		  m_wndToolBarAlign;
	CMFCToolBar		  m_wndToolBarDebug;
	CMFCToolBar		  m_wndToolBarProject;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CMFCToolBarImages			m_ImagesDebug;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;
// Созданные функции схемы сообщений
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
//	afx_msg void OnGrid();
	void UpdatePropertiesWindow(void);
	void Log(CFXMsgType type, CString str);
	BOOL ValidateProperty(int nPropery,variant_t& value);
	afx_msg void OnUpdateIndicatorTicks(CCmdUI *pCmdUI);
	afx_msg void OnIndicatorTicks();
	afx_msg void OnClassviewmenuWebhelp();
	afx_msg void OnDebugStart();
	CFXGraphDoc* m_pDebugCurDoc;
//	void StartDebug(CFXGraphDoc* pDoc);
	CFXGraphDoc* GetCurDoc(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDebugStop();
	void OnDebugBreakPoint(CFXGraphDoc* pDoc);
	afx_msg void OnDebugRestart();
	afx_msg void OnDebugStepOver();
	afx_msg void OnDebugStepInto();
	afx_msg void OnUpdateDebugStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDebugStepInto(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDebugStepOver(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDebugStop(CCmdUI *pCmdUI);
	afx_msg void OnDebugPause();
	afx_msg void OnUpdateDebugPause(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProjectScenario(CCmdUI *pCmdUI);
	void OnDebugEndCycle(CFXGraphDoc* pDoc);
};


