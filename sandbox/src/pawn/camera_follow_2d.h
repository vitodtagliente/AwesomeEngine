/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>
#include <awesome/entity/entity.h>

class CameraFollow2d : public Component
{
public:
	CameraFollow2d() = default;
	virtual ~CameraFollow2d() = default;

	virtual void update(double deltaTime) override;

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	PROTO()

private:
	float m_speed{ 3.0f };
	Entity* m_target{ nullptr };
};