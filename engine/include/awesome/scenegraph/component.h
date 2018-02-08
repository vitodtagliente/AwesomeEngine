#pragma once 

namespace Awesome
{
	namespace Scenegraph
	{
		struct Component
		{
			unsigned int id{ 0 };
			
			virtual void init() = 0;
			virtual void update(float delta_time) = 0;
		};
	}
}