#pragma once
class CFXBlockFunctional;
class CFXPin;

class CFXDataCollectorItem {
public:
	CMap<int,int, variant_t,variant_t&> m_Values;
};

class CFXDataCollector
{
public:
	CFXDataCollector();
	~CFXDataCollector();
	void Initialize();
	void Collect(int ticks, CFXBlockFunctional* pBlockFunc);
	variant_t GetValue(int ticks, int id);
protected:
	CMap<int, int,CFXDataCollectorItem,CFXDataCollectorItem&> m_DataRows;
	void CollectRecurse(int ticks, CFXBlockFunctional* pBlockFunc);
	CMap<int, int, CFXPin*, CFXPin*> m_Columns;

};

