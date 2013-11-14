#ifndef __MAT4_H__
#define __MAT4_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include "../core/Vec4.h"

namespace fb
{
	class Mat4
    {
    public:
        Vec4 m_rows[4];

        Mat4()
		{
		}

        Mat4& operator = ( Mat4& From )
        {
            this->m_rows[0] = From.m_rows[0];
            this->m_rows[1] = From.m_rows[1];
            this->m_rows[2] = From.m_rows[2];
            this->m_rows[3] = From.m_rows[3];

            return ( *this );
        }

		Vec4& operator [] ( int idx )
		{
			if( idx < 0 || idx > 3 )
				return fb::Vec4();

			return m_rows[ idx ];
		}

        Vec4 one()
		{
			return m_rows[0];
		}

        Vec4 two()
		{
			return m_rows[1];
		}

        Vec4 three()
		{
			return m_rows[2];
		}

        Vec4 four()
		{
			return m_rows[3];
		}
    };//Size=0x0040
};

#endif