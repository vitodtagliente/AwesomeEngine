#pragma once 

#include <vector>
#include "object.h"

namespace Awesome
{
	namespace Scenegraph
	{
		class Scene
		{
		public:
			std::vector<Object*> objects;

		public:			
			template <class T>
			T* spawn(std::string name)
			{
				T* t_object = new T{};
				Object* new_object = dynamic_cast<Object*>(t_object);
				if (new_object != nullptr)
				{
					new_object->name = name;
					objects.push_back(new_object);
				}
				return new_object;
			}

			template <class T>
			Object* spawn(std::string name, Object* parent)
			{
				T* t_object = new T{};
				Object* new_object = dynamic_cast<Object*>(t_object);
				if (new_object != nullptr)
				{
					new_object->name = name;
					parent->transform.children.push_back(new_object);
					new_object->parent = parent;
				}
				return new_object;
			}
		};
	}
}