/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/encoding/json.h>

json::value operator<< (json::value& data, const IType& value);
json::value operator>> (json::value& data, IType& value);
template <typename T = IType>
json::value operator<< (json::value& data, const std::vector<T>& value)
{
	data = json::array();
	for (const auto& element : value)
	{
		json::value element_data;
		element_data << *dynamic_cast<IType*>(&element);
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
			std::unique_ptr<T> type = std::make_unique<T>();
			element >> *type;
			value.push_back(std::move(type));
		}
	}
	return data;
}