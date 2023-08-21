#pragma once

#include "core/timer.h"

class EnemySpawner
{
public:
	void update(double delta_time);

private:
	Timer m_spawn_timer{ 1.f };
};