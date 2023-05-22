/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "types.h"

#include <awesome/scene/component.h>

#include <set>
#include <string>
#include <functional>
#include <optional>

template <class T>
class StoragableEntity
{
public:
	StoragableEntity() = default;

    StoragableEntity(const EntityStorageId storage_id);

	bool operator==(const StoragableEntity& other) const
	{
		return (getId() == other.getId());
	}

	bool operator<(const StoragableEntity& other) const
	{
		return (getId() < other.getId());
	}

	const std::string& getId() const;
    void onRelocation(Component* const);
    void assignEntity(T&);
    const EntityStorageId getStorageId() const { return m_storage_id; }

private:
    std::optional<std::reference_wrapper<T>> m_entity;
    EntityStorageId m_storage_id;
};