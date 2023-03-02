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
struct Serializer
{
	static json::value serialize(const T& value) { return {}; }
	static bool deserialize(const json::value& data, T& value) { return false; }
};

template <>
struct Serializer<std::string>
{
	static json::value serialize(const std::string& value);
	static bool deserialize(const json::value& data, std::string& value);
};

template <>
struct Serializer<std::filesystem::path>
{
	static json::value serialize(const std::filesystem::path& value);
	static bool deserialize(const json::value& data, std::filesystem::path& value);
};

template <>
struct Serializer<uuid>
{
	static json::value serialize(const uuid& value);
	static bool deserialize(const json::value& data, uuid& value);
};

template <>
struct Serializer<math::vec2>
{
	static json::value serialize(const math::vec2& value);
	static bool deserialize(const json::value& data, math::vec2& value);
};

template <>
struct Serializer<math::vec3>
{
	static json::value serialize(const math::vec3& value);
	static bool deserialize(const json::value& data, math::vec3& value);
};

template <>
struct Serializer<math::vec4>
{
	static json::value serialize(const math::vec4& value);
	static bool deserialize(const json::value& data, math::vec4& value);
};

template <>
struct Serializer<math::transform>
{
	static json::value serialize(const math::transform& value);
	static bool deserialize(const json::value& data, math::transform& value);
};