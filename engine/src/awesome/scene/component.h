/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>
#include <awesome/math/transform.h>

#include "component_generated.h"

class Entity;

namespace graphics
{
	class Renderer;
}

CLASS()
class Component : public IType
{
public:
	struct Metrics
	{
		std::size_t count{ 0 };
		std::size_t size{ 0 };
	};

	Component() = default;
	Component(const Component& other);
	virtual ~Component() = default;

	Component& operator= (const Component& other) = delete;
	bool operator== (const Component& other) const;
	bool operator!= (const Component& other) const;

	inline const uuid& getId() const { return m_id; }
	inline Entity* const getOwner() const { return m_owner; }
	const math::transform& getOwnerTransform() const;
	math::transform& getOwnerTransform();
	void queueOwnerDestroy();

	inline bool isAttached() const { return m_owner != nullptr; }

	void attach(Entity* const entity);
	void detach();

	virtual void init() {}
	virtual void render(graphics::Renderer& /*renderer*/) {};
	virtual void uninit() {}
	virtual void update(double /*deltaTime*/) {}

	static const Metrics& metrics() { return s_metrics; }

	static void* operator new(std::size_t size);
	static void operator delete(void* const ptr, std::size_t size);

	PROPERTY() bool enabled{ true };

	GENERATED_BODY()

private:
	PROPERTY() uuid m_id;
	Entity* m_owner{ nullptr };

	static inline Metrics s_metrics;
};