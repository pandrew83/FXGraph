#pragma once
#include <cstring>

class CFXObjectDescriptor
{
public:
	int m_Id;
	CString m_Name;
	CString m_ClassName;
	bool m_IsGroup;
	int m_ParentId;
	int m_Version;
	CFXObjectDescriptor(int Id=0, CString ClassName=L"", CString Name=L"", int ParentId=0, bool IsGroup=false, int Version = 0) :
		m_Id(Id), m_ClassName(ClassName), m_Name(Name), m_ParentId(ParentId), m_IsGroup(IsGroup), m_Version(Version) {};
};

