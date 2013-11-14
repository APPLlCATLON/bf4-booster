#ifndef __RELOCARRAY_H__
#define __RELOCARRAY_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include <Windows.h>

namespace fb
{
	template< class T > class RelocArray
	{
	public:
		unsigned int size()
		{
			return m_count;
		}

		T at( int idx )
		{
			return *( T* )( ( DWORD )m_data + ( idx * sizeof( T ) ) );
		}

		T operator [] ( int idx )
		{
			return at( idx );
		}

	private:
		unsigned int m_count;
		T* m_data;
	};
};

#endif