#include "health.h"

#include <algorithm>

#include "ecs/entity.h"

void Health::set_value(const int t_value)
{
	const bool was_alive = alive();

	const int old_value = value;
	value = std::clamp(t_value, min, max);

	if (old_value != value)
	{
		on_change.invoke(old_value, value);

		if (value == min && was_alive)
		{
			on_death.invoke();
			if (destroy_on_death)
			{
				entity()->queue_free();
			}
		}
		else if (!was_alive && value > 0)
		{
			on_revive.invoke();
		}
	}
}
