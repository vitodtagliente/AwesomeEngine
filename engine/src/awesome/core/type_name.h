/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/core/reflection.h>

template <typename T = Type>
struct TypeName
{
	operator std::string() const { return value; }

	std::string value;
};