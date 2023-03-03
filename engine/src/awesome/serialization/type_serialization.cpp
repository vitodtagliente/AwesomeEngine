#include "type_serialization.h"

#include "serialization.h"


json::value operator<<(json::value& data, const IType& value)
{
	return json::value();
}

json::value operator>>(json::value& data, IType& value)
{
	return json::value();
}

json::value operator<<(json::value& data, const std::vector<IType>& value)
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

json::value operator>>(json::value& data, std::vector<IType>& value)
{
	return json::value();
}

json::value operator<<(json::value& data, const std::vector<std::unique_ptr<IType>>& value)
{
	return json::value();
}

json::value operator>>(json::value& data, std::vector<std::unique_ptr<IType>>& value)
{
	return json::value();
}