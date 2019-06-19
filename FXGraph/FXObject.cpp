#include "StdAfx.h"
#include "FXObject.h"
#include "PropertiesWnd.h"
#include "MainFrm.h"
#include "FXGraph.h"
#include "FXGraphDoc.h"
#include "FXBlockFunctional.h"

IMPLEMENT_SERIAL(CFXObject, CObject, 1)

void Log(CFXMsgType type,CString str){
	((CMainFrame*)(((CFXGraphApp*)AfxGetApp())->m_pMainWnd))->Log(type,str);

}

void WriteStr(CArchive& ar, LPCSTR fmt,...){
	va_list args;
	va_start(args,fmt);

	CStringA str;
	str.FormatV(fmt,args);
	va_end(args);
	ar.Write((LPCTSTR)str.GetBuffer(),str.GetLength());
}

CFXObject::CFXObject(void)
{
	m_ID = 0;
	m_Name = "";
	m_SaveX = 0;
	m_SaveY = 0;
	m_Style = 0;
	m_X = 0;
	m_Y = 0;
	m_pBlock = NULL;
}


CFXObject::~CFXObject(void)
{

}


void CFXObject::StartMoving(void)
{
	m_SaveX = m_X;
	m_SaveY = m_Y;
}


void CFXObject::Move(int dx, int dy)
{
	m_X = m_SaveX + dx;
	m_Y = m_SaveY + dy;
}

void CFXObject::Serialize(CArchive& ar){
	TracePrint(TRACE_LEVEL_3,"CFXObject::Serialize");
	CObject::Serialize(ar);
	if (ar.IsStoring()){
		TracePrint(TRACE_LEVEL_3,"CFXObject::Serialize:Storing id=%d name=%s",m_ID,m_Name);
		ar << m_ID;
		ar << m_Name;
		ar << m_X;
		ar << m_Y;
	}
	else{
		ar >> m_ID;
		ar >> m_Name;
		ar >> m_X;
		ar >> m_Y;
	}

}

