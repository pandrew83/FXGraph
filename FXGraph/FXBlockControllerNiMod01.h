#pragma once
#include "fxblockcontroller.h"
//#include <stdint.h>

class CFXBlockControllerNiMod01 :
	public CFXBlockController
{
public:
	DECLARE_SERIAL(CFXBlockControllerNiMod01);
	int m_NetworkID;
	CFXBlockControllerNiMod01(void);
	CFXBlockControllerNiMod01(CFXBlock* pBlock);
	~CFXBlockControllerNiMod01(void);
	int GetClassID(){
		return BLOCK_CONTROLLER_NIMOD01;
	}
	virtual bool Check(){
		return CFXBlockController::Check();
	}
	void FillProperties(CPropertiesWnd* pWnd);
};

