/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

class uuid final
{
public:
	uuid();
	uuid(const uuid& other);
	~uuid() = default;

	bool operator== (const uuid& other) const;
	bool operator!= (const uuid& other) const;
	bool operator< (const uuid& other) const;

	std::string toString() const;

	static const uuid Invalid;

private:
	// hashed data
	long long m_value;
};