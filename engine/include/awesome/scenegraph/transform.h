#pragma once

#include <vector>
#include "object.h"

namespace Awesome
{
	namespace Scenegraph
	{
		class Object;

		struct Transform
		{
			Object* parent{ nullptr };
			std::vector<Object*> children{ nullptr };


		};
	}
}