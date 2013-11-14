#ifndef __CTRREFBASE_H__
#define __CTRREFBASE_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

namespace fb
{
	template< class T > class CtrRefBase
	{
	public:
		T* m_ptr;
	};
};

#endif