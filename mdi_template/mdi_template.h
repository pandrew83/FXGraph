
// mdi_template.h : ������� ���� ��������� ��� ���������� mdi_template
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// Cmdi_templateApp:
// � ���������� ������� ������ ��. mdi_template.cpp
//

class Cmdi_templateApp : public CWinAppEx
{
public:
	Cmdi_templateApp();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cmdi_templateApp theApp;
