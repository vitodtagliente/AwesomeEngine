/// Copyright (c) Vito Domenico Tagliente

#include "storagable_entity.h"
#include <awesome/scene/entity.h>

template <class T>
StoragableEntity<T>::StoragableEntity(const EntityStorageId storage_id)
	: m_storage_id(storage_id)
{}

template <class T>
const std::string& StoragableEntity<T>::getId() const
{
	return m_entity->get().id().value;
}

template <class T>
void StoragableEntity<T>::onRelocation(Component* const component)
{
	m_entity->get().handleRelocation(component);
}

template <class T>
void StoragableEntity<T>::assignEntity(T& entity)
{
	m_entity.emplace(std::ref(entity));
}

template class StoragableEntity<Entity>;