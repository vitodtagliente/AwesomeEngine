/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/component/sprite_renderer_component.h>
#include <awesome/core/timer.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>

#include "health_component_generated.h"

CLASS()
class HealthComponent : public Component
{
public:
	HealthComponent() = default;
	virtual ~HealthComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	inline int get() const { return m_value; }
	void set(int v);
	inline bool isAlive() const { return m_value > 0; }

	int getPercentage() const;

	HealthComponent& operator+= (int value);
	HealthComponent& operator-= (int value);

	int min{ 0 };
	int max{ 100 };

	GENERATED_BODY()

private:
	graphics::Color m_colorToRestore{ graphics::Color::White };
	bool m_destroyOnDeath{ false };
	graphics::Color m_hitColor{ graphics::Color(1.f, 1.f, 1.f, 5.f) };
	double m_hitDuration{ .1 };
	SpriteRendererComponent* m_renderer{ nullptr };
	Timer m_timer{ .1 };
	int m_value{ 100 };
};