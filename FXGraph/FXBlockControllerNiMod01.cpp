#include "StdAfx.h"
#include "FXBlockControllerNiMod01.h"
#include "FXBlockFunctionalPin.h"
#include "PropertiesWnd.h"

IMPLEMENT_SERIAL(CFXBlockControllerNiMod01,CFXBlockController,1)

CFXBlockControllerNiMod01::CFXBlockControllerNiMod01(void)
{
}

CFXBlockControllerNiMod01::CFXBlockControllerNiMod01(CFXBlock* pBlock):CFXBlockController(pBlock){
	m_Name = "NiMod-01";
	m_bCalc = true;
	m_TicksPerSec = 1000;
	m_MinHeight = 400;
	m_MinWidth = 100;
	m_Height = 400;
	m_Width = 100;
	m_PinInMinCount = 14;
	m_PinInMaxCount = 14;
	m_PinOutMinCount = 4;
	m_PinOutMaxCount = 4;
	m_NetworkID = 1;
	m_InputPinTypes.AddTail(Logical);
	m_OutputPinTypes.AddTail(Float);
	m_OutputPinTypes.AddTail(Logical);
	AddInputPin(Logical,_T("DI.01"),false,true,true,false);
	AddInputPin(Logical,_T("DI.02"),false, true,true,false);
	AddInputPin(Logical,_T("DI.03"),false, true,true,false);
	AddInputPin(Logical,_T("DI.04"),false, true,true,false);
	AddInputPin(Logical,_T("DI.05"),false, true,true,false);
	AddInputPin(Logical,_T("DI.06"),false, true,true,false);
	AddInputPin(Logical,_T("DI.07"),false, true,true,false);
	AddInputPin(Logical,_T("DI.08"),false, true,true,false);
	AddInputPin(Float,_T("AI.01"),false, true,true,false);
	AddInputPin(Float,_T("AI.02"),false, true,true,false);
	AddInputPin(Float,_T("AI.03"),false, true,true,false);
	AddInputPin(Float,_T("AI.04"),false, true,true,false);
	AddInputPin(Float,_T("AI.05"),false, true,true,false);
	AddInputPin(Float,_T("AI.06"),false, true,true,false);
	AddOutputPin(Logical,_T("DO.01"),false, true,false);
	AddOutputPin(Logical,_T("DO.02"),false, true,false);
	AddOutputPin(Logical,_T("DO.03"),false, true,false);
	AddOutputPin(Logical,_T("DO.04"),false, true,false);
	
	int c_in = m_InputPins.GetCount();
	int c_out = m_OutputPins.GetCount();
	int h = m_Blocks.GetHead()->GetHeight();
	int d = 25;
	int h_in = c_in*h+(c_in-1)*d;
	int h_out = c_out*h+(c_out-1)*d;

	int y1 = -(h_in /2 /d )*d;
	int y2 = -(h_out /2 /d)*d;
	int x1 = -425;
	int x2 = 300;
	POSITION pos = m_Blocks.GetHeadPosition();
	while (pos){
		CFXBlockFunctionalPin* pBlock = dynamic_cast<CFXBlockFunctionalPin*>(m_Blocks.GetNext(pos));
		if (pBlock){
			if (pBlock->m_pLinkedPin->m_Dir == Input){
				pBlock->SetXY(x1,y1);
				y1 += pBlock->GetHeight()+d;
			}
			else{
				pBlock->SetXY(x2,y2);
				y2 += pBlock->GetHeight()+d;
			}
		}
	}
}

CFXBlockControllerNiMod01::~CFXBlockControllerNiMod01(void)
{
}



