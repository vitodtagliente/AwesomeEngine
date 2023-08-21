#pragma once

#include <vector>

#include "gameplay/enemy_spawner.h"

class GameMode
{
public:
	void init();
	void update(double delta_time);
	void render();

private:
	EnemySpawner m_spawner;
};