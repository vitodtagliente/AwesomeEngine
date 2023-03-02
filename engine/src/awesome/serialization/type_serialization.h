/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

#include "serialization.h"

template <>
struct Serializer<IType>
{
	static json::value serialize(const IType& value);
	static bool deserialize(const json::value& data, IType& value);
};

template <>
struct Serializer<std::vector<IType>>
{
	static json::value serialize(const std::vector<IType>& value);
	static bool deserialize(const json::value& data, std::vector<IType>& value);
};

template <>
struct Serializer<std::vector<std::unique_ptr<IType>>>
{
	static json::value serialize(const std::vector<std::unique_ptr<IType>>& value);
	static bool deserialize(const json::value& data, std::vector<std::unique_ptr<IType>>& value);
};