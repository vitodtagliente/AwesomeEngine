#pragma once

#include "ecs/ecs.h"

#include "game/components/bullet.h"

class BulletSystem : public System<Bullet>
{
protected:
	virtual void process(double delta_time, Bullet& bullet);
};