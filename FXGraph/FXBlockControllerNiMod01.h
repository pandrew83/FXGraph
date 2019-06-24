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
	virtual bool Check(){
		return CFXBlockController::Check();
	}
};

