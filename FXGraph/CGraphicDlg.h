#pragma once


// Диалоговое окно CGraphicDlg

class CGraphicDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphicDlg)

public:
	CGraphicDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CGraphicDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_Title;
};
