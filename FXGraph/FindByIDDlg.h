#pragma once


// диалоговое окно CFingByIDDlg

class CFindByIDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindByIDDlg)

public:
	CFindByIDDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CFindByIDDlg();

// Данные диалогового окна
	enum { IDD = IDD_FINDID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_ID;
};
