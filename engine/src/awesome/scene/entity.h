/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/core/uuid.h>

class Entity
{
public:
	Entity() = default;
	Entity(const uuid& id);
	Entity(const Entity& other) = delete;
	virtual ~Entity() = default;

	Entity& operator= (const Entity& other) = delete;
	bool operator== (const Entity& other) const;
	bool operator!= (const Entity& other) const;

	const std::vector<std::unique_ptr<Entity>>& children() const { return m_children; }
	const uuid& id() const { return m_id; }
	Entity* const parent() const { return m_parent; }

private:
	std::vector<std::unique_ptr<Entity>> m_children;
	uuid m_id;
	Entity* m_parent{ nullptr };
};