// CGraphicDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "FXGraph.h"
#include "CGraphicDlg.h"
#include "afxdialogex.h"


// Диалоговое окно CGraphicDlg

IMPLEMENT_DYNAMIC(CGraphicDlg, CDialogEx)

CGraphicDlg::CGraphicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAPH, pParent)
	, m_Title(_T(""))
{

}

CGraphicDlg::~CGraphicDlg()
{
}

void CGraphicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Title);
}


BEGIN_MESSAGE_MAP(CGraphicDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений CGraphicDlg
