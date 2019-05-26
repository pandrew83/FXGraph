#pragma once



#define AFX_FORMAT_CHAR   _T("%Tc")
#define AFX_FORMAT_SHORT  _T("%d")
#define AFX_FORMAT_LONG   _T("%ld")
#define AFX_FORMAT_USHORT _T("%u")
#define AFX_FORMAT_ULONG  _T("%u")
#define AFX_FORMAT_FLOAT  _T("%f")
#define AFX_FORMAT_DOUBLE _T("%lf")


class CPropertyGridCtrl : public CMFCPropertyGridCtrl
{
	friend class CProperty;
	DECLARE_DYNAMIC(CPropertyGridCtrl)

public:
	CPropertyGridCtrl();
	virtual ~CPropertyGridCtrl();
	TCHAR GetListDelimeter(){
		return m_cListDelimeter;
	}
	CString GetStrFalse(){
		return m_strFalse;
	}
	CString GetStrTrue(){
		return m_strTrue;
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL EditItem(CMFCPropertyGridProperty* pProp, LPPOINT lptClick = NULL){
		return CMFCPropertyGridCtrl::EditItem(pProp,lptClick);
	}

	virtual void OnPropertyChanged(CMFCPropertyGridProperty* pProp) const;
	virtual BOOL ValidateItemData(CMFCPropertyGridProperty* pProp);
};


class CProperty : public CMFCPropertyGridProperty{
public:
	CProperty(const CString& strGroupName,    DWORD_PTR dwData=0,    BOOL bIsValueList=FALSE) : CMFCPropertyGridProperty(strGroupName,dwData,bIsValueList){
	}
	CProperty(const CString& strName,
    const _variant_t& varValue,
    LPCTSTR lpszDescr=NULL,
    DWORD_PTR dwData=0,
    LPCTSTR lpszEditMask=NULL,
    LPCTSTR lpszEditTemplate=NULL,
    LPCTSTR lpszValidChars=NULL) : CMFCPropertyGridProperty(strName,varValue,lpszDescr,dwData,lpszEditMask,lpszEditTemplate,lpszValidChars){
	}
	CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat)
	{
		switch (m_varValue.vt)
		{
		case VT_BSTR:
		case VT_R4:
		case VT_R8:
		case VT_UI1:
		case VT_I2:
		case VT_INT:
		case VT_UINT:
		case VT_I4:
		case VT_UI2:
		case VT_UI4:
		case VT_I8:
		case VT_BOOL:
			break;

		default:
			if (!m_bIsValueList)
			{
				return NULL;
			}
		}

		CEdit* pWndEdit = NULL;

		if (!m_strEditMask.IsEmpty() || !m_strEditTempl.IsEmpty() || !m_strValidChars.IsEmpty())
		{
			CMFCMaskedEdit* pWndEditMask = new CMFCMaskedEdit;
			pWndEditMask->EnableSetMaskedCharsOnly(FALSE);
			pWndEditMask->EnableGetMaskedCharsOnly(FALSE);

			if (!m_strEditMask.IsEmpty() && !m_strEditTempl.IsEmpty())
			{
				pWndEditMask->EnableMask(m_strEditMask, m_strEditTempl, _T(' '));
			}

			if (!m_strValidChars.IsEmpty())
			{
				pWndEditMask->SetValidChars(m_strValidChars);
			}

			pWndEdit = pWndEditMask;
		}
		else
		{
			pWndEdit = new CEdit;
		}

		DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL;

		if (!m_bEnabled || !m_bAllowEdit)
		{
			dwStyle |= ES_READONLY;
		}

		pWndEdit->Create(dwStyle, rectEdit, m_pWndList, AFX_PROPLIST_ID_INPLACE);

		bDefaultFormat = TRUE;
		return pWndEdit;
	}

