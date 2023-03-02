/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/entity.h>

#include "serialization.h"

template <>
struct Serializer<Entity>
{
	static json::value serialize(const Entity& value);
	static bool deserialize(const json::value& data, Entity& value);
};

template <>
struct Serializer<std::vector<Entity>>
{
	static json::value serialize(const std::vector<Entity>& value);
	static bool deserialize(const json::value& data, std::vector<Entity>& value);
};

template <>
struct Serializer<std::vector<std::unique_ptr<Entity>>>
{
	static json::value serialize(const std::vector<std::unique_ptr<Entity>>& value);
	static bool deserialize(const json::value& data, std::vector<std::unique_ptr<Entity>>& value);
};