#pragma once 

#include <vector>

namespace Awesome
{
	namespace Scenegraph
	{
		class Object;

		class Scene
		{
		protected:
			std::vector<Object*> objects;
		};
	}
}