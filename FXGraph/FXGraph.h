
// FXGraph.h : главный файл заголовка для приложения FXGraph
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы
#define VERSION_MAJOR	1
#define VERSION_MINOR	0

#define WEBHELP_URL "http://automatic.pandrew.ru"
// CFXGraphApp:
// О реализации данного класса см. FXGraph.cpp
//
//#include <stdint.h>

class CFXGraphApp : public CWinAppEx
{
public:
	CFXGraphApp();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnGrid();
public:
	int m_GridStep;
	bool m_GridState;
	int m_GridStyle;
	bool m_GridBind;
	COLORREF m_GridColor; 

//	afx_msg void OnClassviewmenuWebhelp();
	virtual int Run();
};

extern CFXGraphApp theApp;
