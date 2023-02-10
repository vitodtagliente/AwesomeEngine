/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/component/sprite_renderer_component.h>
#include <awesome/core/timer.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>

#include "health_component_generated.h"

CLASS(Type = Component)
class HealthComponent : public Component
{
public:
	HealthComponent() = default;
	virtual ~HealthComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	inline int getValue() const { return m_value; }
	void setValue(int v);
	inline bool isAlive() const { return m_value > 0; }

	int getPercentage() const;

	HealthComponent& operator+= (int value);
	HealthComponent& operator-= (int value);

	PROPERTY() int min{ 0 };
	PROPERTY() int max{ 100 };

	GENERATED_BODY()

private:
	PROPERTY() graphics::Color m_colorToRestore{ graphics::Color::White };
	PROPERTY() bool m_destroyOnDeath{ false };
	PROPERTY() graphics::Color m_hitColor{ graphics::Color(1.f, 1.f, 1.f, 5.f) };
	PROPERTY() double m_hitDuration{ .1 };
	SpriteRendererComponent* m_renderer{ nullptr };
	Timer m_timer{ .1 };
	PROPERTY() int m_value{ 100 };
};