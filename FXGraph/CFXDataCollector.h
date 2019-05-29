#pragma once
class CFXBlockFunctional;
class CFXPin;

class CFXDataCollectorItem {
public:
	//CFXDataCollectorItem& operator=(CFXDataCollectorItem& item);
	CMap<int,int, variant_t,variant_t&> m_Values;
	int m_Ticks;
};

class CFXDataCollector
{
public:
	CFXDataCollector();
	~CFXDataCollector();
	void Initialize();
	void Collect(int ticks, CFXBlockFunctional* pBlockFunc);
//	variant_t GetValue(int ticks, int id);
	void Excel(CString filename);
	void RemoveAll();
protected:
	CList<CFXDataCollectorItem*,CFXDataCollectorItem*> m_DataRows;
	void CollectRecurse(CFXDataCollectorItem* pRow, CFXBlockFunctional* pBlockFunc);
	CMap<int, int, CFXPin*, CFXPin*> m_Columns;

};

