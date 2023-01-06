/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/uuid.h>

#include "component_generated.h"

namespace graphics
{
	class Renderer2D;
}

class Entity;

CLASS()
class Component : public Type
{
public:
	Component();
	Component(const Component& other) = delete;
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
	virtual void render(graphics::Renderer2D* const /*renderer*/) {}
	virtual void update(double /*deltaTime*/) {}

	// editor
	virtual void inspect();

	PROPERTY() bool enabled{ true };

	GENERATED_BODY()

private:
	PROPERTY() uuid m_id;
	Entity* m_owner{ nullptr };
};