
// mdi_template.h : главный файл заголовка для приложения mdi_template
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// Cmdi_templateApp:
// О реализации данного класса см. mdi_template.cpp
//

class Cmdi_templateApp : public CWinAppEx
{
public:
	Cmdi_templateApp();


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
};

extern Cmdi_templateApp theApp;
