#pragma once

namespace ECS
{
	class TypeId
	{
	public:

		constexpr TypeId()
			: m_id(m_count++)
		{

		}

		inline constexpr unsigned int get() const
		{
			return m_id;
		}

	private:

		unsigned int m_id;
		static unsigned int m_count;
	};

	unsigned int TypeId::m_count = 0;
}