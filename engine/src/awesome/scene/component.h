#pragma once

#include "../data/string_id.h"

namespace awesome
{
	class Component
	{
	public:

		Component();
		virtual ~Component();

		// id
		inline unsigned int getId() const { return m_id; }

		// name
		inline const StringId& getName() const { return m_name; }
		inline void setName(const StringId& t_name) { m_name = t_name; }

	protected:

		// component id
		unsigned int m_id;
		// component name
		StringId m_name;
	};
}