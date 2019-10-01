#pragma once

#include "type_id.h"

namespace ECS
{
	template <typename T>
	struct DataComponent
	{
		DataComponent()
			: m_id()
			, data()
		{}

		DataComponent(const size_t t_id, const T& t_data)
			: id(t_id)
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
		T data;
	};
}