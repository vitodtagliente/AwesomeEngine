#pragma once

#include "../data/string_id.h"

namespace awesome
{
	class Component
	{
		friend class Object;

	public:

		Component();
		virtual ~Component();

		virtual void init() {}
		virtual void update(const double t_deltaTime) {}
		virtual void uninit() {}

		// get the id
		inline const StringId& getId() const { return m_id; }
		// get the owner object
		inline Object* const getOwner() const { return m_owner; }

		// component name
		StringId name;

	protected:

		// component id
		StringId m_id;
		// owner object
		Object* m_owner;
	};
}