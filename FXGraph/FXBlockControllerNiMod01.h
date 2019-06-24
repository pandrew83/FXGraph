#pragma once
#include "fxblockcontroller.h"
//#include <stdint.h>

class CFXBlockControllerNiMod01 :
	public CFXBlockController
{
public:
	DECLARE_SERIAL(CFXBlockControllerNiMod01);
	CFXBlockControllerNiMod01(void);
	void Create(CFXObject* pObject);
	~CFXBlockControllerNiMod01(void);
	int GetClassID(){
		return BLOCK_CONTROLLER_NIMOD01;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockControllerNiMod01");
	}
	virtual bool Check(){
		return CFXBlockController::Check();
	}
};

