#pragma once

#include "entity.h"

namespace ECS
{
	class DataComponent
	{
	public:

		using Id = size_t;

		DataComponent()
			: m_id()
			, m_entityId()
		{

		}
		virtual ~DataComponent() = default;

		inline virtual bool operator== (const DataComponent& t_other) const 
		{ 
			return m_id == t_other.m_id
				&& m_entityId == t_other.m_entityId;
		}
		inline virtual bool operator!= (const DataComponent& t_other) const
		{
			return m_id != t_other.m_id
				|| m_entityId != t_other.m_entityId;
		}

	private:

		// component id
		Id m_id;
		// owner entity id
		Entity::Id m_entityId;

	};
}