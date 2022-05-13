/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/timer.h>
#include <awesome/entity/component.h>
#include <awesome/graphics/color.h>

class Health : public Component
{
public:
	Health() = default;
	virtual ~Health() = default;

	virtual void init() override;
	virtual void update(double deltaTime) override;

	virtual void inspect() override;
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	inline int get() const { return m_value; }
	void set(int v);
	inline bool isAlive() const { return m_value > 0; }

	int getPercentage() const;

	Health& operator+= (int value);
	Health& operator-= (int value);

	int min{ 0 };
	int max{ 100 };

	REFLECT()

private:
	graphics::Color m_colorToRestore{ graphics::Color::White };
	bool m_destroyOnDeath{ false };
	graphics::Color m_hitColor{ graphics::Color(1.f, 1.f, 1.f, 5.f) };
	double m_hitDuration{ .1 };
	class SpriteRenderer* m_renderer{ nullptr };
	Timer m_timer{ .1 };
	int m_value{ 100 };
};