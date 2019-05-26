// ParamDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "FXGraph.h"
#include "ParamDlg.h"
#include "afxdialogex.h"
#include "FXPin.h"

// диалоговое окно CParamDlg

IMPLEMENT_DYNAMIC(CParamDlg, CDialog)

CParamDlg::CParamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParamDlg::IDD, pParent)
{

	m_Type = _T("");
	m_Name = _T("");
	m_valdbl = 0.0;
	m_valint = 0;
}

CParamDlg::~CParamDlg()
{
}

void CParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_Type);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT2, m_valdbl);
	DDX_Text(pDX, IDC_EDIT3, m_valint);
	//  DDX_Radio(pDX, IDC_RADIO1, m_valbool);
	//  DDX_Control(pDX, IDC_RADIO1, m_btnTrue);
	//  DDX_Control(pDX, IDCANCEL, m_btnFalse);
	DDX_Control(pDX, IDC_EDIT2, m_ctrlDouble);
	DDX_Control(pDX, IDC_EDIT3, m_ctrlInt);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlType);
	DDX_Radio(pDX, IDC_RADIO1, m_valbool);
}


BEGIN_MESSAGE_MAP(CParamDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CParamDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_RADIO1, &CParamDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// обработчики сообщений CParamDlg


//void CParamDlg::OnBnClickedRadio2()
//{
//	// TODO: добавьте свой код обработчика уведомлений
//}


void CParamDlg::OnCbnSelchangeCombo1()
{
	CString str;
	int curSel = m_ctrlType.GetCurSel();
	m_ctrlType.GetLBText(curSel,m_Type);

	if (m_Type == "Logical"){
		m_ctrlInt.ShowWindow(SW_HIDE);
		m_ctrlDouble.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO2)->ShowWindow(SW_SHOW);

	}
	if (m_Type == "Int"){
		m_ctrlDouble.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
		m_ctrlInt.ShowWindow(SW_SHOW);
	}
	if (m_Type == "Float"){
		GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
		m_ctrlInt.ShowWindow(SW_HIDE);
		m_ctrlDouble.ShowWindow(SW_SHOW);
	}
}


BOOL CParamDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	if (m_Type == "Logical"){
		m_ctrlInt.ShowWindow(SW_HIDE);
		m_ctrlDouble.ShowWindow(SW_HIDE);
	}
	if (m_Type == "Int"){
		m_ctrlDouble.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
	}
	if (m_Type == "Float"){
		GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
		m_ctrlInt.ShowWindow(SW_HIDE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}


//void CParamDlg::OnSelendokCombo1()
//{
//}


//void CParamDlg::OnEnChangeEdit2()
//{
//	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
//	// send this notification unless you override the CDialog::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Добавьте код элемента управления
//}


void CParamDlg::OnBnClickedRadio1()
{
	// TODO: добавьте свой код обработчика уведомлений
}
