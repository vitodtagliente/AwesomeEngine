#pragma once

#include <string>
#include <vector>

#include "../math/math.h"
#include "component.h"

namespace Awesome
{
	namespace Scenegraph
	{
		class Object
		{
		private:
			static unsigned int id_counter;

			bool active{ true };		

		protected:
			std::vector<Component*> components;

			Object();
			Object(std::string object_name);
			~Object();

		public:

			struct Transform
			{
				Object* parent{ nullptr };
				std::vector<Object*> children{};

				glm::vec3 position{ 0.0f };
				glm::vec3 rotation{ 0.0f };
				glm::vec3 scale{ 1.0f };

				glm::vec3 up{ 0.0f, 1.0f, 0.0f };
				glm::vec3 right{ 1.0f, 0.0f, 0.0f };
				glm::vec3 forward{ 0.0f, 0.0f, -1.0f };

				glm::mat4 get() const;
			};

			unsigned int id{0};
			std::string name{};

			bool isStatic{ false };

			Transform transform;
			
			template <class T>
			T* addComponent()
			{
				T* t_component = new T{};
				Component* new_component = dynamic_cast<Component*>(t_component);
				if (new_component != nullptr)
					addComponent(new_component);
				return t_component;
			}

			Component* addComponent(Component* new_component);
						
			template <class T>
			T* findComponent()
			{
				for (auto it = components.begin(); it != components.end(); ++it)
				{
					T* current_component = dynamic_cast<T*>(*it);
					if (current_component != nullptr)
						return current_component;
				}
				return nullptr;
			}

			template <class T>
			std::vector<T*> findComponents()
			{
				std::vector<T*> found_components;
				for (auto it = components.begin(); it != components.end(); ++it)
				{
					T* current_component = dynamic_cast<T*>(*it);
					if (current_component != nullptr)
						found_components.push_back(current_component);
				}
				return found_components;
			}

			/*
			template <class T>
			Component* findComponentInChildren();
			template <class T>
			std::vector<Component*> findComponentsInChildren();
			*/

			template <class T>
			T* spawn(std::string name)
			{
				T* t_object = new T{};
				Object* new_object = dynamic_cast<Object*>(t_object);
				if (new_object != nullptr)
				{
					new_object->name = name;
					transform.children.push_back(new_object);
					new_object->transform.parent = this;
				}
				return t_object;
			}

			bool isActive() const { return active; }
			void setActive(bool active_value);

			Object* parent() const { return transform.parent; }
			std::vector<Object*>& const children() { return transform.children; }

			virtual void init();
			virtual void update(float delta_time);

			bool operator== (const Object& other);
		};
	}
}