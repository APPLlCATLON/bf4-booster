#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include "LinearTransform.h"
#include "Plane.h"

namespace fb
{
	class Frustum
    {
    public:
        fb::LinearTransform m_transform;
        fb::AxisAlignedBox m_boundingBox;
        Vec3 m_corners[8];
        Vec3 m_center;
        fb::Plane m_planes[6];
        unsigned char m_planeSignBits[24];
        float m_radius;
        float m_radiusSqr;
        bool m_rightHanded;
        unsigned char _padding[15];
    };//Size=0x0180
};

#endif