void CFXObject::FillProperties(CPropertiesWnd* pWnd){
	CPropertyGridCtrl* pCtrl =  &pWnd->m_wndPropList;
	pCtrl->RemoveAll();
	CMFCPropertyGridProperty* pProp;
	pProp = new CMFCPropertyGridProperty(_T("ID"),(variant_t)m_ID,_T("Идентификатор объекта"));
	pProp->AllowEdit(false);
	pCtrl->AddProperty(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Наименование"),m_Name,_T("Наименование блока"),PROP_NAME);
	pCtrl->AddProperty(pProp);

	pProp = new CMFCPropertyGridProperty( _T("X"), (_variant_t) m_X, _T("Указывает положение блока"),PROP_COORDX);
	pCtrl->AddProperty(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Y"), (_variant_t) m_Y, _T("Указывает положение блока"),PROP_COORDY);
	pCtrl->AddProperty(pProp);
//	pWnd->m_Properties[PROP_COORDX]->SetValue((_variant_t)m_X);
//	pWnd->m_Properties[PROP_COORDY]->SetValue((_variant_t)m_Y);
//	pWnd->m_Properties[PROP_NAME]->SetValue((_variant_t)m_Name);
}



CFXGraphDoc* CFXObject::GetActiveDocument(void)
{
	CMDIChildWnd * pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

      if ( !pChild )
          return NULL;

      CDocument * pDoc = pChild->GetActiveDocument();

      if ( !pDoc )
         return NULL;

      // Ошибка, если документ неправильного типа
      if ( ! pDoc->IsKindOf( RUNTIME_CLASS(CFXGraphDoc) ) )
         return NULL;

      return (CFXGraphDoc *) pDoc;
}


void CFXObject::Invalidate(CFXGraphView* pView, int regions)
{
}


CString CFXObject::GetClassDescriptorByID(int id)
{
	switch (id) {
		case BLOCK_FUNCTIONAL:
			return _T("CFXBlockFunctional");
		case BLOCK_FUNCTIONAL_PIN:
			return _T("CFXBlockFunctionalPin");
		case BLOCK_COMMENT:
			return _T("CFXBlockComment");
		case BLOCK_COMPARATOR_UP:
			return _T("CFXBlockComparatorUp");
		case BLOCK_COMPARATOR_DOWN:
			return _T("CFXBlockComparatorDown");
		case BLOCK_LOGICAL_AND:
			return _T("CFXBlockLogicalAnd");
		case BLOCK_LOGICAL_OR:
			return _T("CFXBlockLogicalOr");
		case BLOCK_LOGICAL_NOT:
			return _T("CFXBlockLogicalNot");
		case BLOCK_LOGICAL_XOR:
			return _T("CFXBlockLogicalXor");
		case BLOCK_LOGICAL_RISING_EDGE:
			return _T("CFXBlockLogicalRisingEdge");
		case BLOCK_LOGICAL_FALLING_EDGE:
			return _T("CFXBlockLogicalFallingEdge");
		case BLOCK_LOGICAL_TRIGGER_RS:
			return _T("CFXBlockLogicalTriggerRS");
		case BLOCK_LOGICAL_TRIGGER_SR:
			return _T("CFXBlockLogicalTriggerSR");
		case BLOCK_LOGICAL_TRIGGER_RS_RE:
			return _T("CFXBlockLogicalTriggerRSRisingEdge");
		case BLOCK_LOGICAL_FRONTS:
			return _T("CFXBlockLogicalFronts");
		case BLOCK_COUNTER:
			return _T("CFXBlockCounter");
		case BLOCK_MATH_INT_ADD:
			return _T("CFXBlockMathIntAdd");
		case BLOCK_MATH_INT_SUB:
			return _T("CFXBlockMathIntSub");
		case BLOCK_MATH_INT_MUL:
			return _T("CFXBlockMathIntMul");
		case BLOCK_MATH_INT_DIV:
			return _T("CFXBlockMathIntDiv");
		case BLOCK_MATH_INT_MOD:
			return _T("CFXBlockMathIntMod");
		case BLOCK_MATH_INT_ABS:
			return _T("CFXBlockMathIntAbs");
		case BLOCK_MATH_INT_EQUAL:
			return _T("CFXBlockMathIntEqual");
		case BLOCK_MATH_INT_GREAT:
			return _T("CFXBlockMathIntGreat");
		case BLOCK_MATH_INT_GREATEQUAL:
			return _T("CFXBlockMathIntGreatEqual");
		case BLOCK_MATH_INT_LESS:
			return _T("CFXBlockMathIntLess");
		case BLOCK_MATH_INT_LESSEQUAL:
			return _T("CFXBlockMathIntLessEqual");
		case BLOCK_MATH_INT_NOTEQUAL:
			return _T("CFXBlockMathIntNotEqual");
		case BLOCK_MATH_FLOAT_ADD:
			return _T("CFXBlockMathFloatAdd");
		case BLOCK_MATH_FLOAT_SUB:
			return _T("CFXBlockMathFloatSub");
		case BLOCK_MATH_FLOAT_MUL:
			return _T("CFXBlockMathFloatMul");
		case BLOCK_MATH_FLOAT_DIV:
			return _T("CFXBlockMathFloatDiv");
		case BLOCK_MATH_FLOAT_GREAT:
			return _T("CFXBlockMathFloatGreat");
		case BLOCK_MATH_FLOAT_GREATEQUAL:
			return _T("CFXBlockMathFloatGreatEqual");
		case BLOCK_MATH_FLOAT_LESS:
			return _T("CFXBlockMathFloatLess");
		case BLOCK_MATH_FLOAT_LESSEQUAL:
			return _T("CFXBlockMathFloatLessEqual");
		case BLOCK_MATH_FLOAT_EQUAL:
			return _T("CFXBlockMathFloatEqual");
		case BLOCK_MATH_FLOAT_NOTEQUAL:
			return _T("CFXBlockMathFloatNotEqual");
		case BLOCK_MATH_FLOAT_ABS:
			return _T("CFXBlockMathFloatAbs");
		case BLOCK_MATH_FLOAT_FLOOR:
			return _T("CFXBlockMathFloatFloor");
		case BLOCK_MATH_FLOAT_ROUND:
			return _T("CFXBlockMathFloatRound");
		case BLOCK_MATH_COS:
			return _T("CFXBlockMathCos");
		case BLOCK_MATH_SIN:
			return _T("CFXBlockMathSin");
		case BLOCK_MATH_TAN:
			return _T("CFXBlockMathTan");
		case BLOCK_MATH_SQRT:
			return _T("CFXBlockMathSqrt");
		case BLOCK_MATH_POW:
			return _T("CFXBlockMathPow");
		case BLOCK_MATH_LOG:
			return _T("CFXBlockMathLog");
		case BLOCK_MATH_LOG10:
			return _T("CFXBlockMathLog10");
		case BLOCK_MATH_ACOS:
			return _T("CFXBlockMathAcos");
		case BLOCK_MATH_ASIN:
			return _T("CFXBlockMathAsin");
		case BLOCK_MATH_ATAN:
			return _T("CFXBlockMathAtan");
		case BLOCK_MATH_EXP:
			return _T("CFXBlockMathExp");
		case BLOCK_MATH_CAST_FLOAT_INT:
			return _T("CFXBlockMathCastFloatInt");
		case BLOCK_MATH_CAST_INT_FLOAT:
			return _T("CFXBlockMathCastIntFloat");
		case BLOCK_MATH_BITWISE_AND:
			return _T("CFXBlockMathBitwiseAnd");
		case BLOCK_MATH_BITWISE_OR:
			return _T("CFXBlockMathBitwiseOr");
		case BLOCK_MATH_BITWISE_XOR:
			return _T("CFXBlockMathBitwiseXor");
		case BLOCK_MATH_BITWISE_NOT:
			return _T("CFXBlockMathBitwiseNot");
		case BLOCK_MATH_BITWISE_SHIFT_LEFT:
			return _T("CFXBlockMathBitwiseShiftLeft");
		case BLOCK_MATH_BITWISE_SHIFT_RIGHT:
			return _T("CFXBlockMathBitwiseShiftRight");
		case BLOCK_MATH_BITWISE_PACK:
			return _T("CFXBlockMathBitwisePack");
		case BLOCK_MATH_BITWISE_UNPACK:
			return _T("CFXBlockMathBitwiseUnpack");
		case BLOCK_ANTIBOUNCE:
			return _T("CFXBlockAntiBounce");
		case BLOCK_DELAY_ON:
			return _T("CFXBlockDelayOn");
		case BLOCK_DELAY_OFF:
			return _T("CFXBlockDelayOff");
		case BLOCK_CONTROLLER_NIMOD01:
			return _T("CFXBlockControllerNiMod01");
		case BLOCK_EXTENSION_NIMODA01:
			return _T("CFXBlockExtensionA01");
		case BLOCK_SENSOR_TRD_2W_PT100:
			return _T("CFXBlockSensorTRD2WPt100");
		case BLOCK_SENSOR_TRD_2W_PT500:
			return _T("CFXBlockSensorTRD2WPt500");
		case BLOCK_SENSOR_TRD_2W_PT1000:
			return _T("CFXBlockSensorTRD2WPt1000");
		case BLOCK_SENSOR_TRD_2W_M50:
			return _T("CFXBlockSensorTRD2WM50");
		case BLOCK_SENSOR_TRD_2W_M100:
			return _T("CFXBlockSensorTRD2WM100");
		case BLOCK_SENSOR_TRD_2W_P50:
			return _T("CFXBlockSensorTRD2WP50");
		case BLOCK_SENSOR_TRD_2W_P100:
			return _T("CFXBlockSensorTRD2WP100");
		case BLOCK_SENSOR_TRD_3W_PT100:
			return _T("CFXBlockSensorTRD3WPt100");
		case BLOCK_SENSOR_TRD_3W_PT500:
			return _T("CFXBlockSensorTRD3WPt500");
		case BLOCK_SENSOR_TRD_3W_PT1000:
			return _T("CFXBlockSensorTRD3WPt1000");
		case BLOCK_SENSOR_TRD_3W_M50:
			return _T("CFXBlockSensorTRD3WM50");
		case BLOCK_SENSOR_TRD_3W_M100:
			return _T("CFXBlockSensorTRD3WM100");
		case BLOCK_SENSOR_TRD_3W_P50:
			return _T("CFXBlockSensorTRD3WP50");
		case BLOCK_SENSOR_TRD_3W_P100:
			return _T("CFXBlockSensorTRD3WP100");
		case BLOCK_SENSOR_TRD_4W_PT100:
			return _T("CFXBlockSensorTRD4WPt100");
		case BLOCK_SENSOR_TRD_4W_PT500:
			return _T("CFXBlockSensorTRD4WPt500");
		case BLOCK_SENSOR_TRD_4W_PT1000:
			return _T("CFXBlockSensorTRD4WPt1000");
		case BLOCK_SENSOR_TRD_4W_M50:
			return _T("CFXBlockSensorTRD4WM50");
		case BLOCK_SENSOR_TRD_4W_M100:
			return _T("CFXBlockSensorTRD4WM100");
		case BLOCK_SENSOR_TRD_4W_P50:
			return _T("CFXBlockSensorTRD4WP50");
		case BLOCK_SENSOR_TRD_4W_P100:
			return _T("CFXBlockSensorTRD4WP100");
		case BLOCK_TRANSFORM_CURRENT:
			return _T("CFXBlockTransformCurrent");
		case BLOCK_TRANSFORM_LINEAR:
			return _T("CFXBlockTransformLinear");
		case BLOCK_TRANSFORM_LINEAR_LIMITS:
			return _T("CFXBlockTransformLinearLimits");
		case FXLINK:
			return _T("CFXLink");
		case FXPIN:
			return _T("CFXPin");
	}
	throw new CFXException(_T("GetClassDescriptorByID: Unknown id"));
}
