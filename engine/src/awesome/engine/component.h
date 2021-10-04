#pragma once

#include <awesome/core/string_id.h>

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
		inline const string_id& getId() const { return m_id; }
		// get the owner object
		inline Object* const getOwner() const { return m_owner; }

		// component name
		string_id name;
		// if true the component is enabled
		bool enabled;

	

		Component();
		virtual ~Component();

	private:

		template <typename T = Component>
		static T * const create(Object * t_object)
		{
			if (t_object != nullptr)
			{
				// T* const created_component = new T{};
				// created_component->m_id = StringId::unique();
				// created_component->m_owner = t_object;
				// return created_component;
			}
			return nullptr;
		}

		// component id
		string_id m_id;
		// owner object
		Object* m_owner;
	};
}