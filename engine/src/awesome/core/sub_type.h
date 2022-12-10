/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <type_traits>

#include <awesome/core/reflection.h>

template <typename T = Type>
struct SubType : public std::unique_ptr<T>
{
	std::string type;
};