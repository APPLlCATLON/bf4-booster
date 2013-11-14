#ifndef __QUAT_H__
#define __QUAT_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include <Windows.h>

namespace fb
{
	class Quat
	{
	public:
		fb::Vec4 vec; //0x0000
	};

	class QuatTransform
	{
	public:
		fb::Vec4 transAndScale; //0x0000
		fb::Quat rotation; //0x0010
	};
};

#endif