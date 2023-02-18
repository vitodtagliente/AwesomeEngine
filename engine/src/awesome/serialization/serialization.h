/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>

#include <awesome/core/uuid.h>
#include <awesome/encoding/json.h>
#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>

template <typename T>
json::value serialize(const T& data) 
{
	return json::value();
}

template <> 
json::value serialize(const std::string& primitive)
{
	return json::value(primitive);
}

template <> 
json::value serialize(const std::filesystem::path& path)
{
	return json::value(path.string());
}

template <> 
json::value serialize(const uuid& id)
{
	return json::value(static_cast<std::string>(id));
}

template<>
json::value serialize(const math::vec2& v)
{
	return json::object({
		{"x", v.x},
		{"y", v.y}
		});
}

template<>
json::value serialize(const math::vec3& v)
{
	return json::object({
		{"x", v.x},
		{"y", v.y},
		{"z", v.z}
		});
}

template<>
json::value serialize(const math::vec4& v)
{
	return json::object({
		{"x", v.x},
		{"y", v.y},
		{"z", v.z},
		{"w", v.w}
		});
}

template<>
json::value serialize(const math::transform& t)
{
	return json::object({
		{"position", serialize(t.position)},
		{"rotation", serialize(t.rotation)},
		{"scale", serialize(t.scale)},
		{"isStatic", t.isStatic}
		});
}

template <typename T>
bool deserialize(const json::value& value, T& data)
{
	return false;
}