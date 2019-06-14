#pragma once
#include "afxwin.h"
#include "FXObject.h"

// диалоговое окно CParamDlg

class CParamDlg : public CDialog
{
	DECLARE_DYNAMIC(CParamDlg)

public:
	CParamDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CParamDlg();

// Данные диалогового окна
	enum { IDD = IDD_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_Type;
	CString m_Name;
//	afx_msg void OnBnClickedRadio2();
	double m_valdbl;
	int m_valint;
//	BOOL m_valbool;
	afx_msg void OnCbnSelchangeCombo1();
//	CButton m_btnTrue;
//	CButton m_btnFalse;
	CEdit m_ctrlDouble;
	CEdit m_ctrlInt;
	virtual BOOL OnInitDialog();
//	afx_msg void OnSelendokCombo1();
	CComboBox m_ctrlType;
//	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedRadio1();
	BOOL m_valbool;
};
