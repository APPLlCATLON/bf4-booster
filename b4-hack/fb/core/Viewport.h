#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

namespace fb
{
	class Viewport
	{
	public:
		unsigned int x;
		unsigned int y;
		unsigned int width;
		unsigned int height;
		float minZ;
		float maxZ;
	};
};

#endif