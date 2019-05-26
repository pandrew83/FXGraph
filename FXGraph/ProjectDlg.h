#pragma once


// диалоговое окно CProjectDlg

class CProjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CProjectDlg)

public:
	CProjectDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CProjectDlg();

// Данные диалогового окна
	enum { IDD = IDD_PROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
//	CString m_CycleTicks;
	int m_CycleTicks;
//	int m_Timer;
	int m_DebugTimer;
};
