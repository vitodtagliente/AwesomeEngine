#include "string_id.h"

const string_id string_id::Invalid = {};

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

bool string_id::operator==(const string_id& other) const
{
	return m_hash == other.m_hash;
}

bool string_id::operator!=(const string_id& other) const
{
	return m_hash != other.m_hash;
}