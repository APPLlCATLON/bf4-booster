#ifndef __LINEARTRANSFORM_H__
#define __LINEARTRANSFORM_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

namespace fb
{
	class LinearTransform
    {
    public:
        Vec3 left;
        Vec3 up;
        Vec3 forward;
        Vec3 trans;
    };//Size=0x0040
};

#endif