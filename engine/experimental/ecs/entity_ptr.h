#pragma once

#include "core/uuid.h"

class Entity;

class EntityPtr
{
public:
	EntityPtr() = default;
	EntityPtr(const uuid& id);
	EntityPtr(Entity* const entity);
	
	operator bool() const;

	EntityPtr& operator=(const uuid& id);
	EntityPtr& operator=(Entity* const entity);

	inline bool operator== (const EntityPtr& other) const { return m_id == other.m_id; }
	inline bool operator!= (const EntityPtr& other) const { return m_id != other.m_id; }
	
	Entity* const operator->() const;
	Entity& operator*() const;

	Entity& get() const;
	void reset();

private:
	Entity* m_data{ nullptr };
	uuid m_id{ uuid::Invalid };
};