#pragma once


// ���������� ���� CProjectDlg

class CProjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CProjectDlg)

public:
	CProjectDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CProjectDlg();

// ������ ����������� ����
	enum { IDD = IDD_PROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
//	CString m_CycleTicks;
	int m_CycleTicks;
//	int m_Timer;
	int m_DebugTimer;
};
