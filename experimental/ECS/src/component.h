#pragma once

#include "entity.h"

namespace ECS
{
	class Component
	{
	public:

		Component()
			: m_id(++id_counter)
			, m_entityId()
		{

		}
		virtual ~Component() = default;

		size_t id() const { return m_id; }

		size_t getEntityId() const { return m_entityId; }

		inline virtual bool operator== (const Component& t_other) const
		{
			return m_id == t_other.m_id;
		}
		inline virtual bool operator!= (const Component& t_other) const
		{
			return m_id != t_other.m_id;
		}

	private:

		static size_t id_counter;

		// component id
		size_t m_id;
		// owner entity id
		size_t m_entityId;

	};

	size_t Component::id_counter = 0;
}