#ifndef __VEC4_H__
#define __VEC4_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include <Windows.h>
#include <math.h>

namespace fb
{
	class Vec4
    {
    public:
        float                    x, y, z, w;

        Vec4()
		{
		}

        Vec4( float x, float y, float z, float w )
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        Vec4 & operator = ( Vec4 & From )
        {
            this->x = From.x;
            this->y = From.y;
            this->z = From.z;
            this->w = From.w;

            return (*this);
        }

		float operator [] ( int idx )
		{
			if( idx < 0 || idx > 3 )
				return 0.0f;

			if( idx == 0 )
				return x;
			else if( idx == 1 )
				return y;
			else if( idx == 2 )
				return z;
			else if( idx == 3 )
				return w;

			return 0.0f;
		}

        float Dot( Vec4 Vec )
        {
            return this->x * Vec.x + this->y * Vec.y + this->z * Vec.z + this->w * Vec.w;
        }

		float Dott( Vec3 Vec )
		{
			return this->x * Vec.x + this->y * Vec.y + this->z * Vec.z;
		}

        float DistanceFrom( Vec4 Vec )
        {
            Vec4 Distance(
                Vec.x - this->x,
                Vec.y - this->y,
                Vec.z - this->z,
                Vec.w - this->w );

            return sqrt( ( Distance.x * Distance.x ) + ( Distance.y * Distance.y ) + ( Distance.z * Distance.z ) + ( Distance.w * Distance.w ) );
        }
    };//Size=0x0010
};

#endif