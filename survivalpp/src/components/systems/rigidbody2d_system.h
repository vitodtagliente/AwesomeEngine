#pragma once

#include "ecs/ecs.h"

#include "components/rigidbody2d.h"

class Rigidbody2DSystem : public System<Rigidbody2D>
{
protected:
	virtual void process(double delta_time, Rigidbody2D& body);
};