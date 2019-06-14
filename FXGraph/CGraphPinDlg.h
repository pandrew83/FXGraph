#pragma once


// Диалоговое окно CGraphPinDlg

class CGraphPinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphPinDlg)

public:
	CGraphPinDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CGraphPinDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPHPIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
//	COLORREF m_Color;
	CMFCColorButton m_ColorBtn;
};
