#pragma once

#include <awesome/data/string_id.h>

namespace awesome
{
	class Component
	{
		friend class Object;

	public:

		virtual void init() {}
		virtual void update(const double t_deltaTime) {}
		virtual void uninit() {}

		// get the id
		inline const StringId& getId() const { return m_id; }
		// get the owner object
		inline Object* const getOwner() const { return m_owner; }

		// component name
		StringId name;
		// if true the component is enabled
		bool enabled;

	protected:

		Component();
		virtual ~Component();

	private:

		template <typename T = Component>
		static T * const create(Object * t_object)
		{
			if (t_object != nullptr)
			{
				T* const created_component = new T{};
				created_component->m_id = StringId::unique();
				created_component->m_owner = t_object;
				return created_component;
			}
			return nullptr;
		}

		// component id
		StringId m_id;
		// owner object
		Object* m_owner;
	};
}