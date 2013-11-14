#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

namespace fb
{
	class Material
	{
	public:
		void* m_materialGridManager; //0x0000 fb::MaterialGridManager
		void* m_data; //0x0004 fb::MaterialData
		unsigned int m_index; //0x0008 
	
		__forceinline int IsPenetrable()
		{
			return m_index & 0x80000000;
		}

		__forceinline int IsSeeThrough()
		{
			return m_index & 0x20000000;
		} 
	
		__forceinline int IsClientDestructible()
		{
			return m_index & 0x40000000;
		}
	};//Size=0x003C
};

#endif