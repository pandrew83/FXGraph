#pragma once


// ���������� ���� CFingByIDDlg

class CFindByIDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindByIDDlg)

public:
	CFindByIDDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CFindByIDDlg();

// ������ ����������� ����
	enum { IDD = IDD_FINDID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_ID;
};
