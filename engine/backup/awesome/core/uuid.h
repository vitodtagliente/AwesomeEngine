/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

class uuid final
{
public:
	uuid();
	uuid(const std::string& value);
	uuid(const uuid& other);
	~uuid() = default;

	bool operator== (const uuid& other) const;
	bool operator!= (const uuid& other) const;
	bool operator< (const uuid& other) const;

	operator std::string() const { return m_value; }

	static const uuid Invalid;

private:
	std::string m_value;
};