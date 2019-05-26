#include "StdAfx.h"
#include "FXBlockExtension.h"

IMPLEMENT_SERIAL(CFXBlockExtension,CFXBlock,1);

CFXBlockExtension::CFXBlockExtension(void)
{
}


CFXBlockExtension::~CFXBlockExtension(void)
{
}


CFXPin* CFXBlockExtension::AddInputPin(CFXPinType type, CString funcName)
{
	return CFXBlock::AddInputPin(type,funcName,false,false,true);
}


CFXPin* CFXBlockExtension::AddOutputPin(CFXPinType type, CString funcName)
{
	return CFXBlock::AddOutputPin(type,funcName,false,false,true);
}
