#include "entity.h"

void Entity::queue_free()
{
	EntityManager::queue_free(m_id);
}

Entity* const EntityManager::find(const uuid& id)
{
	const auto& it = s_lookup.find(id);
	if (it != s_lookup.end())
	{
		return it->second;
	}
	return nullptr;
}

Entity& EntityManager::get(const uuid& id)
{
	return *s_lookup[id];
}

void EntityManager::clear()
{
	ComponentRegistry::clear();

	s_entities.clear();
	s_components.clear();
	s_lookup.clear();

	s_pendingDeleteEntities = {};
}

void EntityManager::flush()
{
	while (s_pendingDeleteEntities.empty() == false)
	{
		const uuid& id = s_pendingDeleteEntities.front();

		const auto& it = std::find_if(
			s_entities.begin(),
			s_entities.end(),
			[&id](const Entity& entity) -> bool
			{
				return entity.id() == id;
			}
		);
		s_entities.erase(it);
		s_components.erase(id);
		s_lookup.erase(id);

		ComponentRegistry::erase(id);

		s_pendingDeleteEntities.pop();
	}
}

Entity& EntityManager::spawn()
{
	const auto it = s_entities.insert(Entity{});
	s_lookup.insert(std::make_pair(it->id(), &*it));
	return *it;
}

void EntityManager::queue_free(const uuid& entity)
{
	s_pendingDeleteEntities.push(entity);
}
