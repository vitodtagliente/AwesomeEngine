#include "entity_ptr.h"

#include "entity.h"

EntityPtr::EntityPtr(const uuid& id)
{
	const auto& it = EntityManager::s_lookup.find(id);
	if (it != EntityManager::s_lookup.end())
	{
		m_id = id;
		m_data = it->second;
	}
	else
	{
		reset();
	}
}

EntityPtr::EntityPtr(Entity* const entity)
{
	if (entity)
	{
		m_data = entity;
		m_id = entity->id();
	}
}

EntityPtr& EntityPtr::operator=(const uuid& id)
{
	const auto& it = EntityManager::s_lookup.find(id);
	if (it != EntityManager::s_lookup.end())
	{
		m_id = id;
		m_data = it->second;
	}
	else
	{
		reset();
	}

	return *this;
}

EntityPtr& EntityPtr::operator=(Entity* const entity)
{
	if (entity)
	{
		m_data = entity;
		m_id = entity->id();
	}
	return *this;
}

EntityPtr::operator bool() const
{
	return m_data != nullptr && m_data->id() == m_id;
}

Entity& EntityPtr::get() const
{
	return *m_data;
}

void EntityPtr::reset()
{
	m_data = nullptr;
	m_id = uuid::Invalid;
}

Entity& EntityPtr::operator*() const
{
	return *m_data;
}

Entity* const EntityPtr::operator->() const
{
	return m_data;
}
