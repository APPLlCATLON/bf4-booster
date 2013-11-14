#ifndef __VEC2_H__
#define __VEC2_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include <Windows.h>
#include <math.h>

namespace fb
{
	class Vec2
    {
    public:
        float x, y;

        Vec2()
		{
		}

        Vec2( float x, float y )
        {
            this->x = x;
            this->y = y;
        }

        Vec2& operator = ( Vec2 & From )
        {
            this->x = From.x;
            this->y = From.y;

            return ( *this );
        }

        float DistanceFrom( Vec2 to )
        {
            Vec2 Distance( to.x - this->x, to.y - this->y );

            return sqrt( ( Distance.x * Distance.x ) + ( Distance.y * Distance.y ) );
        }
    };//Size=0x0008
};

#endif