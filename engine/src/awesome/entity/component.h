/// Copyright (c) Vito Domenico Tagliente
#pragma once

class Entity;
class World;

namespace editor
{
	class Context;
}

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

	inline Entity* const getOwner() const { return m_owner; }
	World* const getWorld() const;
	inline bool isAttached() const { return m_owner != nullptr; }

	void attach(Entity* const entity);
	void detach();

	virtual void init() {}
	virtual void uninit() {}
	virtual void update(double /*deltaTime*/) {}
	virtual void render(graphics::Renderer& /*renderer*/) {}
	virtual void inspect(editor::Context& context);

private:
	Entity* m_owner;
};