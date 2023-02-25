/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/entity.h>

#include "serialization.h"

template <>
json::value serialize(const Entity& entity);

template <>
json::value serialize(const std::vector<Entity>& list)
{
	json::value entities = json::array();
	for (const auto& element : list)
	{
		entities.push_back(serialize(element));
	}
	return entities;
}

template <>
json::value serialize(const std::vector<std::unique_ptr<Entity>>& list)
{
	json::value entities = json::array();
	for (const auto& element : list)
	{
		entities.push_back(serialize(*element));
	}
	return entities;
}

template <>
json::value serialize(const Entity& entity)
{
	json::value components = json::array();
	for (const auto& component : entity.components())
	{
		// components.push_back(Serializer<IType>::serialize((IType*)component.get()));
	}

	return json::object({
		{"children", serialize(entity.children())},
		{"components", components},
		{"id", serialize(entity.id())},
		{"name", entity.name},
		{"parent", entity.hasParent() ? serialize(entity.parent()->id()) : ""},
		{"persistent", entity.persistent},
		{"replicate", entity.replicate},
		{"tag", entity.tag},
		{"transform", serialize(entity.transform)},
		{"transient", entity.transient}
		});
}