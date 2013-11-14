#ifndef __VEC3_H__
#define __VEC3_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include <Windows.h>
#include <math.h>

namespace fb
{
	class Vec3
    {
    public:
        float x, y, z, pad;

        Vec3(){}

        Vec3( float x, float y, float z )
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Vec3 & operator = ( Vec3 & From )
        {
            this->x = From.x;
            this->y = From.y;
            this->z = From.z;

            return (*this);
        }

        float Dot( Vec3 Vec )
        {
            return this->x * Vec.x + this->y * Vec.y + this->z * Vec.z;
        }

		float DistanceFrom2( Vec3 p )
		{
			float xD = p.x - x;
			float yD = p.y - y;
			float zD = p.z - z;

			float dist = sqrt( xD * xD + yD * yD + zD * zD );

			return dist;
		}

		float DistanceFrom( Vec3 & point )
		{
			float x2 = ( point.x - x ) * ( point.x - x );
			float y2 = ( point.y - y ) * ( point.y - y );
			float z2 = ( point.z - z ) * ( point.z - z );

			float dist = sqrt( x2 + y2 + z2 );

			return dist;
		}

		float Length()
		{
			float flLengthX, flLengthY, flLengthZ, flLength;

			flLengthX = x * x;
			flLengthY = y * y;
			flLengthZ = z * z;

			flLength = sqrt( flLengthX + flLengthY + flLengthZ );

			return fabs( flLength );
		}

		float Length2D()
		{
			float flLengthX, flLengthY, flLength;

			flLengthX = x * x;
			flLengthY = y * y;

			flLength = sqrt( flLengthX + flLengthY );

			return flLength;
		}

		double DotProductEx( Vec3 vec )
		{
			double temp = 0;

			temp = this->x*vec.x+ this->y*vec.y+ this->z*vec.z;

			return temp;
		}

		void Normalize( )
		{
			float length, ilength;

			length = this->Length();

			if( length )
			{
				ilength = 1 / length;

				this->x *= ilength;
				this->y *= ilength;
				this->z *= ilength;
			}
		}

		fb::Vec3& operator + ( const fb::Vec3& v ) const
		{
			return fb::Vec3( x + v.x, y + v.y, z + v.z );
		}

		fb::Vec3& operator / ( const float& div ) const
		{
			return fb::Vec3( x / div, y / div, z / div );
		}

		fb::Vec3& operator - ( const fb::Vec3& v ) const
		{
			return fb::Vec3( x - v.x, y - v.y, z - v.z );
		}

		fb::Vec3& operator * ( const float& mul ) const
		{
			return fb::Vec3( x * mul, y * mul, z * mul );
		}
    };//Size=0x0010
};

#endif