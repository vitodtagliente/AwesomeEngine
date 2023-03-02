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
	return false;
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
	return false;
}