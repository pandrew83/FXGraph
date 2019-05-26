#include "StdAfx.h"
#include "FXBlockController.h"
#include "FXBlockFunctional.h"

IMPLEMENT_SERIAL(CFXBlockController,CFXBlock,1)

CFXBlockController::CFXBlockController(void)
{
}

CFXBlockController::CFXBlockController(CFXBlock* pBlock):CFXBlockFunctional(pBlock){
	m_Ticks = 0;
}

CFXBlockController::~CFXBlockController(void)
{
}
