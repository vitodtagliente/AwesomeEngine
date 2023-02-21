/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>

#include "component_generated.h"

class Entity;

CLASS()
class Component : public IType
{
public:
	Component() = default;
	Component(const Component& other);
	virtual ~Component() = default;

	Component& operator= (const Component& other) = delete;
	bool operator== (const Component& other) const;
	bool operator!= (const Component& other) const;

	inline const uuid& getId() const { return m_id; }
	inline Entity* const getOwner() const { return m_owner; }
	inline bool isAttached() const { return m_owner != nullptr; }

	void attach(Entity* const entity);
	void detach();

	virtual void init() {}
	virtual void uninit() {}
	virtual void update(double /*deltaTime*/) {}

	bool enabled{ true };

	GENERATED_BODY()

private:
	uuid m_id;
	Entity* m_owner{ nullptr };
};