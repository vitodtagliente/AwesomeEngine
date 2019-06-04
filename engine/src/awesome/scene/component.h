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
		inline const StringId& getId() const { return m_id; }

		// component name
		StringId name;

	protected:

		// component id
		StringId m_id;
	};
}