// ProjectDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "FXGraph.h"
#include "ProjectDlg.h"
#include "afxdialogex.h"


// диалоговое окно CProjectDlg

IMPLEMENT_DYNAMIC(CProjectDlg, CDialog)

CProjectDlg::CProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectDlg::IDD, pParent)
{

	//  m_CycleTicks = _T("");
	m_CycleTicks = 0;
	m_DebugTimer = 0;
}

CProjectDlg::~CProjectDlg()
{
}

void CProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_CBString(pDX, IDC_CYCLE_TICKS, m_CycleTicks);
	DDX_CBIndex(pDX, IDC_CYCLE_TICKS, m_CycleTicks);
	//	DDV_MinMaxInt(pDX, m_CycleTicks, 50, 10000);
	DDX_Text(pDX, IDC_TIMER, m_DebugTimer);
	DDV_MinMaxInt(pDX, m_DebugTimer, 100, 100000);
}


BEGIN_MESSAGE_MAP(CProjectDlg, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CProjectDlg
