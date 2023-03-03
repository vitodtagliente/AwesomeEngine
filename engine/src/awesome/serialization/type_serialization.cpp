#include "type_serialization.h"

#include "serialization.h"


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
		case NativeType::Type::T_template: break;
		case NativeType::Type::T_type: break;
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