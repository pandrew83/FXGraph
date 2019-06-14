#pragma once


// диалоговое окно CCommentDlg

class CCommentDlg : public CDialog
{
	DECLARE_DYNAMIC(CCommentDlg)

public:
	CCommentDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CCommentDlg();

// Данные диалогового окна
	enum { IDD = IDD_COMMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_Comment;
};
