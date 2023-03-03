#include "entity_serialization.h"

json::value operator<<(json::value& data, const Entity& value)
{
	data =  json::object({
		{"name", value.name},
		{"persistent", value.persistent},
		{"replicate", value.replicate},
		{"tag", value.tag},
		{"transient", value.transient}
		});
	data["children"] << value.children();
	// data["components"] 
	data["id"] << value.id();
	if (value.hasParent())
	{
		data["parent"] << value.parent()->id();
	}
	data["transform"] << value.transform;
	return data;
}

json::value operator>>(json::value& data, Entity& value)
{
	return json::value();
}

json::value operator<<(json::value& data, const std::vector<Entity>& value)
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

json::value operator>>(json::value& data, std::vector<Entity>& value)
{
	if (data.is_array())
	{
		for (auto& element : data.as_array())
		{
			Entity entity;
			element >> entity;
			value.push_back(entity);
		}
	}
	return data;
}

json::value operator<<(json::value& data, const std::vector<std::unique_ptr<Entity>>& value)
{
	data = json::array();
	for (const auto& element : value)
	{
		json::value element_data;
		element_data << *element;
		data.push_back(element_data);
	}
	return data;
}

json::value operator>>(json::value& data, std::vector<std::unique_ptr<Entity>>& value)
{
	if (data.is_array())
	{
		for (auto& element : data.as_array())
		{
			std::unique_ptr<Entity> entity = std::make_unique<Entity>();
			element >> *entity;
			value.push_back(std::move(entity));
		}
	}
	return data;
}
