#include "uuid.h"

#include <chrono>

const uuid uuid::Invalid = { "" };

uuid::uuid()
	: value()
{
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	value = std::to_string(now.time_since_epoch().count());
}

uuid::uuid(const std::string& value)
	: value(value)
{
}

uuid::uuid(const uuid& other)
	: value(other.value)
{
}

uuid& uuid::operator=(const uuid& other)
{
	value = other.value;
	return *this;
}

bool uuid::operator==(const uuid& other) const
{
	return value == other.value;
}

bool uuid::operator!=(const uuid& other) const
{
	return value != other.value;
}

bool uuid::operator<(const uuid& other) const
{
	return value < other.value;
}
