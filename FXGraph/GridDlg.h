#pragma once


// ���������� ���� CGridDlg

class CGridDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGridDlg)

public:
	CGridDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CGridDlg();

// ������ ����������� ����
	enum { IDD = IDD_GRID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_Step;
	BOOL m_Grid_On;
	int m_GridStyle;
	BOOL m_GridBind;
	CMFCColorButton m_GridColor;
};
