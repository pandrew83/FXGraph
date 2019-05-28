#include "stdafx.h"
#include "CFXDataCollector.h"
#include "FXBlock.h"
#include "FXBlockFunctional.h"
#include "FXPin.h"

CFXDataCollector::CFXDataCollector()
{
}

CFXDataCollector::~CFXDataCollector()
{
}

void CFXDataCollector::Initialize()
{
	m_DataRows.RemoveAll();
}

void CFXDataCollector::Collect(int ticks, CFXBlockFunctional* pBlockFunc)
{
	CollectRecurse(ticks, pBlockFunc);
}

variant_t CFXDataCollector::GetValue(int ticks, int id)
{
	return m_DataRows[ticks].m_Values[id];
}

void CFXDataCollector::CollectRecurse(int ticks, CFXBlockFunctional* pCur)
{
	POSITION pos = pCur->m_Blocks.GetHeadPosition();
	while (pos) {
		CFXBlock* pBlock = pCur->m_Blocks.GetNext(pos);
		CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(pBlock);
		POSITION pos1;
		pos1 = pBlock->m_InputPins.GetHeadPosition();
		while (pos1) {
			CFXPin* pPin = pBlock->m_InputPins.GetNext(pos1);
			if (!m_Columns[pPin->m_ID]) {
				m_Columns[pPin->m_ID] = pPin;
			}
			m_DataRows[ticks].m_Values[pPin->m_ID] = pPin->GetValue();
		}
		pos1 = pBlock->m_OutputPins.GetHeadPosition();
		while (pos1) {
			CFXPin* pPin = pBlock->m_OutputPins.GetNext(pos1);
			m_DataRows[ticks].m_Values[pPin->m_ID] = pPin->GetValue();
		}
		if (pBlockFunc) {
			CollectRecurse(ticks, pBlockFunc);
		}

	}
}
