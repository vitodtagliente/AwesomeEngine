#include "uuid.h"

#include <chrono>

const uuid uuid::Invalid = {};

uuid::uuid()
	: m_value()
{
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	m_value = std::to_string(now.time_since_epoch().count());
}

uuid::uuid(const std::string& value)
	: m_value(value)
{
}

uuid::uuid(const uuid& other)
	: m_value(other.m_value)
{
}

bool uuid::operator==(const uuid& other) const
{
	return m_value == other.m_value;
}

bool uuid::operator!=(const uuid& other) const
{
	return m_value != other.m_value;
}

bool uuid::operator<(const uuid& other) const
{
	return m_value < other.m_value;
}
