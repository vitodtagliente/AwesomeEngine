#pragma once 

#include "object.h"

namespace Awesome
{
	class Component
	{
		friend class Object;

	private:
		Object* owner_object{ nullptr };

		Component();
		
	protected:
		virtual ~Component();

	public:
		UniqueId id;

		// return the owner object 
		Object* owner() { return owner_object; }

		// engine events
		virtual void init() = 0;
		virtual void update(float delta_time) = 0;

		bool operator== (const Component& other);
	};
}