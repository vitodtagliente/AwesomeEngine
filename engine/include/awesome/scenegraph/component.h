#pragma once 

namespace Awesome
{
	namespace Scenegraph
	{
		struct Component
		{
			virtual void init() = 0;
			virtual void update(float delta_time) = 0;
			virtual void draw() = 0;
		};
	}
}