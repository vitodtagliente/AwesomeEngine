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
					addObject(new_object);
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
					addObject(new_object, parent);
				}
				return new_object;
			}

			void addObject(Object* new_object);
			void addObject(Object* new_object, Object* parent);

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
		};
	}
}