#pragma once
class CFXBlockFunctional;
class CFXPin;
#include "FXPin.h"

class CFXDataCollectorItem {
public:
	CFXDataCollectorItem(int Ticks);
	CMap<int,int, variant_t,variant_t&> m_Values;
	int m_Ticks;
};

class CFXDataCollectorColumn {
public:
	CFXDataCollectorColumn(int id, CString name, CFXPinType type) {
		m_ID = id;
		m_Name = name;
		m_Type = type;
	}
	int m_ID;
	CString m_Name;
	CFXPinType m_Type;
};

class CFXDataCollector
{
public:
	CFXDataCollector();
	~CFXDataCollector();
	void Initialize();
	void Collect(int ticks, CFXBlockFunctional* pBlockFunc);
	CFXDataCollectorColumn* GetColumn(int id);

//	variant_t GetValue(int ticks, int id);
	void Excel(CString filename);
	void RemoveAll();
	POSITION GetFirstDataRow();
	CFXDataCollectorItem* GetNextDataRow(POSITION& pos);
protected:
	CList<CFXDataCollectorItem*,CFXDataCollectorItem*> m_DataRows;
	void CollectRecurse(CFXDataCollectorItem* pRow, CFXBlockFunctional* pBlockFunc);
	CMap<int, int, CFXDataCollectorColumn*, CFXDataCollectorColumn*> m_Columns;

};

