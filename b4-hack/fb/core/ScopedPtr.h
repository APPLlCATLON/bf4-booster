#ifndef __SCOPEDPTR_H__
#define __SCOPEDPTR_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

namespace fb
{
	template< typename T > class ScopedPtr
	{
	public:
		T* m_ptr; //0x0000
	};
};

#endif