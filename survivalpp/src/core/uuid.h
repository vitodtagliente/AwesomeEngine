/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

struct uuid final
{
	uuid();
	uuid(const std::string& value);
	uuid(const uuid& other);
	~uuid() = default;

	uuid& operator= (const uuid& other);
	bool operator== (const uuid& other) const;
	bool operator!= (const uuid& other) const;
	bool operator< (const uuid& other) const;

	static const uuid Invalid;
	std::string value;
};