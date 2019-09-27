#pragma once

#include "type_id.h"

namespace ECS
{
	template <typename T>
	struct DataComponent
	{
		DataComponent()
			: m_id()
			, entityId()
			, data()
		{}

		DataComponent(const size_t t_id, const size_t t_entityId, const T& t_data)
			: id(t_id)
			, entityId(t_entityId)
			, data(t_data)
		{}

		bool operator== (const DataComponent<T>& t_other) const
		{
			return id == t_other.id;
		}
		bool operator!= (const DataComponent<T>& t_other) const
		{
			return id != t_other.id;
		}

		size_t id;
		size_t entityId;
		T data;
	};
}