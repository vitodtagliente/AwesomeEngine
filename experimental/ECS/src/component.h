#pragma once

#include "entity.h"

namespace ECS
{
	class Component
	{
	public:

		using Id = size_t;

		Component()
			: m_id(++id_counter)
			, m_entityId()
		{

		}
		virtual ~Component() = default;

		Id id() const { return m_id; }

		Entity::Id getEntityId() const { return m_entityId; }

		inline virtual bool operator== (const Component& t_other) const
		{
			return m_id == t_other.m_id;
		}
		inline virtual bool operator!= (const Component& t_other) const
		{
			return m_id != t_other.m_id;
		}

	private:

		static Id id_counter;

		// component id
		Id m_id;
		// owner entity id
		Entity::Id m_entityId;

	};

	Component::Id Component::id_counter = 0;
}