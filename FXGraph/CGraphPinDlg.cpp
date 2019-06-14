// CGraphPinDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "FXGraph.h"
#include "CGraphPinDlg.h"
#include "afxdialogex.h"


// Диалоговое окно CGraphPinDlg

IMPLEMENT_DYNAMIC(CGraphPinDlg, CDialogEx)

CGraphPinDlg::CGraphPinDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAPHPIN, pParent)
{

}

CGraphPinDlg::~CGraphPinDlg()
{
}

void CGraphPinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_MFCCOLORBUTTON1, m_Color);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_ColorBtn);
}


BEGIN_MESSAGE_MAP(CGraphPinDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений CGraphPinDlg
