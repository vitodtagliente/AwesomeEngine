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
			template <class T>
			T* findObject()
			{
				for (auto it = objects.begin(); it != objects.end(); ++it)
				{
					T* current_object = dynamic_cast<T*>(*it);
					if (current_object != nullptr)
						return current_object;
				}
			}

			template <class T>
			std::vector<T*> findObjects()
			{
				std::vector<T*> found_objects;
				for (auto it = objects.begin(); it != objects.end(); ++it)
				{
					T* current_object = dynamic_cast<T*>(*it);
					if (current_object != nullptr)
					{
						found_objects.push_back(current_object);
						// TODO
					}
				}
				return found_objects;
			}
			*/

			void unload();
		};
	}
}