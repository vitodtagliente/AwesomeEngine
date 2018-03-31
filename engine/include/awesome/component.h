#pragma once 

#include <string>
#include "object.h"

namespace Awesome
{
	class Component
	{
	private:
		Object* owner_object{ nullptr };

	protected:
		Component();
		~Component();

	public:
		std::string name{};
		UniqueId id;
		
		// return the owner object 
		Object* owner() { return owner_object; }

		// engine events
		virtual void init();
		virtual void update(float delta_time);
		virtual void free();

		bool operator== (const Component& other);

		template<class T>
		static T* add(Object* current_owner)
		{
			T* t_component = new T{};
			Component* new_component = dynamic_cast<Component*>(t_component);
			if (new_component != nullptr)
			{
				new_component->owner_object = current_owner;
			}
			return t_component;
		}
	};
}