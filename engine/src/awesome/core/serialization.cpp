#include "serialization.h"

#include <awesome/core/string_util.h>

json::value operator<<(json::value& data, const bool& value)
{
	return json::value(value);
}

json::value operator>>(json::value& data, bool& value)
{
	if (data.is_bool())
	{
		value = data.as_bool();
	}
	return data;
}

json::value operator<<(json::value& data, const double& value)
{
	return json::value(value);
}

json::value operator>>(json::value& data, double& value)
{
	if (data.is_number())
	{
		value = data.as_number(0).as_double();
	}
	return data;
}

json::value operator<<(json::value& data, const int& value)
{
	return json::value(value);
}

json::value operator>>(json::value& data, int& value)
{
	if (data.is_number())
	{
		value = data.as_number(0).as_int();
	}
	return data;
}

json::value operator<<(json::value& data, const float& value)
{
	return json::value(value);
}

json::value operator>>(json::value& data, float& value)
{
	if (data.is_number())
	{
		value = data.as_number(0.f).as_float();
	}
	return data;
}


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

void serializeVector(const IType& value, const Property& property, const NativeType type, json::value& data);
void serialize(const IType& value, const Property& property, json::value& data)
{
	switch (property.type.type)
	{
	case NativeType::Type::T_bool: data = property.value<bool>(&value); break;
	case NativeType::Type::T_double: data = property.value<double>(&value); break;
	case NativeType::Type::T_enum: data = property.value<int>(&value); break;
	case NativeType::Type::T_float: data = property.value<float>(&value); break;
	case NativeType::Type::T_int: data = property.value<int>(&value); break;
	case NativeType::Type::T_string: data = property.value<std::string>(&value); break;
	case NativeType::Type::T_template:
	{
		if (StringUtil::contains(property.type.name, "map", StringUtil::CompareMode::IgnoreCase))
		{

		}
		else if (StringUtil::contains(property.type.name, "shared_ptr", StringUtil::CompareMode::IgnoreCase))
		{
			if (property.type.children.front().type == NativeType::Type::T_type)
			{
				data << property.value<std::shared_ptr<IType>>(&value);
			}
		}
		else if (StringUtil::contains(property.type.name, "vector", StringUtil::CompareMode::IgnoreCase))
		{
			serializeVector(value, property, property.type.children.front(), data);
		}
		else if (StringUtil::contains(property.type.name, "unique_ptr", StringUtil::CompareMode::IgnoreCase))
		{
			if (property.type.children.front().type == NativeType::Type::T_type)
			{
				data << property.value<std::unique_ptr<IType>>(&value);
			}
		}
		break;
	}
	case NativeType::Type::T_type: 
	{

		break;
	}
	case NativeType::Type::T_unknown:
	{
		if (StringUtil::contains(property.type.name, "transform", StringUtil::CompareMode::IgnoreCase))
		{
			data << property.value<math::transform>(&value);
		}
		else if (StringUtil::contains(property.type.name, "uuid", StringUtil::CompareMode::IgnoreCase))
		{
			data << property.value<uuid>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec2", StringUtil::CompareMode::IgnoreCase))
		{
			data << property.value<math::vec2>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec3", StringUtil::CompareMode::IgnoreCase))
		{
			data << property.value<math::vec3>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec4", StringUtil::CompareMode::IgnoreCase))
		{
			data << property.value<math::vec4>(&value);
		}
		break;
	}
	default: break;
	}
}
void serializeVector(const IType& value, const Property& property, const NativeType type, json::value& data)
{
	switch (type.type)
	{
	case NativeType::Type::T_bool: data << property.value<std::vector<bool>>(&value); break;
	case NativeType::Type::T_double: data << property.value<std::vector<double>>(&value); break;
	case NativeType::Type::T_enum: data << property.value<std::vector<int>>(&value); break;
	case NativeType::Type::T_float: data << property.value<std::vector<float>>(&value); break;
	case NativeType::Type::T_int: data << property.value<std::vector<int>>(&value); break;
	case NativeType::Type::T_string: data << property.value<std::vector<std::string>>(&value); break;
	case NativeType::Type::T_template:
	{
		if (StringUtil::contains(type.name, "shared_ptr", StringUtil::CompareMode::IgnoreCase))
		{
			if (type.children.front().type == NativeType::Type::T_type)
			{
				data << property.value<std::vector<std::shared_ptr<IType>>>(&value);
			}
		}
		else if (StringUtil::contains(type.name, "unique_ptr", StringUtil::CompareMode::IgnoreCase))
		{
			if (type.children.front().type == NativeType::Type::T_type)
			{
				data << property.value<std::vector<std::unique_ptr<IType>>>(&value);
			}
		}
		break;
	}
	case NativeType::Type::T_type: 
	{

		break;
	}
	case NativeType::Type::T_unknown:
	{
		if (StringUtil::contains(property.type.name, "transform", StringUtil::CompareMode::IgnoreCase))
		{
			data << property.value<std::vector<math::transform>>(&value);
		}
		else if (StringUtil::contains(property.type.name, "uuid", StringUtil::CompareMode::IgnoreCase))
		{
			data << property.value<std::vector<uuid>>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec2", StringUtil::CompareMode::IgnoreCase))
		{
			data << property.value<std::vector<math::vec2>>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec3", StringUtil::CompareMode::IgnoreCase))
		{
			data << property.value<std::vector<math::vec3>>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec4", StringUtil::CompareMode::IgnoreCase))
		{
			data << property.value<std::vector<math::vec4>>(&value);
		}
		break;
	}
	default: break;
	}
}

json::value operator<<(json::value& data, const IType& value)
{
	data = json::object();
	data["type_id"] = std::string(value.type_name());
	for (const auto& [name, property] : value.type_properties())
	{
		serialize(value, property, data[name]);
	}
	return data;
}

void deserializeVector(const IType& value, const Property& property, const NativeType type, json::value& data);
void deserialize(const IType& value, const Property& property, json::value& data)
{
	switch (property.type.type)
	{
	case NativeType::Type::T_bool: property.value<bool>(&value) = data.as_bool(); break;
	case NativeType::Type::T_double: property.value<double>(&value) = data.as_number().as_double(); break;
	case NativeType::Type::T_enum: property.value<int>(&value) = data.as_number().as_int(); break;
	case NativeType::Type::T_float: property.value<float>(&value) = data.as_number().as_float(); break;
	case NativeType::Type::T_int: property.value<int>(&value) = data.as_number().as_int(); break;
	case NativeType::Type::T_string: property.value<std::string>(&value) = data.as_string(); break;
	case NativeType::Type::T_template:
	{
		if (StringUtil::contains(property.type.name, "map", StringUtil::CompareMode::IgnoreCase))
		{

		}
		else if (StringUtil::contains(property.type.name, "shared_ptr", StringUtil::CompareMode::IgnoreCase))
		{
			if (property.type.children.front().type == NativeType::Type::T_type)
			{
				data >> property.value<std::shared_ptr<IType>>(&value);
			}
		}
		else if (StringUtil::contains(property.type.name, "vector", StringUtil::CompareMode::IgnoreCase))
		{
			deserializeVector(value, property, property.type.children.front(), data);
		}
		else if (StringUtil::contains(property.type.name, "unique_ptr", StringUtil::CompareMode::IgnoreCase))
		{
			if (property.type.children.front().type == NativeType::Type::T_type)
			{
				data >> property.value<std::unique_ptr<IType>>(&value);
			}
		}
		break;
	}
	case NativeType::Type::T_type:
	{

		break;
	}
	case NativeType::Type::T_unknown:
	{
		if (StringUtil::contains(property.type.name, "transform", StringUtil::CompareMode::IgnoreCase))
		{
			data >> property.value<math::transform>(&value);
		}
		else if (StringUtil::contains(property.type.name, "uuid", StringUtil::CompareMode::IgnoreCase))
		{
			data >> property.value<uuid>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec2", StringUtil::CompareMode::IgnoreCase))
		{
			data >> property.value<math::vec2>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec3", StringUtil::CompareMode::IgnoreCase))
		{
			data >> property.value<math::vec3>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec4", StringUtil::CompareMode::IgnoreCase))
		{
			data >> property.value<math::vec4>(&value);
		}
		break;
	}
	default: break;
	}
}
void deserializeVector(const IType& value, const Property& property, const NativeType type, json::value& data)
{
	switch (type.type)
	{
	case NativeType::Type::T_bool: data >> property.value<std::vector<bool>>(&value); break;
	case NativeType::Type::T_double: data >> property.value<std::vector<double>>(&value); break;
	case NativeType::Type::T_enum: data >> property.value<std::vector<int>>(&value); break;
	case NativeType::Type::T_float: data >> property.value<std::vector<float>>(&value); break;
	case NativeType::Type::T_int: data >> property.value<std::vector<int>>(&value); break;
	case NativeType::Type::T_string: data >> property.value<std::vector<std::string>>(&value); break;
	case NativeType::Type::T_template:
	{
		if (StringUtil::contains(type.name, "shared_ptr", StringUtil::CompareMode::IgnoreCase))
		{
			if (type.children.front().type == NativeType::Type::T_type)
			{
				data >> property.value<std::vector<std::shared_ptr<IType>>>(&value);
			}
		}
		else if (StringUtil::contains(type.name, "unique_ptr", StringUtil::CompareMode::IgnoreCase))
		{
			if (type.children.front().type == NativeType::Type::T_type)
			{
				data >> property.value<std::vector<std::unique_ptr<IType>>>(&value);
			}
		}
		break;
	}
	case NativeType::Type::T_type:
	{

		break;
	}
	case NativeType::Type::T_unknown:
	{
		if (StringUtil::contains(property.type.name, "transform", StringUtil::CompareMode::IgnoreCase))
		{
			data >> property.value<std::vector<math::transform>>(&value);
		}
		else if (StringUtil::contains(property.type.name, "uuid", StringUtil::CompareMode::IgnoreCase))
		{
			data >> property.value<std::vector<uuid>>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec2", StringUtil::CompareMode::IgnoreCase))
		{
			data >> property.value<std::vector<math::vec2>>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec3", StringUtil::CompareMode::IgnoreCase))
		{
			data >> property.value<std::vector<math::vec3>>(&value);
		}
		else if (StringUtil::contains(property.type.name, "vec4", StringUtil::CompareMode::IgnoreCase))
		{
			data >> property.value<std::vector<math::vec4>>(&value);
		}
		break;
	}
	default: break;
	}
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
			deserialize(value, property, data[name]);
		}
	}
	return data;
}

json::value operator<<(json::value& data, const std::shared_ptr<IType>& value)
{
	if (value != nullptr)
	{
		data << *value;
	}
	return data;
}

json::value operator>>(json::value& data, std::shared_ptr<IType>& value)
{
	if (data.is_object())
	{
		if (!data.contains("type_id"))
		{
			return data;
		}

		if (value == nullptr)
		{
			value = std::shared_ptr<IType>(TypeFactory::instantiate<IType>(data["type_id"].as_string()));
		}
		else if (data["type_id"].as_string("") != value->type_name())
		{
			return data;
		}

		data >> *value;
	}
	return data;
}

json::value operator<<(json::value& data, const std::unique_ptr<IType>& value)
{
	if (value != nullptr)
	{
		data << *value;
	}
	return data;
}

json::value operator>>(json::value& data, std::unique_ptr<IType>& value)
{
	if (data.is_object())
	{
		if (!data.contains("type_id"))
		{
			return data;
		}

		if (value == nullptr)
		{
			value = std::unique_ptr<IType>(TypeFactory::instantiate<IType>(data["type_id"].as_string()));
		}
		else if (data["type_id"].as_string("") != value->type_name())
		{
			return data;
		}

		data >> *value;
	}
	return data;
}