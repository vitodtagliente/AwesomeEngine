#pragma once

#include <cassert>
#include <initializer_list>
#include <string>
#include <vector>

namespace Awesome
{
	namespace Scenegraph
	{
		class Component;

		class Object
		{
		private:
			static unsigned int id_counter;

		protected:
			std::vector<Component*> components;

		public:

			struct Transform
			{
				Object* parent{ nullptr };
				std::vector<Object*> children{ nullptr };
			};

			unsigned int id{0};
			std::string name{};

			Transform transform;

			Object();
			Object(std::string object_name);
			Object(std::initializer_list<Component*> init_components);
			Object(std::string object_name, std::initializer_list<Component*> init_components);
			
			template <class T>
			T* addComponent(T* new_component)
			{
				assert(dynamic_cast<const Component*>(new_component) != nullptr);
				components.push_back(new_component);
				return new_component;
			}
						
			template <class T>
			Component* findComponent()
			{
				for (auto it = myvector.begin(); it != components.end(); ++it)
				{
					if (dynamic_cast<const Component*>(*it) != nullptr)
						return *it;
				}
				return nullptr;
			}

			template <class T>
			std::vector<Component*> findComponents()
			{
				std::vector<Component*> found_components;
				for (auto it = myvector.begin(); it != components.end(); ++it)
				{
					if (dynamic_cast<const Component*>(*it) != nullptr)
						found_components.push_back(*it);
				}
				return found_components;
			}

			/*
			template <class T>
			Component* findComponentInChildren();
			template <class T>
			std::vector<Component*> findComponentsInChildren();
			*/

			virtual void init();
			virtual void update(float delta_time);

			bool operator== (const Object& other);
		};
	}
}