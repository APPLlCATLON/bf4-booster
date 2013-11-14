#ifndef __SMARTREF_H__
#define __SMARTREF_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

namespace fb
{
	template< class T > class SmartRef
	{
	public:
		T* m_ptr;
	};
};

#endif