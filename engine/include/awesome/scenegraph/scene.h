#pragma once 

#include "object.h"

namespace Awesome
{
	namespace Scenegraph
	{
		class Scene : public Object
		{
		public:			

			Scene(std::string scene_name) : Object(scene_name) {};
			
			/* 
				TODO: add IO operations 
				- load from file
				- save to file
			*/

			/* release all the scene memory */
			void unload();
		};
	}
}