// GridDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "FXGraph.h"
#include "GridDlg.h"
#include "afxdialogex.h"


// диалоговое окно CGridDlg

IMPLEMENT_DYNAMIC(CGridDlg, CDialogEx)

CGridDlg::CGridDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGridDlg::IDD, pParent)
{

	m_Step = 0;
	m_GridStyle = 0;
}

CGridDlg::~CGridDlg()
{
}

void CGridDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STEP, m_Step);
	DDV_MinMaxInt(pDX, m_Step, 5, 100);
	DDX_Radio(pDX, IDC_GRID_ONOFF, m_Grid_On);
	DDX_Radio(pDX, IDC_GRID_STYLE_POINTS, m_GridStyle);
	DDV_MinMaxInt(pDX, m_GridStyle, 0, 1);
	DDX_Check(pDX, IDC_GRID_BIND, m_GridBind);
	DDX_Control(pDX, IDC_COLOR, m_GridColor);
}


BEGIN_MESSAGE_MAP(CGridDlg, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений CGridDlg
