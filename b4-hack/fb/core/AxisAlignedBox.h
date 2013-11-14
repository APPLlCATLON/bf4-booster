#ifndef __AXISALIGNEDBOX_H__
#define __AXISALIGNEDBOX_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include <Windows.h>
#include "../core/Vec3.h"

namespace fb
{
	class AxisAlignedBox
    {
    public:
         __declspec( align( 16 ) )fb::Vec3 min;
         __declspec( align( 16 ) )fb::Vec3 max;
    };//Size=0x0020
};

#endif