#pragma once


// ���������� ���� CCommentDlg

class CCommentDlg : public CDialog
{
	DECLARE_DYNAMIC(CCommentDlg)

public:
	CCommentDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CCommentDlg();

// ������ ����������� ����
	enum { IDD = IDD_COMMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_Comment;
};
