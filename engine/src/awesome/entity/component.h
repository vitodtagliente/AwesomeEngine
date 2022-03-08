/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/uuid.h>
#include <awesome/encoding/json.h>

class Entity;
class World;

namespace graphics
{
	class Renderer;
}

class Component
{
public:

	Component();
	~Component() = default;

	bool enabled;

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

	virtual json::value toJson() const;
	void fromJson(const json::value& data);

private:
	uuid m_id;
	Entity* m_owner;
};