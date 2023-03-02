#include "serialization.h"

json::value Serializer<std::string>::serialize(const std::string& value)
{
	return json::value(value);
}

bool Serializer<std::string>::deserialize(const json::value& data, std::string& value)
{
	if (data.is_string())
	{
		value = data.as_string();
		return true;
	}
	return false;
}

json::value Serializer<std::filesystem::path>::serialize(const std::filesystem::path& value)
{
	return json::value(value.string());
}

bool Serializer<std::filesystem::path>::deserialize(const json::value& data, std::filesystem::path& value)
{
	if (data.is_string())
	{
		value = data.as_string();
		return true;
	}
	return false;
}

json::value Serializer<uuid>::serialize(const uuid& value)
{
	return json::value(static_cast<std::string>(value));
}

bool Serializer<uuid>::deserialize(const json::value& data, uuid& value)
{
	if (data.is_string())
	{
		value = data.as_string();
		return true;
	}
	return false;
}

json::value Serializer<math::vec2>::serialize(const math::vec2& value)
{
	return json::object({
		{"x", value.x},
		{"y", value.y}
		});
}

bool Serializer<math::vec2>::deserialize(const json::value& data, math::vec2& value)
{
	if (data.is_object())
	{
		value.x = data.contains("x") ? data["x"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("y") ? data["y"].as_number(0.0f).as_float() : 0.f;
		return true;
	}
	return false;
}

json::value Serializer<math::vec3>::serialize(const math::vec3& value)
{
	return json::object({
		   {"x", value.x},
		   {"y", value.y},
		   {"z", value.z}
		});
}

bool Serializer<math::vec3>::deserialize(const json::value& data, math::vec3& value)
{
	if (data.is_object())
	{
		value.x = data.contains("x") ? data["x"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("y") ? data["y"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("z") ? data["z"].as_number(0.0f).as_float() : 0.f;
		return true;
	}
	return false;
}

json::value Serializer<math::vec4>::serialize(const math::vec4& value)
{
	return json::object({
		   {"x", value.x},
		   {"y", value.y},
		   {"z", value.z},
		   {"w", value.w}
		});
}

bool Serializer<math::vec4>::deserialize(const json::value& data, math::vec4& value)
{
	if (data.is_object())
	{
		value.x = data.contains("x") ? data["x"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("y") ? data["y"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("z") ? data["z"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("w") ? data["w"].as_number(0.0f).as_float() : 0.f;
		return true;
	}
	return false;
}

json::value Serializer<math::transform>::serialize(const math::transform& value)
{
	return json::object({
		{"position", Serializer<math::vec3>::serialize(value.position)},
		{"rotation", Serializer<math::vec3>::serialize(value.rotation)},
		{"scale", Serializer<math::vec3>::serialize(value.scale)},
		{"isStatic", value.isStatic}
		});
}

bool Serializer<math::transform>::deserialize(const json::value& data, math::transform& value)
{
	if (data.is_object())
	{
		bool result = true;
		if (data.contains("position"))
		{
			result &= Serializer<math::vec3>::deserialize(data["position"], value.position);
		}
		if (data.contains("rotation"))
		{
			result &= Serializer<math::vec3>::deserialize(data["rotation"], value.rotation);
		}
		if (data.contains("scale"))
		{
			result &= Serializer<math::vec3>::deserialize(data["scale"], value.scale);
		}
		value.isStatic = data.contains("isStatic") ? data["isStatic"].as_bool(false) : false;
		return result;
	}
	return false;
}