// FingByIDDlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "FXGraph.h"
#include "FindByIDDlg.h"
#include "afxdialogex.h"


// ���������� ���� CFingByIDDlg

IMPLEMENT_DYNAMIC(CFindByIDDlg, CDialogEx)

CFindByIDDlg::CFindByIDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindByIDDlg::IDD, pParent)
	, m_ID(0)
{

	m_ID = 0;
}

CFindByIDDlg::~CFindByIDDlg()
{
}

void CFindByIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ID);
}


BEGIN_MESSAGE_MAP(CFindByIDDlg, CDialogEx)
END_MESSAGE_MAP()


// ����������� ��������� CFingByIDDlg
