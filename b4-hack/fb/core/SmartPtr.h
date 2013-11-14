#ifndef __SMARTPTR_H__
#define __SMARTPTR_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

namespace fb
{
	template< class T > class SmartPtr
	{
	public:
		T* m_ptr;
	};
};

#endif