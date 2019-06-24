#pragma once
#include "fxblockextension.h"
class CFXBlockExtensionA01 :
	public CFXBlockExtension
{
public:
	DECLARE_SERIAL(CFXBlockExtensionA01);
	CFXBlockExtensionA01(void);
	~CFXBlockExtensionA01(void);
	void Create(CFXObject* pObject);
	int GetClassID() {
		return BLOCK_EXTENSION_NIMODA01;
	}
	CString GetClassDescriptor() {
		return _T("CFXBlockExtensionA01");
	}
};

