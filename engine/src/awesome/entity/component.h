/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/serialization.h>
#include <awesome/core/uuid.h>
#include <awesome/encoding/json.h>
#include <awesome/net/net_mode.h>

#include "component_generated.h"

class Entity;

CLASS()
class Component : public Type, public ISerializable
{
public:
	Component() = default;
	Component(const Component& other) = delete;
	virtual ~Component() = default;

	Component& operator= (const Component& other) = delete;
	bool operator== (const Component& other) const;
	bool operator!= (const Component& other) const;

	inline const uuid& getId() const { return m_id; }
	inline Entity* const getOwner() const { return m_owner; }
	inline NetMode getNetMode() const { return m_netMode; }
	inline bool isAttached() const { return m_owner != nullptr; }

	void attach(Entity* const entity);
	void detach();

	virtual void init() {}
	virtual void uninit() {}
	virtual void update(double /*deltaTime*/) {}

	// serialization
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	// editor
	virtual void inspect();

	PROPERTY() bool enabled{ true };

	GENERATED_BODY()

private:
	PROPERTY() uuid m_id;
	PROPERTY(IsEnum) NetMode m_netMode{ NetMode::Shared };
	Entity* m_owner{ nullptr };
};