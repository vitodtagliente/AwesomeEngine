#pragma once

#include "core/event.h"
#include "ecs/component.h"

struct Health : public Component
{
	inline bool alive() const { return value > 0; }

	void set_value(int t_value);

	event_t<int, int> on_change;
	event on_death;
	event on_revive;

	int min{ 0 };
	int max{ 1 };
	int value{ 1 };

	bool destroy_on_death{ true };
};