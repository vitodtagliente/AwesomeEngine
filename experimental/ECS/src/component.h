#pragma once

namespace ECS
{
	class Component
	{
	public:

		using Id = size_t;

		Component()
			: m_id(id_counter++)
		{

		}
		virtual ~Component() = default;

		Id id() const { return m_id; }

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

	};

	Component::Id Component::id_counter = 0;
}