// CommentDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "FXGraph.h"
#include "CommentDlg.h"
#include "afxdialogex.h"


// диалоговое окно CCommentDlg

IMPLEMENT_DYNAMIC(CCommentDlg, CDialog)

CCommentDlg::CCommentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommentDlg::IDD, pParent)
{

	m_Comment = _T("");
}

CCommentDlg::~CCommentDlg()
{
}

void CCommentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COMMENT, m_Comment);
}


BEGIN_MESSAGE_MAP(CCommentDlg, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CCommentDlg
