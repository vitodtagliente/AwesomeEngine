#include "serialization.h"

#include <awesome/core/string_util.h>

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

json::value operator<<(json::value& data, const IType& value)
{
	data = json::object();
	data["type_id"] = std::string(value.type_name());
	for (const auto& [name, property] : value.type_properties())
	{
		switch (property.type.type)
		{
		case NativeType::Type::T_bool: data[name] = property.value<bool>(&value); break;
		case NativeType::Type::T_double: data[name] = property.value<double>(&value); break;
		case NativeType::Type::T_enum: data[name] = property.value<int>(&value); break;
		case NativeType::Type::T_float: data[name] = property.value<float>(&value); break;
		case NativeType::Type::T_int: data[name] = property.value<int>(&value); break;
		case NativeType::Type::T_string: data[name] = property.value<std::string>(&value); break;
		case NativeType::Type::T_template: 
		{
			if (StringUtil::contains(property.type.name, "vector", StringUtil::CompareMode::IgnoreCase))
			{

			}
			break;
		}
		case NativeType::Type::T_type: break;
		case NativeType::Type::T_unknown: 
		{
			if (StringUtil::contains(property.type.name, "transform", StringUtil::CompareMode::IgnoreCase))
			{
				data[name] << property.value<math::transform>(&value);
			}
			else if (StringUtil::contains(property.type.name, "transform", StringUtil::CompareMode::IgnoreCase))
			{
				data[name] << property.value<math::transform>(&value);
			}
			else if (StringUtil::contains(property.type.name, "uuid", StringUtil::CompareMode::IgnoreCase))
			{
				data[name] << property.value<uuid>(&value);
			}
			else if (StringUtil::contains(property.type.name, "vec2", StringUtil::CompareMode::IgnoreCase))
			{
				data[name] << property.value<math::vec2>(&value);
			}
			else if (StringUtil::contains(property.type.name, "vec3", StringUtil::CompareMode::IgnoreCase))
			{
				data[name] << property.value<math::vec3>(&value);
			}
			else if (StringUtil::contains(property.type.name, "vec4", StringUtil::CompareMode::IgnoreCase))
			{
				data[name] << property.value<math::vec4>(&value);
			}
			break;
		}
		default: break;
		}
	}
	return data;
}

json::value operator>>(json::value& data, IType& value)
{
	if (data.is_object())
	{
		if (!data.contains("type_id") || data["type_id"].as_string("") != value.type_name())
		{
			return data;
		}

		for (const auto& [name, property] : value.type_properties())
		{
			switch (property.type.type)
			{
			case NativeType::Type::T_bool: property.value<bool>(&value) = data[name].as_bool(false); break;
			case NativeType::Type::T_double: property.value<double>(&value) = data[name].as_number(0).as_double(); break;
			case NativeType::Type::T_enum: property.value<int>(&value) = data[name].as_number().as_int(); break;
			case NativeType::Type::T_float: property.value<float>(&value) = data[name].as_number(0.f).as_float(); break;
			case NativeType::Type::T_int: property.value<int>(&value) = data[name].as_number(0).as_int(); break;
			case NativeType::Type::T_string: property.value<std::string>(&value) = data[name].as_string(""); break;
			case NativeType::Type::T_template: break;
			case NativeType::Type::T_type: break;
			default: break;
			}
		}
	}
	return data;
}