#include "string_id.h"

namespace awesome
{
	string_id::string_id()
		: m_hash()
		, m_data()
	{

	}

	string_id::string_id(const std::string& data)
		: m_hash()
		, m_data(data)
	{
		for (const auto& it : data)
		{
			// be sure to use prime numbers
			m_hash = 37 * m_hash + 17 * static_cast<char>(it);
		}
	}

	string_id::~string_id()
	{

	}

	string_id string_id::unique()
	{
		// #todo
		return string_id();
	}

	const string_id string_id::Invalid = {};
}