	virtual CString FormatProperty(){
		ASSERT_VALID(this);
		ASSERT_VALID(m_pWndList);

		COleVariant& var = m_varValue;

		CString strVal;

		if (m_bIsValueList)
		{
			for (POSITION pos = m_lstSubItems.GetHeadPosition(); pos != NULL;)
			{
				CMFCPropertyGridProperty* pProp = m_lstSubItems.GetNext(pos);
				ASSERT_VALID(pProp);

				strVal += pProp->FormatProperty();
				          
				if (pos != NULL)
				{
					strVal += ((CPropertyGridCtrl*)m_pWndList)->GetListDelimeter();
					strVal += _T(' ');
				}
			}

			return strVal;
		}

		switch (var.vt)
		{
		case VT_BSTR:
			strVal = var.bstrVal;
			break;

		case VT_I2:
			strVal.Format(AFX_FORMAT_SHORT, (short)var.iVal);
			break;

		case VT_I4:
		case VT_INT:
			strVal.Format(AFX_FORMAT_LONG, (long)var.lVal);
			break;

		case VT_UI1:
			if ((BYTE)var.bVal != 0)
			{
				strVal.Format(AFX_FORMAT_CHAR, (TCHAR)(BYTE)var.bVal);
			}
			break;

		case VT_UI2:
			strVal.Format(AFX_FORMAT_USHORT, var.uiVal);
			break;

		case VT_UINT:
		case VT_UI4:
			strVal.Format(AFX_FORMAT_ULONG, var.ulVal);
			break;

		case VT_R4:
			strVal.Format(AFX_FORMAT_DOUBLE, (float)var.fltVal);
			break;

		case VT_R8:
			strVal.Format(AFX_FORMAT_DOUBLE, (double)var.dblVal);
			break;

		case VT_BOOL:
			strVal = var.boolVal == VARIANT_TRUE ? ((CPropertyGridCtrl*)m_pWndList)->GetStrTrue() : ((CPropertyGridCtrl*)m_pWndList)->GetStrFalse();
			break;
		case VT_I8:
			strVal.Format(_T("%I64d"),var.llVal);  
			break;
		default:
			// Unsupported type
			strVal = _T("*** error ***");
		}

		return strVal;
	}
	BOOL TextToVar(const CString& strText)
	{
		CString strVal = strText;

		switch (m_varValue.vt)
		{
		case VT_BSTR:
			m_varValue = (LPCTSTR) strVal;
			return TRUE;

		case VT_UI1:
			m_varValue = strVal.IsEmpty() ?(BYTE) 0 :(BYTE) strVal[0];
			return TRUE;

		case VT_I2:
			m_varValue = (short) _ttoi(strVal);
			return TRUE;

		case VT_INT:
		case VT_I4:
			m_varValue = _ttol(strVal);
			return TRUE;

		case VT_UI2:
			m_varValue.uiVal = unsigned short(_ttoi(strVal));
			return TRUE;

		case VT_UINT:
		case VT_UI4:
			m_varValue.ulVal = unsigned long(_ttol(strVal));
			return TRUE;
		case VT_I8:
			m_varValue.llVal = (long long)(_ttoi64(strVal));
			return TRUE;
		case VT_R4:
			{
				float fVal = 0.;

				strVal.TrimLeft();
				strVal.TrimRight();

				if (!strVal.IsEmpty())
				{
					_stscanf_s(strVal, _T("")/*m_strFormatFloat*/, &fVal);
				}

				m_varValue = fVal;
			}
			return TRUE;

		case VT_R8:
			{
				double dblVal = 0.;

				strVal.TrimLeft();
				strVal.TrimRight();

				if (!strVal.IsEmpty())
				{
					_stscanf_s(strVal, _T("")/*m_strFormatDouble*/, &dblVal);
				}

				m_varValue = dblVal;
			}
			return TRUE;

		case VT_BOOL:
			strVal.TrimRight();
			m_varValue = (VARIANT_BOOL)(strVal == ((CPropertyGridCtrl*)m_pWndList)->GetStrTrue());
			return TRUE;
		}

		return FALSE;
	}
};