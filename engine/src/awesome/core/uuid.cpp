#include "uuid.h"

#include <chrono>

const uuid uuid::Invalid = {};

uuid::uuid()
	: m_value()
{
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	m_value = now.time_since_epoch().count();
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

std::string uuid::toString() const
{
	return std::to_string(m_value);
}
