#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include <Windows.h>

namespace fb
{
	template< class T > class Array
	{
	public:
		T at( int idx )
		{
			if( !m_firstElement )
				return NULL;

			return *( T* )( ( DWORD )m_firstElement + ( idx * sizeof( T ) ) );
		}

		T operator [] ( int idx )
		{
			return at( index );
		}

	private:
		T* m_firstElement;
	};
};

#endif