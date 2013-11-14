#ifndef __TUPLE2_H__
#define __TUPLE2_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

namespace fb
{
	template <class T> class Tuple2
	{
	public:
		Tuple2( T e1, T e2 ) : _e1( e1 ), _e2( e2 )
		{
		}

	public:
		T _e1;
		T _e2;
	};
};

#endif