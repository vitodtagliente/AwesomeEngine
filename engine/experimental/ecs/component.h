/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "core/uuid.h"
#include "ecs/entity_ptr.h"

class Component
{
public:
	template <typename T>
	friend class ComponentArray;

	bool operator== (const Component& other) const;
	bool operator!= (const Component& other) const;

	inline const EntityPtr& entity() const { return m_entity; }
	inline const uuid& id() const { return m_id; }

	virtual void init() { }
	virtual void uninit() {}

	bool enabled{ true };

private:
	void attach(const EntityPtr& entity);

	EntityPtr m_entity;
	uuid m_id;
};