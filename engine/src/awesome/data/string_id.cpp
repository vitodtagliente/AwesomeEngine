#include "string_id.h"

namespace awesome
{
	StringId::StringId()
		: m_hash()
		, m_data()
	{

	}

	StringId::StringId(const std::string& t_data)
		: m_hash()
		, m_data(t_data)
	{
		for (const auto& it : t_data)
		{
			// be sure to use prime numbers
			m_hash = 37 * m_hash + 17 * static_cast<char>(it);
		}
	}

	StringId::~StringId()
	{

	}

	StringId StringId::unique()
	{
		// #todo
		return StringId();
	}

	const StringId StringId::None = {};
}