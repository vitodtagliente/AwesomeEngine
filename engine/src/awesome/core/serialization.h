/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>
#include <awesome/encoding/json.h>
#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>

json::value operator<< (json::value& data, const std::string& value);
json::value operator>> (json::value& data, std::string& value);
json::value operator<< (json::value& data, const std::filesystem::path& value);
json::value operator>> (json::value& data, std::filesystem::path& value);
json::value operator<< (json::value& data, const uuid& value);
json::value operator>> (json::value& data, uuid& value);
json::value operator<< (json::value& data, const math::vec2& value);
json::value operator>> (json::value& data, math::vec2& value);
json::value operator<< (json::value& data, const math::vec3& value);
json::value operator>> (json::value& data, math::vec3& value);
json::value operator<< (json::value& data, const math::vec4& value);
json::value operator>> (json::value& data, math::vec4& value);
json::value operator<< (json::value& data, const math::transform& value);
json::value operator>> (json::value& data, math::transform& value);
json::value operator<< (json::value& data, const IType& value);
json::value operator>> (json::value& data, IType& value);
template <typename T = IType>
json::value operator<< (json::value& data, const std::vector<T>& value)
{
	data = json::array();
	for (const auto& element : value)
	{
		json::value element_data;
		element_data << element;
		data.push_back(element_data);
	}
	return data;
}
template <typename T = IType>
json::value operator>> (json::value& data, std::vector<T>& value)
{
	if (data.is_array())
	{
		for (auto& element : data.as_array())
		{
			T type;
			element >> type;
			value.push_back(type);
		}
	}
	return data;
}
template <typename T = IType>
json::value operator<< (json::value& data, const std::vector<std::unique_ptr<T>>& value)
{
	data = json::array();
	for (const auto& element : value)
	{
		json::value element_data;
		element_data << *dynamic_cast<IType*>(element.get());
		data.push_back(element_data);
	}
	return data;
}
template <typename T = IType>
json::value operator>> (json::value& data, std::vector<std::unique_ptr<T>>& value)
{
	if (data.is_array())
	{
		for (auto& element : data.as_array())
		{
			if (!element.contains("type_id")) continue;

			std::unique_ptr<T> type(TypeFactory::instantiate<T>(element["type_id"].as_string()));
			element >> *type;
			value.push_back(std::move(type));
		}
	}
	return data;
}