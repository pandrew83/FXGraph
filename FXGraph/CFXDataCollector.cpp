#include "stdafx.h"
#include "CFXDataCollector.h"
#include "FXBlock.h"
#include "FXBlockFunctional.h"
#include "FXPin.h"
#include "libxl.h"

using namespace libxl;

CFXDataCollector::CFXDataCollector()
{
}
//
//CFXDataCollectorItem& CFXDataCollectorItem::operator=(CFXDataCollectorItem& item)
//{
//	m_Values = item.m_Values;
//	return *this;
//}

CFXDataCollector::~CFXDataCollector()
{
	RemoveAll();
}

void CFXDataCollector::Initialize()
{
	RemoveAll();
}

void CFXDataCollector::Collect(int ticks, CFXBlockFunctional* pBlockFunc)
{
	CFXDataCollectorItem* pRow = new CFXDataCollectorItem();
	pRow->m_Ticks = ticks;
	CollectRecurse(pRow, pBlockFunc);
	m_DataRows.AddTail(pRow);
}

//variant_t CFXDataCollector::GetValue(int ticks, int id)
//{
//	return m_DataRows[ticks]->m_Values[id];
//}

void CFXDataCollector::Excel(CString filename)
{
	Book* book = xlCreateBook();
	if (book) {
		Sheet* sheet = book->addSheet(L"Data");
		if (sheet) {
			int line = 1;
			int col = 1;
			sheet->writeStr(line, 0, L"Tick");
			POSITION pos = m_Columns.GetStartPosition();
			while (pos) {
				CFXPin* pPin;
				int id;
				m_Columns.GetNextAssoc(pos, id, pPin);
				sheet->writeNum(line, col, id);
				sheet->writeStr(line + 1, col, pPin->GetName());
				col++;
			}
			line+=2;
			pos = m_DataRows.GetHeadPosition();
			while (pos) {
				CFXDataCollectorItem* pRow = m_DataRows.GetNext(pos);
				sheet->writeNum(line, 0, pRow->m_Ticks);
				int col = 1;
				POSITION pos1 = m_Columns.GetStartPosition();
				while (pos1) {
					int id;
					CFXPin* pPin;
					m_Columns.GetNextAssoc(pos1, id, pPin);
					switch (pPin->m_Type) {
					case Logical:
						sheet->writeBool(line, col++, pRow->m_Values[id]);
						break;
					default:
						sheet->writeNum(line, col++, pRow->m_Values[id]);
					}
					
				}
				line++;
			}
			if (book->save(filename)) {
				::ShellExecute(NULL, L"open", filename, NULL, NULL, SW_SHOW);
			}
		}
	}
}

void CFXDataCollector::RemoveAll()
{
	POSITION pos = m_DataRows.GetHeadPosition();
	while (pos) {
		CFXDataCollectorItem* pCur = m_DataRows.GetNext(pos);
		delete pCur;
	}
	m_DataRows.RemoveAll();
}

void CFXDataCollector::CollectRecurse(CFXDataCollectorItem* pRow, CFXBlockFunctional* pCur)
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
			pRow->m_Values[pPin->m_ID] = pPin->GetValue();
		}
		pos1 = pBlock->m_OutputPins.GetHeadPosition();
		while (pos1) {
			CFXPin* pPin = pBlock->m_OutputPins.GetNext(pos1);
			pRow->m_Values[pPin->m_ID] = pPin->GetValue();
		}
		if (pBlockFunc) {
			CollectRecurse(pRow, pBlockFunc);
		}

	}
}
