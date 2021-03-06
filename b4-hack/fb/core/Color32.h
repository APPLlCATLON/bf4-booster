#ifndef __COLOR32_H__
#define __COLOR32_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

namespace fb
{
	class Color32
	{
	public:
		Color32( unsigned long color )
		{
			this->color = color;
		}

		Color32( unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha ) :
			r( red ), g( green ), b( blue ), a( alpha )
		{
		}

		static Color32 White()
		{
			return Color32( 255, 255, 255, 255 );
		}

		static Color32 Black()
		{
			return Color32( 0, 0, 0, 255 );
		}

		static Color32 Red()
		{
			return Color32( 255, 0, 0, 255 );
		}

		static Color32 Green()
		{
			return Color32( 0, 255, 0, 255 );
		}

		static Color32 Blue()
		{
			return Color32( 0, 0, 255, 255 );
		}

	public:
		union
		{
			struct
			{
				unsigned char r;
				unsigned char g;
				unsigned char b;
				unsigned char a;
			};

			unsigned long color;
		};
	};
};

#endif