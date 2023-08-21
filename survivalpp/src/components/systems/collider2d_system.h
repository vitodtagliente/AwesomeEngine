#pragma once

#include "ecs/ecs.h"

#include "components/collider2d.h"

class Collider2DSystem : public System<Collider2D>
{
protected:
	virtual void process(double delta_time, Collider2D& collider);
};