/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/uuid.h>
#include <awesome/encoding/json.h>

class Entity;

class Component
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

	// editor
	virtual void inspect();
	// serialization
	virtual json::value serialize() const;
	virtual bool deserialize(const json::value& data);

	virtual void init() {}
	virtual void uninit() {}
	virtual void update(double /*deltaTime*/) {}

	bool enabled{ true };

private:
	uuid m_id;
	Entity* m_owner{ nullptr };
};