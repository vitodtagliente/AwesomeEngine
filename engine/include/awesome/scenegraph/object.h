#pragma once

#include <string>
#include <vector>

#include "../math/math.h"
#include "component.h"

namespace Awesome
{
	namespace Scenegraph
	{
		/* Base engine object */
		class Object
		{
		private:
			static unsigned int id_counter;

			/* update method is called only if the object is active */
			bool active{ true };		

		protected:
			/* the list of components attached to the object */
			std::vector<Component*> components;

		public:
			Object();
			Object(std::string object_name);
			~Object();
			
			/* object transform info */
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
				glm::mat4 getHierarchy() const;
			} transform;

			unsigned int id{0};
			/* the object name */
			std::string name{};

			bool isStatic{ false };

			/* add a new component by class */
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
						
			/* find the first component of class */
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

			/* find all components of class */
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
			TODO:
			template <class T>
			Component* findComponentInChildren();
			template <class T>
			std::vector<Component*> findComponentsInChildren();
			*/

			/* spawn a new child object */
			template <class T>
			T* spawn(std::string name)
			{
				T* t_object = new T();
				Object* new_object = dynamic_cast<Object*>(t_object);
				if (dynamic_cast<Object*>(t_object) != nullptr)
				{
					new_object->name = name;
					addChild(new_object);
				}
				return t_object;
			}

			void addChild(Object* child);

			/* change and get the active state */
			bool isActive() const { return active; }
			void setActive(bool active_value);

			/* get transform const info data */
			Object* parent() const { return transform.parent; }
			std::vector<Object*>& const children() { return transform.children; }

			/* find a child object of class */
			template <class T>
			T* findObject()
			{
				for (auto it = children().begin(); it != children().end(); ++it)
				{
					T* current_object = dynamic_cast<T*>(*it);
					if (current_object != nullptr)
						return current_object;
					else
					{
						if (current_object->children().size() > 0)
						{
							T* result = current_object->findObject<T>();
							if (result != nullptr)
								return result;
						}							
					}
				}
				return nullptr;
			}

			/* find all the children objects of class */
			template <class T>
			std::vector<T*> findObjects()
			{
				std::vector<T*> found_objects;
				for (auto it = children().begin(); it != children().end(); ++it)
				{
					T* current_object = dynamic_cast<T*>(*it);
					if (current_object != nullptr)
						found_objects.push_back(current_object);
					else
					{
						if (current_object->children().size() > 0)
							found_objects.push_back(current_object->findObjects<T>());
					}
				}
				return found_objects;
			}

			/* init the object */
			virtual void init();
			/* update only if the object is active */
			virtual void update(float delta_time);

			bool operator== (const Object& other);
		};
	}
}