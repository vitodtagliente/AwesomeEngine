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

		DataComponent(const id_t t_id, const id_t t_entityId, const T& t_data)
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

		id_t id;
		id_t entityId;
		T data;
	};
}