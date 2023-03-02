#include "entity_serialization.h"

json::value Serializer<Entity>::serialize(const Entity& value)
{
	json::value components = json::array();
	for (const auto& component : value.components())
	{
		// components.push_back(Serializer<IType>::serialize((IType*)component.get()));
	}

	return json::object({
		{"children", Serializer<std::vector<std::unique_ptr<Entity>>>::serialize(value.children())},
		{"components", components},
		{"id", serialize(value.id())},
		{"name", value.name},
		{"parent", value.hasParent() ? serialize(value.parent()->id()) : ""},
		{"persistent", value.persistent},
		{"replicate", value.replicate},
		{"tag", value.tag},
		{"transform", Serializer<math::transform>::serialize(value.transform)},
		{"transient", value.transient}
		});
}

bool Serializer<Entity>::deserialize(const json::value& data, Entity& value)
{
	if (!data.is_object()) return false;

	bool result = true;
	if (data.contains("children")) result &= Serializer<std::vector<std::unique_ptr<Entity>>>::deserialize(data["children"], value.m_children);
	// components
	if (data.contains("id")) result &= Serializer<uuid>::deserialize(data["id"], value.m_id);
	if (data.contains("name")) result &= Serializer<std::string>::deserialize(data["name"], value.name);
	// parent
	if (data.contains("persistent")) value.persistent = data["persistent"].as_bool(false);
	if (data.contains("replicate")) value.replicate = data["replicate"].as_bool(false);
	if (data.contains("tag")) result &= Serializer<std::string>::deserialize(data["tag"], value.tag);
	if (data.contains("transform")) result &= Serializer<math::transform>::deserialize(data["transform"], value.transform);
	if (data.contains("transient")) value.transient = data["transient"].as_bool(false);
	return result;
}

json::value Serializer<std::vector<Entity>>::serialize(const std::vector<Entity>& value)
{
	json::value entities = json::array();
	for (const auto& element : value)
	{
		entities.push_back(Serializer<Entity>::serialize(element));
	}
	return entities;
}

bool Serializer<std::vector<Entity>>::deserialize(const json::value& data, std::vector<Entity>& value)
{
	if (data.is_array())
	{
		for (const auto& element : data.as_array())
		{
			Entity entity;
			if (!Serializer<Entity>::deserialize(element, entity))
			{
				return false;
			}
			value.push_back(entity);
		}
		return true;
	}
	return false;
}

json::value Serializer<std::vector<std::unique_ptr<Entity>>>::serialize(const std::vector<std::unique_ptr<Entity>>& value)
{
	json::value entities = json::array();
	for (const auto& element : value)
	{
		entities.push_back(Serializer<Entity>::serialize(*element));
	}
	return entities;
}

bool Serializer<std::vector<std::unique_ptr<Entity>>>::deserialize(const json::value& data, std::vector<std::unique_ptr<Entity>>& value)
{
	if (data.is_array())
	{
		for (const auto& element : data.as_array())
		{
			std::unique_ptr<Entity> entity = std::make_unique<Entity>();
			if (!Serializer<Entity>::deserialize(element, *entity))
			{
				return false;
			}
			value.push_back(std::move(entity));
		}
		return true;
	}
	return false;
}