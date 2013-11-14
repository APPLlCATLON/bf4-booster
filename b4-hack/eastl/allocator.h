#ifndef __EASTL_ALLOCATOR_H__
#define __EASTL_ALLOCATOR_H__

#include <Windows.h>
#include "eastl_classes.h"

namespace eastl
{
	class allocator
    {
    public:
        __forceinline allocator()
		{
		}

        __forceinline allocator( eastl::allocator *__formal )
		{
		}

        __forceinline void set_name( const char *__formal )
		{
		}

        __forceinline const char* get_name()
		{
			return "EASTL";
		}

        __forceinline void* allocate( unsigned int n, int flags )
		{
			return malloc( n );
		}

        __forceinline void deallocate( void *p, unsigned int __formal )
		{
			free( p );
		}
    };
};

#endif