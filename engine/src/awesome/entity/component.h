/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/core/serialization.h>
#include <awesome/core/uuid.h>
#include <awesome/encoding/json.h>

class Entity;
class World;

namespace graphics
{
	class Renderer;
}

class Component : public ISerializable
{
public:

	Component() = default;
	Component(const Component& other);
	virtual ~Component() = default;

	Component& operator= (const Component& other);
	bool operator== (const Component& other) const;
	bool operator!= (const Component& other) const;

	inline const uuid& getId() const { return m_id; }
	inline Entity* const getOwner() const { return m_owner; }
	World* const getWorld() const;
	inline bool isAttached() const { return m_owner != nullptr; }

	void attach(Entity* const entity);
	void detach();

	virtual void init() {}
	virtual void uninit() {}
	virtual void update(double /*deltaTime*/) {}
	virtual void render(graphics::Renderer* const /*renderer*/) {}

	// serialization
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	// editor
	virtual void inspect();

	bool enabled{ true };

	REFLECT()

private:
	uuid m_id;
	Entity* m_owner{ nullptr };
};

#define REFLECT_COMPONENT(T) REFLECT_IMP_CATEGORY(T, Component)