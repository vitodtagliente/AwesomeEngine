#pragma once

#include "base_element.h"

namespace Dreamkeeper
{
	namespace Core
	{
		struct BaseBuffer : public BaseElement
		{
			virtual void bind() = 0;
			virtual void unbind() = 0;
			virtual void free() = 0;
		};
	}
}