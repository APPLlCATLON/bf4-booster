#ifndef __REFARRAY_H__
#define __REFARRAY_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include <Windows.h>

namespace fb
{
	template< class T > class RefArray
	{
	public:
		T* at( int idx )
		{
			if( !m_array )
				return NULL;

			return *( T** )( ( DWORD )m_array + ( idx * 4 ) );
		}

		T* operator [] ( int idx )
		{
			return at( idx );
		}

	private:
		T** m_array;
	};
};

#endif