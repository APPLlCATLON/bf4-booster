#ifndef __TYPEINFO_H__
#define __TYPEINFO_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

namespace fb
{
	class MemberInfo
	{
	public:
		class MemberInfoData
		{
		public:
			const char* name; //0x0000
			int flags; //0x0004
		};

	public:
		const void* m_infoData; //0x0000
	};

	class TypeInfo
	{
	public:
		TypeInfoData* m_infoData; //0x0000 
		TypeInfo* m_pNext; //0x0004 
	char _0x0008[4];

	};//Size=0x000C

	class TypeInfoData
	{
	public:
		char* name; //0x0000 
	char _0x0004[60];

	};//Size=0x0040
};

#endif