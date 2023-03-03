#include "serialization.h"

json::value operator<<(json::value& data, const std::string& value)
{
	data = json::value(value);
	return data;
}

json::value operator>>(json::value& data, std::string& value)
{
	if (data.is_string())
	{
		value = data.as_string();
	}
	return data;
}

json::value operator<<(json::value& data, const std::filesystem::path& value)
{
	data = json::value(value.string());
	return data;
}

json::value operator>>(json::value& data, std::filesystem::path& value)
{
	if (data.is_string())
	{
		value = data.as_string();
	}
	return data;
}

json::value operator<<(json::value& data, const uuid& value)
{
	data = json::value(static_cast<std::string>(value));
	return data;
}

json::value operator>>(json::value& data, uuid& value)
{
	if (data.is_string())
	{
		value = data.as_string();
	}
	return data;
}

json::value operator<<(json::value& data, const math::vec2& value)
{
	data = json::object({
		{"x", value.x},
		{"y", value.y}
	});
	return data;
}

json::value operator>>(json::value& data, math::vec2& value)
{
	if (data.is_object())
	{
		value.x = data.contains("x") ? data["x"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("y") ? data["y"].as_number(0.0f).as_float() : 0.f;
	}
	return data;
}

json::value operator<<(json::value& data, const math::vec3& value)
{
	data = json::object({
		{"x", value.x},
		{"y", value.y},
		{"z", value.z}
	});
	return data;
}

json::value operator>>(json::value& data, math::vec3& value)
{
	if (data.is_object())
	{
		value.x = data.contains("x") ? data["x"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("y") ? data["y"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("z") ? data["z"].as_number(0.0f).as_float() : 0.f;
	}
	return data;
}

json::value operator<<(json::value& data, const math::vec4& value)
{
	data = json::object({
		{"x", value.x},
		{"y", value.y},
		{"z", value.z},
		{"w", value.w}
	});
	return data;
}

json::value operator>>(json::value& data, math::vec4& value)
{
	if (data.is_object())
	{
		value.x = data.contains("x") ? data["x"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("y") ? data["y"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("z") ? data["z"].as_number(0.0f).as_float() : 0.f;
		value.x = data.contains("w") ? data["w"].as_number(0.0f).as_float() : 0.f;
	}
	return data;
}

json::value operator<<(json::value& data, const math::transform& value)
{
	data = json::object();
	data["position"] << value.position;
	data["rotation"] << value.rotation;
	data["scale"] << value.scale;
	data["isStatic"] = value.isStatic;
	return data;
}

json::value operator>>(json::value& data, math::transform& value)
{
	if (data.is_object())
	{
		bool result = true;
		if (data.contains("position"))
		{
			data["position"] >> value.position;
		}
		if (data.contains("rotation"))
		{
			data["rotation"] >> value.rotation;
		}
		if (data.contains("scale"))
		{
			data["scale"] >> value.scale;
		}
		if (data.contains("isStatic"))
		{
			value.isStatic = data["isStatic"].as_bool(false);
		}
	}
	return data;
}
