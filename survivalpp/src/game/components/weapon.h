#pragma once

#include <string>

#include "ecs/component.h"

#include "core/timer.h"
#include "math/vector2.h"

class Weapon : public Component
{
public:
	void update(double delta_time);

	void aim(const math::vec2& direction);
	void attack();

	std::string texture;

private:
	math::vec2 m_direction;
	Timer m_timer{ 0.f };
};