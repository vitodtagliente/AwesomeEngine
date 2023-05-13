/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/component.h>

#include "test_component_generated.h"

CLASS(Type = Component)
class TestComponent : public Component
{
public:
	virtual void init() override;
	virtual void update(double deltaTime) override;

	PROPERTY() float speed = 5.f;

	GENERATED_BODY()
private:
	class Rigidbody2DComponent* m_body{ nullptr };
};