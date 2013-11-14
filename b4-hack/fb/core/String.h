#ifndef __STRING_H__
#define __STRING_H__

#include "../../fb2_classes.h"
#include "../../fb2_offsets.h"

#include <Windows.h>

namespace fb
{
	class String
	{
	public:
		String( char* chars ) : m_chars( chars )
		{
		}

		char* getString()
		{
			return m_chars;
		}

	private:
		char* m_chars;
	};
};

#endif