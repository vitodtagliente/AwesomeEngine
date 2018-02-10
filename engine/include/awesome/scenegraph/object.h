#pragma once

#include <string>
#include <vector>
#include <initializer_list>

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
			Component* findComponent();
			template <class T>
			std::vector<Component*> findComponents();

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